#pragma hdrstop
#include "uFunctions.h"
#include "Protocol.h"
#include "RLCard502.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
RLCard502::RLCard502(void)
{
	raw_size = LCard502_INIT_SIZE;
	rawi = new unsigned int[raw_size];
	raw = new double[raw_size];
	handle = L502_Create();
	if (handle == NULL)
		FATAL("LCard502::LCard502: ������ �������� ��������� ������");
	unsigned int dev_cnt = 0;
	if (L502_GetSerialList(NULL, 0, 0, &dev_cnt) < 0)
		FATAL("LCard502::LCard502: �� ����� ����� �� ������� !");
	if (dev_cnt <= 0)
		FATAL("LCard502::LCard502: �� ����� ����� �� ������� !!");
	t_l502_serial_list list =
		(t_l502_serial_list)(new char[dev_cnt * L502_SERIAL_SIZE]);
	if (L502_GetSerialList(list, dev_cnt, 0, NULL) <= 0)
		FATAL("LCard502::LCard502: �� ����� ����� �� ������� !!!");
	AnsiString a = "LCard502::LCard502: ������ �������� ������: ";
	a += list[0];
	LFATAL(a, L502_Open(handle, list[0]));
	delete[](char*)list;
	IsStarted = false;
	RECV_TOUT = 700;
	MainSensors = 0;
	OtherSensors = 0;
}

// ---------------------------------------------------------------------------
RLCard502::~RLCard502(void)
{
	Stop();
	L502_Free(handle);
	delete rawi;
	delete raw;
}

// ---------------------------------------------------------------------------
void RLCard502::LFATAL(AnsiString _msg, int _err)
{
	if (_err == 0)
		return;
	AnsiString a = _msg;
	a += " ";
	a += L502_GetErrorString(_err);
	FATAL(a);
}

// ---------------------------------------------------------------------------
bool RLCard502::CheckError(int _err)
{
	if (_err == 0)
		return (false);
	LastError = L502_GetErrorString(_err);
	return (true);
}

// ---------------------------------------------------------------------------
void RLCard502::LoadMainSettings()
{
	AnsiString a = "LCard502::LoadMainSettings: �� ������� ������ ���������";
	MainSensors = Parameters->channels.size();
	LFATAL(a, L502_SetLChannelCount(handle, MainSensors));
	for (int i = 0; i < MainSensors; i++)
	{
		AnsiString a = "�����[";
		a += i;
		a += "]=l:";
		a += Parameters->channels[i].logicalChannel;
		a += ",m:";
		a += Parameters->channels[i].collectedMode;
		a += ",r:";
		a += Parameters->channels[i].range;
		TPr::pr(a);
		LFATAL(a, L502_SetLChannel(handle, i,
			Parameters->channels[i].logicalChannel,
			Parameters->channels[i].collectedMode,
			Parameters->channels[i].range, 0));
	}
	// ����������� �������� ������� �������������
	LFATAL(a, L502_SetSyncMode(handle, Parameters->syncMode));
	// �����������  �������� ������� �����
	LFATAL(a, L502_SetSyncStartMode(handle, Parameters->syncStartMode));
	double f_acq = Parameters->frequencyPerChannel * MainSensors;
	double f_lch = Parameters->frequencyPerChannel;
	// ����������� ������� ����� � ���
	LFATAL(a, L502_SetAdcFreq(handle, &f_acq, &f_lch));
  //LFATAL(a, L502_SetDmaBufSize(handle, X502_STREAM_CH_IN, 50000000));
	// Parameters.frequencyCollect = f_acq;
	// Parameters.frequencyPerChannel = f_lch;
	// ���������� ��������� � ������
	LFATAL(a, L502_Configure(handle, 0));
}

