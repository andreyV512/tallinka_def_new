//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFUserCustomer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "uFunctions.h"
#include "uCDBS.h"

TFUserCustomer *FUserCustomer;
//---------------------------------------------------------------------------
__fastcall TFUserCustomer::TFUserCustomer(TComponent* Owner, TIniFile* _ini)
	: TForm(Owner)
{
	ini=_ini;
}
//---------------------------------------------------------------------------
void __fastcall TFUserCustomer::FormCreate(TObject *Sender)
{
	LoadFormPos(this,ini);
	TUsers->Connection=DBS->Connection();
	TUsers->Active=true;
	TCustomers->Connection=DBS->Connection();
	TCustomers->Active=true;
	AnsiString val=ini->ReadString("Default","User","Неизвестный");
	for(;;)
	{
 		if(TUsers->Eof)
			break;
		if(TUsers->FieldByName("Name")->AsAnsiString==val)
			break;
		TUsers->Next();
	}
	val=ini->ReadString("Default","Customer","Неизвестный");
	for(;;)
	{
		if(TCustomers->Eof)
			break;
		if(TCustomers->FieldByName("Name")->AsAnsiString==val)
			break;
		TCustomers->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFUserCustomer::FormClose(TObject *Sender, TCloseAction &Action)
{
	SaveFormPos(this,ini);
	AnsiString val=TUsers->FieldByName("Name")->AsString;
	if(val!=NULL)
		ini->WriteString("Default","User",val);
	val=TCustomers->FieldByName("Name")->AsString;
	if(val!=NULL)
		ini->WriteString("Default","Customer",val);

}
//---------------------------------------------------------------------------
void __fastcall TFUserCustomer::FormResize(TObject *Sender)
{
	int space=3;
	int a0=space;
	int a1=ClientWidth/2+space;

	LUsers->Left=space;
	GUsers->Left=space;
	NUsers->Left=space;
	GUsers->Width=ClientWidth/2-space*2;

	LCustomers->Left=a1;
	GCustomers->Left=a1;
	NCustomers->Left=a1;
	GCustomers->Width=ClientWidth/2-space*2;

	NUsers->Top=ClientHeight-NUsers->Height-space;
	GUsers->Height=NUsers->Top-space-GUsers->Top;

	NCustomers->Top=NUsers->Top;
	GCustomers->Height=GUsers->Height;


}
//---------------------------------------------------------------------------
