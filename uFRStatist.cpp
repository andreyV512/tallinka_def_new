//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFRStatist.h"
#include "uCSelect.h"
#include "uCExecSQL.h"
#include "uFunctions.h"
#include "Protocol.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRStatist *FRStatist;
//---------------------------------------------------------------------------
__fastcall TFRStatist::TFRStatist(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void TFRStatist::Add(bool _brak)
{
	TPr::pr("TFRStatist: �������� �����");
	AnsiString SQL="update Uran.Statist set tubes=tubes+1";
	if(_brak)
		SQL+=",brak=brak+1";
	CExecSQL E(SQL);
	if(E.RowsAffected()!=1)
		FATAL("TFRStatist::Add: �� ���� �������� ����������");
	Load();
}
//---------------------------------------------------------------------------
void TFRStatist::Load(void)
{
	CSelect S("select * from Uran.Statist");
	if(S.Count()!=1)
		FATAL("TFRStatist::Load: �� ���� �������� ����������");
	int tubes=S.AsInt("tubes");
	STTubes->Caption=tubes;
	int brak=S.AsInt("brak");
	STGood->Caption=tubes-brak;
	STBrak->Caption=brak;
}
//---------------------------------------------------------------------------
void __fastcall TFRStatist::Button1Click(TObject *Sender)
{
	TDateTime StatTime = Date() + Time();
	ini->WriteDateTime("Default","StatistFlushTime",StatTime);
	Button1->Hint = "��������� �����: " + DateTimeToStr(StatTime);
	TPr::pr("TFRStatist: �������� �� ������");
	CExecSQL E("update Uran.Statist set tubes=0,brak=0");
	if(E.RowsAffected()!=1)
		FATAL("TFRStatist::Button1Click: �� ���� �������� ����������");
	Load();
}
//---------------------------------------------------------------------------
void TFRStatist::Init(TIniFile* _ini)
{
	ini = _ini;
	Load();
	Button1->Hint = "��������� �����: "
		+ DateTimeToStr(ini->ReadDateTime("Default","StatistFlushTime",0));
}

