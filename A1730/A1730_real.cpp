#pragma hdrstop
#include "A1730_real.h"
#include <SysUtils.hpp>
#include "Protocol.h"
#include "uFunctions.h"
#pragma package(smart_init)
/*
A1730_real::A1730_real(int _DevNum)
{
	startPort = 0;
	portCount = 4;
	ErrorCode errorCode;
	AccessMode AM = ModeWrite;
	device = NULL;
	errorCode = BDaqDevice::Open(_DevNum, AM, device);
	if (BioFailed(errorCode))
		FATAL("A1730_real::A1730_real: �� ������ ������� ����� Advantech1730");
	errorCode = device->GetModule(0, dio); // Get Dio Module
	if (errorCode == Success && ReadOnly)
		FATAL("A1730_real::A1730_real: �� ������ ������� ����� Advantech1730");
}

A1730_real::~A1730_real(void)
{
	device->Close();
}

DWORD A1730_real::Read(void)
{
	if(device==NULL)
		return(0);
	BYTE buf[4];
	ErrorCode errorcode = dio->DiRead(startPort, portCount, buf);
	if (dio->DiRead(startPort, portCount, buf) != Success)
		FATAL("A1730::ReadIn: �� ���� ��������� �����");
	DWORD v = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
	return (v);
}

DWORD A1730_real::ReadOut(void)
{
	if(device==NULL)
		return(0);
	BYTE buf[4];
	if (dio->DoRead(startPort, portCount, buf) != Success)
		FATAL("A1730::ReadOut: �� ���� ��������� �����");
	DWORD bufOut = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
	return (bufOut);
}

void A1730_real::Write(DWORD _v)
{
	if(device==NULL)
		return;
	BYTE buf[4];
	buf[0] = _v & 0xFF;
	buf[1] = _v >> 8 & 0xFF;
	buf[2] = _v >> 16 & 0xFF;
	buf[3] = _v >> 24 & 0xFF;
	if (dio->DoWrite(startPort, portCount, buf) != Success)
		FATAL("A1730::Write: �� ���� �������� �� �����");
}
void A1730_real::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}
*/
A1730_real::A1730_real(int _DevNum)
{
	ErrorCode errorCode;
	instantDiCtrl = AdxInstantDiCtrlCreate();
	instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(_DevNum);
	errorCode = instantDiCtrl->setSelectedDevice(devInfo);
	if (BioFailed(errorCode))
		throw(Exception
		("A1730::A1730: �� ������ ������� ����� Advantech1730"));
	errorCode = instantDoCtrl->setSelectedDevice(devInfo);
	if (BioFailed(errorCode))
		throw(Exception
		("A1730::A1730: �� ������ ������� ����� Advantech1730"));
}

A1730_real::~A1730_real(void)
{
	instantDiCtrl->Dispose();
	instantDoCtrl->Dispose();
}

DWORD A1730_real::Read(void)
{
	DWORD buf;
	ErrorCode errorcode  = instantDiCtrl->Read(0,4, (unsigned char *)&buf);
	if (errorcode != Success) throw(Exception("A1730::ReadIn: �� ���� ��������� �����"));
	return buf;
}

DWORD A1730_real::ReadOut(void)
{
	DWORD buf;
	ErrorCode errorcode  = instantDoCtrl->Read(0, 4, (unsigned char *)&buf);
	if (errorcode != Success) throw(Exception("A1730::ReadIn: �� ���� ��������� �����"));
	return buf;
}

void A1730_real::Write(DWORD _v)
{
	ErrorCode errorcode  = instantDoCtrl->Write(0,4, (unsigned char *)&_v);
	if (errorcode != Success) throw(Exception("A1730::Write: �� ���� �������� �� �����"));
}

void A1730_real::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}
