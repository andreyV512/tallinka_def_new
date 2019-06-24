#ifndef RLCard_parametersH
#define RLCard_parametersH
#include <vector>
#include <l502api.h>
#include "RChannel_parameters.h"
#include <IniFiles.hpp>
using namespace std;

// ---------------------------------------------------------------------------
class RLCard_parameters
{
private:
public:
	// ! ������� ��� ����� (� ����� �������� ����� ��������� ������ �� ��� � ������� �����,��)
	int RECV_TOUT;
	// ! @brief ����� �������������
	// ! @li 0 ���������� ������
	// ! @li 1 �� �������� ������� �� ������� �������������
	// ! @li 2 �� ������ ������� DI_SYN1
	// ! @li 3 �� ������ ������� DI_SYN2
	// ! @li 6 �� ����� ������� DI_SYN1
	// ! @li 7 �� ����� ������� DI_SYN2
	uint32_t syncMode;
	// ! �������� ������� ����������� �����/������ ��. ������ @link syncMode
	uint32_t syncStartMode;
	// ! ������� ����� (��.)
	double frequencyCollect;
	// ! ������� �� ����� (��.)
	double frequencyPerChannel;

	// ! ���������� ���-�� ������������ �������
	int getCountChannels()
	{
		return channels.size() + others.size();
	}

	// ! �������������� ��������� ��� ������� ������
	vector<RChannel_parameters>channels;
	// ! @brief �������������� ������
	// ! @li 0 - ��� ���������� ��������
	// ! @li 1 - ���������� ���������� ��������
	// ! @li 2 - ��� ���������� ��������
	// ! @li 3 - ���������� ���������� ��������
	// ! @li 4 - ��� ������ ���������
	// ! @li 5 - ���������� ������ ���������
	// ! @li 6 - ���������� �� �����
	vector<RChannel_parameters>others;

	int LSensors;
	int CSensors;
	int OSensors;
	static const int others_sensors_count = 3;
	// ! �����������
	RLCard_parameters()
	{
		others.resize(others_sensors_count);
	}
	void LoadSettings(TIniFile* _ini);

};
// ---------------------------------------------------------------------------
#endif
