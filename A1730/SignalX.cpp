// ---------------------------------------------------------------------------
#pragma hdrstop
#include "SignalX.h"
#include<SysUtils.hpp>
#include"protocol.h"
#include "uFunctions.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CSignal::CSignal(AnsiString _name, bool _in, int _index, tagOnSet _OnSet,
	TCriticalSection* _cs, tagOnWait _OnWait)
{
	name = _name;
	in = _in;
	index = _index;
	value = false;
	value_prev = false;
	OnSet = _OnSet;
	OnWait = _OnWait;
	cs = _cs;
	last_changed = GetTickCount();
}

bool CSignal::Get(void)
{
	bool ret;
	cs->Enter();
	{
		ret = value;
	} cs->Leave();
	return (ret);
}

bool CSignal::WasConst(bool _value, DWORD _period)
{
	bool ret;
	DWORD last_changed1;
	cs->Enter();
	{
		ret = value;
		last_changed1 = last_changed;
	} cs->Leave();
	if (last_changed1 + _period < GetTickCount())
	{
		if (ret == _value)
			return (true);
	}
	return (false);
}

bool CSignal::WasConst0(bool _value, DWORD _period)
{
	DWORD tick=GetTickCount();
	if (last_changed + _period < tick)
	{
		if (value == _value)
		{
//			AnsiString a;
//			a="WasConst0 ";
//			a+=name;
//			a+=" ";
//			a+=last_changed;
//			a+="+";
//			a+=_period;
//			a+=">";
//			a+=tick;
//			TPr::pr(a);
			return (true);
		}
	}
	return (false);
}

void CSignal::Set0(bool _value)
{
	if (in)
	{
		AnsiString a = "Signal::Set: ������� ��������� ������� ������: ";
		a += name;
		FATAL(a);
	}
	if(_value != value)
		last_changed=GetTickCount();
	value_prev = value;
	value = _value;
	OnSet();
//	AnsiString a;
//	a="*** ";
//	a+=name;
//	a+=" set ";
//	a+=value?"true ":"false ";
//	a+=last_changed;
//	TPr::pr(a);
}

void CSignal::Set(bool _value)
{
	if (in)
	{
		AnsiString a = "Signal::Set: ������� ��������� ������� ������: ";
		a += name;
		FATAL(a);
	}
	cs->Enter();
	{
		if(_value != value)
			last_changed=GetTickCount();
		value_prev = value;
		value = _value;
		OnSet();
	} cs->Leave();
//	AnsiString a;
//	a="*** * ";
//	a+=name;
//	a+=" set ";
//	a+=value?"true ":"false ";
//	a+=last_changed;
//	TPr::pr(a);
}

bool CSignal::Wait(bool _value, DWORD _tm)
{
	if (!in)
	{
		AnsiString a = "Signal::Wait: ������� ��������� �������� ������: ";
		a += name;
		FATAL(a);
	}
	if (Get() == _value)
		return (true);
	return (OnWait(_value, this, _tm));
}