// ---------------------------------------------------------------------------
void RLCard502::LoadOtherSettings()
{
	AnsiString a = "LCard502::LoadOtherSettings: �� ������� ������ ���������";
	OtherSensors = Parameters->others.size();
	LFATAL(a, L502_SetLChannelCount(handle, OtherSensors));
	for (int i = 0; i < OtherSensors; i++)
	{
		/*
		 AnsiString a = "�����[";
		 a += i;
		 a += "]=l:";
		 a += Parameters->others[i].logicalChannel;
		 a += ",m:";
		 a += Parameters->others[i].collectedMode;
		 a += ",r:";
		 a += Parameters->others[i].range;
		 TPr::pr(a);
		 */
		LFATAL(a, L502_SetLChannel(handle, i,
			Parameters->others[i].logicalChannel,
			Parameters->others[i].collectedMode,
			Parameters->others[i].range, 0));
	}
	// ����������� �������� ������� �������������
	LFATAL(a, L502_SetSyncMode(handle, Parameters->syncMode));
	// �����������  �������� ������� �����
	LFATAL(a, L502_SetSyncStartMode(handle, Parameters->syncStartMode));
	double f_acq = Parameters->frequencyPerChannel * OtherSensors;
	double f_lch = Parameters->frequencyPerChannel;
	// ����������� ������� ����� � ���
	LFATAL(a, L502_SetAdcFreq(handle, &f_acq, &f_lch));
	// Parameters.frequencyCollect = f_acq;
	// Parameters.frequencyPerChannel = f_lch;
	// ���������� ��������� � ������
	LFATAL(a, L502_Configure(handle, 0));
}

// ---------------------------------------------------------------------------
void RLCard502::Start(void)
{
	if (IsStarted)
		return;
	LoadMainSettings();
	IsStarted = true;
	LFATAL("LCard502::Start: �� ������ ��������� ������: ",
		L502_StreamsEnable(handle, L502_STREAM_ADC));

	LFATAL("LCard502::Start: �� ������ ����������: ",
		L502_StreamsStart(handle));
}

// ---------------------------------------------------------------------------
void RLCard502::Stop(void)
{
	if (!IsStarted)
		return;
	IsStarted = false;
	LFATAL("LCard502::Start: �� ������ ������������: ",
		L502_StreamsStop(handle));
}

// ---------------------------------------------------------------------------
double* RLCard502::Read(int* _size)
{
	uint32_t count;
	if (CheckError(L502_GetRecvReadyCount(handle, &count)))
	{
		*_size = -1;
		return (NULL);
	}
	count /= MainSensors;
	count *= MainSensors;
	SetRawSize(count);
	int rcv_size = L502_Recv(handle, rawi, count, RECV_TOUT);
	/* �������� ������ ���� �������� ������... */
	/* �������� ����� ���. ������, ��������������� �������
	 ������� ���, ��� ��� �� ����� ����� ����������
	 ��������� ���������� ������ */
	unsigned int firstLch;
	L502_GetNextExpectedLchNum(handle, &firstLch);
	AnsiString a="firstLch=";
	a+=firstLch;
	TPr::pr(a);
	if (CheckError(L502_GetNextExpectedLchNum(handle, &firstLch)))
	{
		*_size = -2;
		return (NULL);
	}
	if (rcv_size != (int)count)
	{
		*_size = -3;
		LastError = "������ ���������� �� ����� ������� ������������";
		return (NULL);
	}
	// ��������� ��� � ������
	unsigned int count1 = count;
	if (CheckError(L502_ProcessAdcData(handle, rawi, raw, &count1,
		L502_PROC_FLAGS_VOLT)))
	{
		*_size = -4;
		return (NULL);
	}
	if (count != count1)
	{
		*_size = -5;
		LastError =
			"������ �������������� ���������� �� ����� ������� ������������";
		return (NULL);
	}
	*_size = count;
	return (raw);
}

// ---------------------------------------------------------------------------
void RLCard502::SetRawSize(int _size)
{
	if (_size > raw_size)
	{
		delete rawi;
		delete raw;
		double k = LCard502_ADD_PERCENT;
		k /= 100;
		k += 1;
		raw_size = (int)(_size * k);
		rawi = new unsigned int[raw_size];
		raw = new double[raw_size];
	}
}

// ---------------------------------------------------------------------------
double RLCard502::GetValue(int _ch)
{
//	double* buf = new double[Parameters->OSensors];
	double buf[RLCard_parameters::others_sensors_count];
	LFATAL("RLCard502::GetValue: �� ������ �������� ��������: ",
		L502_AsyncGetAdcFrame(handle, L502_PROC_FLAGS_VOLT, 1000, buf));
	for(int i = 0, len = Parameters->others.size(); i < len; ++i)
	{
	   if(Parameters->others[i].logicalChannel == _ch)
	   {
		 return buf[i];
	   }
    }
	//double ret = -1;
//	delete buf;
	return -1;
}
// ---------------------------------------------------------------------------
