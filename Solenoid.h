// ---------------------------------------------------------------------------
#ifndef SolenoidH
#define SolenoidH
#include <System.hpp>
// ! ����� ������ � �����������
class Solenoid
{
public:
	// ! @brief ����������� � �����������
	// ! @param _lc ��������� �� L-Card, � �������� ��������� ��������
	// ! @param TypeOfControl ��� �������� - PP ��� PR
	Solenoid();//String TypeOfControl);
	bool SolenoidOn();
	bool Solenoid1U(double &);
	bool Solenoid2U(double &);
	private:
	int channelSolenoidsON;
	int channelSolinoid1;
	int channelSolinoid2;
	double solenoidTresholdU;
	// ! �������� �������� ���� ���������
 //	double getAmperage();
	// ! �������� �������� ���������� ���������
   //	double getVoltage();
	// ! ���������� �������� ����������� ���������
 //	double getResist();
	// ! ���������, �� ���������� �� ��������
 //	bool OkResist();
 //	bool OkU(void);
  //	AnsiString GetUIR(void);

private:
	// ! ����������� �������������
  //	double Devider;
	// ! ����� L-Card, �� ������� ��������� ����� ����
  //	int chAmperage;
	// ! ����� L-Card, �� ������� ��������� ����� ����������
  //	int chVoltage;
	// ! ����������� ������� �����������, ���� �������� ������� ��������
//	float AlarmLevel;
  //	float AlarmULevel;
 //	float DifULevel;
};
extern Solenoid *CrossSolenoid;
//extern Solenoid *LinearSolenoid;
#endif
