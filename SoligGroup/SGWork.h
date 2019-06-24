#ifndef SGWorkH
#define SGWorkH
#include "CSG.h"
#include <IniFiles.hpp>

class SGWork
{
	bool IsWorkSG;
	bool IsFix;
	AnsiString GroupFix;

public:
	SGWork(TIniFile* _ini);
	void SetRequest(void);
	bool Exec(void);
	CSG csg;
};
#endif
