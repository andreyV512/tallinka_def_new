#pragma hdrstop
#include "CSG.h"
#pragma package(smart_init)
AnsiString CSG::ToString()
{
	AnsiString a="CSG: g=";
	a+=group;
	a+=" p=";
	a+=probability;
	a+=" color=";
	a+=color;
	return(a);
}
