//---------------------------------------------------------------------------

#ifndef InverterH
#define InverterH
#include "MitCome/uCInv.h"
#include "Protocol.h"
#include "vcl.h"

//------------------------------------------------------------------------------
//class rotationThread;
class Inverter
{
	public:
		Inverter();
		~Inverter();
		//! @brief ������������� �������� � ���� �� ����������
		//! @param number - ����� ������ � ���������� ( 4,5,6 )
		//! @param value  - �������� � ��
		bool setParameterSpeed(int number, int value);
		//! @param number ����� ������ �� (4,5,6)
		int getParameterSpeed(int number);
		//! �������� ��������
		bool startRotation();
		//! ������������� ��������
		bool stopRotation();
		//! ��������� ��� ��������, ����� ��� �������� � ��������� ������
		bool stateRead();
		bool ResetErrors();
		bool NETManage();
	private:
	  //	CInv* inverter;
	 //	TCriticalSection* cs;
		//! ����� ������� ����� ����������� ��������� ��������� ������ 500��
	//	rotationThread *testThread;
		void OnProtocol(AnsiString _msg);
};
//------------------------------------------------------------------------------
/*
class rotationThread: public TThread
{
	private:
		void __fastcall Execute();
		CInv* inv;
		TCriticalSection* cs;
	public:
		__fastcall rotationThread(CInv* _inv,TCriticalSection* _cs);
};
*/
extern Inverter *frConverter;
//------------------------------------------------------------------------------

#endif


