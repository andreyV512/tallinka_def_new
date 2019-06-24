#pragma hdrstop
#include "SGWork.h"
#pragma package(smart_init)
#include "uCExecSQL.h"
#include "uCSelect.h"

SGWork::SGWork(TIniFile* _ini)
{
	IsWorkSG = _ini->ReadBool("SolidGroup", "IsWorkSG", false);
	IsFix = _ini->ReadBool("SolidGroup", "IsFix", false);
	GroupFix = _ini->ReadString("SolidGroup", "GroupFix", "K");
	if (IsWorkSG)
	{
		if (IsFix)
			csg.group = GroupFix;
	}
	CExecSQL E =
		CExecSQL(
		"update SGWork set Request=null, Answer=null, SolidGroup=null, Color=null");
}

void SGWork::SetRequest(void)
{
	if (!IsWorkSG || IsFix)
		return;
	CExecSQL E =
		CExecSQL(
		"update SGWork set Request=getdate(), Answer=null, SolidGroup=null, Color=null");
}

bool SGWork::Exec(void)
{
	if (!IsWorkSG || IsFix)
		return(true);
	CSelect S=CSelect("select SolidGroup, Color from SGWork where Answer is not null");
	if(S.Count()!=1)
		return(false);
	csg.group=S.AsAnsiString("SolidGroup");
	csg.color=(TColor)S.AsInt("Color");
	return(true);
}
