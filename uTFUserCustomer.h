// ---------------------------------------------------------------------------

#ifndef uTFUserCustomerH
#define uTFUserCustomerH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IniFiles.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

// ---------------------------------------------------------------------------
class TFUserCustomer : public TForm
{
__published: // IDE-managed Components
	TADOTable *TUsers;
	TDBGrid *GUsers;
	TDBNavigator *NUsers;
	TDataSource *DSUsers;
	TLabel *LUsers;
	TDBGrid *GCustomers;
	TDBNavigator *NCustomers;
	TLabel *LCustomers;
	TDataSource *DSCustomers;
	TADOTable *TCustomers;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);

private: // User declarations
	 TIniFile* ini;
public: // User declarations
	__fastcall TFUserCustomer(TComponent* Owner, TIniFile* _ini);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFUserCustomer *FUserCustomer;
// ---------------------------------------------------------------------------
#endif
