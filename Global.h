// ---------------------------------------------------------------------------

#ifndef GlobalH
#define GlobalH

#include <Classes.hpp>
// ---------------------------------------------------------------------------
/*
enum SGSource
{
	sgsLCard=0,sgsCOMPort=1,sgsNone=-1
};
*/
// ! ����� ���������� ����������
class Globals
{
public:
	// ! ������� ������� (������ 60,73 ��� 89)
	static int current_diameter;
	// ! ��� � ���� � ����� � �����������
	static String IniFileName;
	// ! ���� � ����� � �������� ��� �� � ms-dos
	static String PathFile_threshold_sg;
	// ! ����� �����
//	static AnsiString tube_number;
	// ! ����� �����
//	static bool tube_transit;

	// ! @deprecated ��������, ����� ��� ���������� �� �������
	// ! @brief ���� ���-�� ��������, �������� ��������, ����� ����������
	static const int max_sensors=16;
	// ! @deprecated ��������, ����� ��� ���������� �� �������
	// ! @brief ���� ���-�� ���, ��������, ����������
	static const int max_zones=60;
	// ! ����� �������� ����������� �������� � �������
//	static const int LinSensors=4;
	// ! ������������ ����� �������� ����������� �������� � �������
//	static const int Cross_sensors=12;
	// ! �������� ���������� � ������� �������� �������� �������
	static const int defaultRotParameter=4;
private:

};

int Globals::current_diameter=2;
String Globals::PathFile_threshold_sg="..\\..\\Settings\\";
String Globals::IniFileName="..\\..\\Settings\\SettingsDefectoscope.ini";
//AnsiString Globals::tube_number="";
//bool Globals::tube_transit;

// -------------------------------------------------------------------------------------------
// ! ����� ��������, ����������� � ������������ �������
class SystemConst
{
public:
	// !	������� �� �������� ������� � ���������� �������
	static bool HideInGain;
	// ! ����� �� ����������� ������ ����������� �������� ��������
	static bool isCrossDigitalFilter;
	// ! ����� �� ����������� ������ ����������� �������� ��������
	static bool isLinearDigitalFilterIn;
	static bool isLinearDigitalFilterOut;

	// ! ��������� ���������� �������������� �������
	static void SetSystemConstants();

};
bool SystemConst::isCrossDigitalFilter=true;
bool SystemConst::isLinearDigitalFilterIn=true;
bool SystemConst::isLinearDigitalFilterOut=true;
//bool SystemConst::ComWithASU=false;
bool SystemConst::HideInGain=false;

// ---------------------------------------------------------------------------
#endif
