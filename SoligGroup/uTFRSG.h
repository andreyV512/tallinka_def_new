//---------------------------------------------------------------------------

#ifndef uTFRSGH
#define uTFRSGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSG.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
class TFRSG : public TFrame
{
__published:	// IDE-managed Components
	TPanel *pSolidGroup;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox1;
	TEdit *Edit1;
	TCheckBox *CheckBox2;
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
private:	// User declarations
	void Save(void);
	bool block;
	TIniFile* ini;
	void Set(AnsiString _SolidGroup,TColor _SolidGroupColor);
	inline bool IsFix(void)
	{
		return(CheckBox1->Checked);
	}
	inline bool IsSG(void)
	{
		return (CheckBox2->Checked);
	}
public:		// User declarations
	__fastcall TFRSG(TComponent* Owner);
	void Init(TIniFile* _ini);
	void LoadSettings(void);
	void Set(CSG _sg);
	void Clear();
	AnsiString SGGroup(void);
	typedef void (__closure * OnTFRTubeHistoryChange)(bool _IsFix,AnsiString _SGroupFix);
	OnTFRTubeHistoryChange OnChange;
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSG *FRSG;
//---------------------------------------------------------------------------
#endif
