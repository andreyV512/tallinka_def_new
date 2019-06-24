#ifndef ThreadOnLineH
#define ThreadOnLineH
#include "CBank.h"
#include <IniFiles.hpp>
#include "SGWork.h"

class ThreadOnLine : public TThread
{
private:
	int pauseWorkSpeed;
	int pauseStop;

	void __fastcall Execute();

	// ! ���������� �� ���������� (������ ����������)
	bool Cross;
	// ! ���������� �� ����������
	bool Linear;

	// ! ����� ��� ������� � ���������� � ������ 1
	AnsiString stext1;
	// ! ����� ��� ������� � ���������� � ������ 2
	AnsiString stext2;

	// ! ���������� �������� ��������� ������� ����� �������
	UnicodeString PrepareForWork();
	// ! ��������� ����� (���������� �������� � �.�.)
	void Finally();
	void ErrFinally(AnsiString _msg, bool* _Collect, bool* _result);

	// �������� �������� ����, ������, �����
	// vector<int> speeds;
	int InSpeed;
	int WorkSpeed;
	int OutSpeed;

	// ! ����� ��������� ���� ���� ����������
	bool OnlineCycle(void);

	int delay;
	CBank* BankCross;
	CBank* BankLine;
	UINT thread_msg;
	HWND main_handle;

	// unsigned unitBaseMMLong; //������� ���������� ����� SQ1 � ��������1 � ��
	// unsigned unitBaseMMCross; //������� ���������� ����� SQ1 � ��������2 � ��

	void Post(WPARAM _w, LPARAM _l = 0);

	bool Collect;

	TCriticalSection* cs;

	void SetStext1(AnsiString _s);
	void SetStext2(AnsiString _s);

	TEvent* calc_event;

	TIniFile* ini;

	void pr(AnsiString _msg);

	vector<double> *SGbuffer;
	bool IsBrak;
	char *updateStatusBarBottomParam;

	void __fastcall UpdateStatusBarBottom();
	SGWork sgWork;

public:
	__fastcall ThreadOnLine(bool CreateSuspended, bool _Linear,
		CBank*_BankCross, CBank*_BankLine, HWND _main_handle, UINT _thread_msg,
		TIniFile*_ini, vector<double> *_SGbuffer);
	__fastcall ~ThreadOnLine(void);
	static const WPARAM REDRAW = 0;
	static const LPARAM REDRAW_CROSS = 0;
	static const LPARAM REDRAW_LINE = 1;
	static const WPARAM COMPUTE = 1;
	static const WPARAM UPDATE_STATUS = 3;
	static const WPARAM SGDRAW = 4;
	static const WPARAM COMPLETE = 5;
	static const WPARAM NEXT_TUBE = 6;

	AnsiString GetStext1(void);
	AnsiString GetStext2(void);
	void SetCalc(bool _IsBrak);
};
// ---------------------------------------------------------------------------

#endif
