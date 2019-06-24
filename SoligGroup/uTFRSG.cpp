// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSG.h"
#include "uCExecSQL.h"
#include "protocol.h"
#include "uCSelect.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSG *FRSG;

// ---------------------------------------------------------------------------
__fastcall TFRSG::TFRSG(TComponent* Owner) : TFrame(Owner)
{
	Clear();
	Edit1->Visible = false;
	pSolidGroup->Visible = true;
	block = true;
	OnChange = NULL;
}

// ---------------------------------------------------------------------------
void TFRSG::Init(TIniFile* _ini)
{
	ini=_ini;
	LoadSettings();
}

// ---------------------------------------------------------------------------
void TFRSG::LoadSettings(void)
{
	CheckBox2->Checked = ini->ReadBool("SolidGroup", "IsWorkSG", false);
	CheckBox1->Checked = ini->ReadBool("SolidGroup", "IsFix", false);
	Edit1->Text = ini->ReadString("SolidGroup", "GroupFix", "K");
	if (CheckBox1->Checked)
	{
		Edit1->Visible = true;
		pSolidGroup->Visible = false;
	}
	else
	{
		Edit1->Visible = false;
		pSolidGroup->Visible = true;
	}
	block = false;
}

// ---------------------------------------------------------------------------
void TFRSG::Set(AnsiString _SolidGroup, TColor _SolidGroupColor)
{
	pSolidGroup->Caption = _SolidGroup;
	pSolidGroup->Color = _SolidGroupColor;
}

// ---------------------------------------------------------------------------
void TFRSG::Clear()
{
	pSolidGroup->Caption = "";
	pSolidGroup->Color = clBtnFace;
}

// ---------------------------------------------------------------------------
void __fastcall TFRSG::CheckBox1Click(TObject *Sender)
{
	TCheckBox* s = (TCheckBox*)Sender;
	if (s->Checked)
	{
		Edit1->Visible = true;
		pSolidGroup->Visible = false;
	}
	else
	{
		Edit1->Visible = false;
		pSolidGroup->Visible = true;
	}
	Save();
}

// ---------------------------------------------------------------------------
void TFRSG::Save(void)
{
	if (block)
		return;
	ini->WriteBool("SolidGroup", "IsWorkSG", CheckBox2->Checked);
	ini->WriteBool("SolidGroup", "IsFix", CheckBox1->Checked);
	ini->WriteString("SolidGroup", "GroupFix", Edit1->Text);
	if (OnChange != NULL)
		OnChange(CheckBox1->Checked, Edit1->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TFRSG::Edit1Change(TObject *Sender)
{
	Save();
}

// ---------------------------------------------------------------------------
void TFRSG::Set(CSG _sg)
{
	pSolidGroup->Caption = _sg.group;
	pSolidGroup->Color = _sg.color;
}
// ---------------------------------------------------------------------------

void __fastcall TFRSG::CheckBox2Click(TObject *Sender)
{
	Save();
	// PA("Defect.Work.IsWorkSG").Write(CheckBox2->Checked);
}

// ---------------------------------------------------------------------------
AnsiString TFRSG::SGGroup(void)
{
	if (!IsSG())
		return ("?");
	if (IsFix())
		return (Edit1->Text);
	return (pSolidGroup->Caption);
}
