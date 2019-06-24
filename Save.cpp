// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Save.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "uCExecSQL.h"
#include "uCExecute.h"
#include "uCSelect.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "ADCSettings.h"
#include "Singleton.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)

// ---------------------------------------------------------------------------
void SaveTubeToDB(TIniFile* _ini)
{
	TIniFile* ini = _ini;
	AnsiString SQL;
	AnsiString ret;

	AnsiString Customer = ini->ReadString("Default", "Customer", "?");
	AnsiString User = ini->ReadString("Default", "User", "?");


	CExecSQL* E;
	// ��������� ����� �������
	CSelect S1("SELECT COUNT(TubeNum) as nn from dbo.TubesStat");
	if (S1.AsInt("nn") > 60000)
	{
		// ������� ����� ������ ������
		CSelect S2("Select top 1 * from dbo.TubesStat order by IDTube ASC");
		// ������� ������ ������ � ���� �������

		SQL = "Delete from dbo.ZonesStat where TubeNum=";
		SQL += S2.AsInt("TubeNum");
		E = new CExecSQL(SQL);
		delete E;

		SQL = "Delete from dbo.TubesStat where TubeNum=";
		SQL += S2.AsInt("TubeNum");
		E = new CExecSQL(SQL);
		delete E;
	}

	// ���� ��������� ����� �����
	CSelect S3("Select top 1 * from dbo.TubesStat order by IDTube Desc");
	// �������� ����� ����� �����
	int TubeNum = 0;
	TubeNum = S3.AsInt("TubeNum");
	if (TubeNum == 0 || TubeNum == 200000)
		TubeNum = 1;
	else
		TubeNum++;

	// ������� ������ ������ � ���� �������
	SQL = "Delete from dbo.ZonesStat where TubeNum=";
	SQL += TubeNum;
	E = new CExecSQL(SQL);
	delete E;

	SQL = "Delete from dbo.TubesStat where TubeNum=";
	SQL += TubeNum;
	E = new CExecSQL(SQL);
	ret = E->IsOk();
	delete E;

	// ������ ����� ������ �����
	SQL = "insert into dbo.TubesStat (TubeNum,DateTime,TypeSize,Result,SolidGroup,";
	SQL += "ThickBrackBorder,NumOfZones,Cut1,Cut2,Defectoscoper";
	// ---
	SQL += ",C11Reas,C12Reas,C13Reas,C21Reas,C22Reas,C23Reas,Mod1Brack,Mod2Brack,Mod3Brack";
	// ---
	SQL += ",Customer) values(";
	SQL += IntToStr(TubeNum);
	SQL += ",'";
	SQL += DateTimeToStr(Date() + Time());
	SQL += "','";
	AnsiString sect = "Type_" + ini->ReadString("Default", "TypeSize", "1");
	SQL += ini->ReadString("Default", "TypeSize", "1");
	SQL += "','";
	SQL += Singleton->SumResult->decision;
	SQL += "','";
	SQL += Singleton->currentSolidGroup.group;
	SQL += "',";
	AnsiString ss;
	double minThick = Singleton->ThResult->MinThick(Singleton->SumResult->cut1,
		Singleton->SumResult->cut2);
	if (minThick < 0 || minThick > 7.00)
		minThick = 5.5;
	ss.printf("%0.2f,", minThick);
	SQL += ss;
	SQL += IntToStr(Singleton->SumResult->zones);
	SQL += ",";
	SQL += IntToStr(Singleton->SumResult->cut1);
	SQL += ",";
	SQL += IntToStr(Singleton->SumResult->cut2);
	SQL += ",'";
	SQL += User;
	// ---
	SQL += "',";
	if (Singleton->SumResult->cut1 >= 1)
	{
		SQL += CheckCutReason(Singleton->SumResult->cut1 - 1, 1);
		// �������� �� 1 ����
		SQL += ",";
		SQL += CheckCutReason(Singleton->SumResult->cut1 - 1, 2);
		// �������� �� 1 ����
		SQL += ",";
		SQL += CheckCutReason(Singleton->SumResult->cut1 - 1, 3);
		// �������� �� 1 ����
	}
	else
		SQL += "0,0,0";
	SQL += ",";
	if (Singleton->SumResult->cut2 >= 1)
	{
		SQL += CheckCutReason(Singleton->SumResult->cut2 + 1, 1);
		SQL += ",";
		SQL += CheckCutReason(Singleton->SumResult->cut2 + 1, 2);
		SQL += ",";
		SQL += CheckCutReason(Singleton->SumResult->cut2 + 1, 3);
	}
	else
		SQL += "0,0,0";
	SQL += ",";
	SQL += CheckModBrack(1);
	SQL += ",";
	SQL += CheckModBrack(2);
	SQL += ",";
	SQL += CheckModBrack(3);
	SQL += ",'";
	SQL += Customer;
	SQL += "')";
	TPr::pr(SQL);
	E = new CExecSQL(SQL);
	ret = E->IsOk();
	delete E;
	if (ret != "Ok")
	{
		TPr::pr(AnsiString("SaveTubeToDB: ") + ret);
		wchar_t wstr[500];
		ret.WideChar(wstr, 500);
		Application->MessageBoxW(wstr, L"������", MB_ICONERROR | MB_OK);
	}
	else
	{
		// ���� ����� ����� �����
		CSelect S4("Select top 1 * from dbo.TubesStat order by IDTube Desc");
		int IDTube = 0;
		IDTube = S4.AsInt("IDTube");
		if (IDTube > 0)
		{
			// ������ ����� ������ �� �����
			// ����������
			SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
			SQL += "Zone1,Zone2,Zone3,Zone4,Zone5,Zone6,Zone7,Zone8,Zone9,Zone10,";
			SQL += "Zone11,Zone12,Zone13,Zone14,Zone15,Zone16,Zone17,Zone18,Zone19,Zone20,";
			SQL += "Zone21,Zone22,Zone23,Zone24,Zone25,Zone26,Zone27,Zone28,Zone29,Zone30,";
			SQL += "Zone31,Zone32,Zone33,Zone34,Zone35,Zone36,Zone37,Zone38,Zone39,Zone40,";
			SQL += "Zone41,Zone42,Zone43,Zone44,Zone45,Zone46,Zone47,Zone48,Zone49,Zone50,";
			SQL += "Zone51,Zone52,Zone53,Zone54,Zone55,Zone56,Zone57,Zone58,Zone59,Zone60) values(";
			SQL += IDTube;
			SQL += ",";
			SQL += TubeNum;
			SQL += ",'����������'";
			int NumOfZones = Singleton->CrossResult->zones;
			int i;
			for (i = 0; i < NumOfZones; i++)
			{
				SQL += ",";
				SQL += Singleton->CrossResult->zone_data[i];
			}
			for (; i < 60; i++)
			{
				SQL += ",";
				SQL += 5; // ��� ������ (�� ������ �����)
			}
			SQL += ")";
			TPr::pr(SQL);
			E = new CExecSQL(SQL);
			ret = E->IsOk();
			delete E;
			if (ret != "Ok")
			{
				TPr::pr(AnsiString("SaveTubeToDB: ") + ret);
			}

			// ����������
			NumOfZones = Singleton->LinearResult->zones;
			if (NumOfZones > 0)
			{
				SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
				SQL += "Zone1,Zone2,Zone3,Zone4,Zone5,Zone6,Zone7,Zone8,Zone9,Zone10,";
				SQL += "Zone11,Zone12,Zone13,Zone14,Zone15,Zone16,Zone17,Zone18,Zone19,Zone20,";
				SQL += "Zone21,Zone22,Zone23,Zone24,Zone25,Zone26,Zone27,Zone28,Zone29,Zone30,";
				SQL += "Zone31,Zone32,Zone33,Zone34,Zone35,Zone36,Zone37,Zone38,Zone39,Zone40,";
				SQL += "Zone41,Zone42,Zone43,Zone44,Zone45,Zone46,Zone47,Zone48,Zone49,Zone50,";
				SQL += "Zone51,Zone52,Zone53,Zone54,Zone55,Zone56,Zone57,Zone58,Zone59,Zone60) values(";
				SQL += IDTube;
				SQL += ",";
				SQL += TubeNum;
				SQL += ",'����������'";
				for (i = 0; i < NumOfZones; i++)
				{
					SQL += ",";
					SQL += Singleton->LinearResult->zone_data[i];
				}
				for (; i < 60; i++)
				{
					SQL += ",";
					SQL += 5; // ��� ������ (�� ������ �����)
				}
				SQL += ")";
				TPr::pr(SQL);
				E = new CExecSQL(SQL);
				ret = E->IsOk();
				delete E;
				if (ret != "Ok")
				{
					TPr::pr(AnsiString("SaveTubeToDB: ") + ret);
				}
			}
			// ����������
			NumOfZones = Singleton->ThResult->zones;
			if (NumOfZones > 0)
			{
				SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
				SQL += "Zone1,Zone2,Zone3,Zone4,Zone5,Zone6,Zone7,Zone8,Zone9,Zone10,";
				SQL += "Zone11,Zone12,Zone13,Zone14,Zone15,Zone16,Zone17,Zone18,Zone19,Zone20,";
				SQL += "Zone21,Zone22,Zone23,Zone24,Zone25,Zone26,Zone27,Zone28,Zone29,Zone30,";
				SQL += "Zone31,Zone32,Zone33,Zone34,Zone35,Zone36,Zone37,Zone38,Zone39,Zone40,";
				SQL += "Zone41,Zone42,Zone43,Zone44,Zone45,Zone46,Zone47,Zone48,Zone49,Zone50,";
				SQL += "Zone51,Zone52,Zone53,Zone54,Zone55,Zone56,Zone57,Zone58,Zone59,Zone60) values(";
				SQL += IDTube;
				SQL += ",";
				SQL += TubeNum;
				SQL += ",'����������'";
				for (i = 0; i < NumOfZones; i++)
				{
					SQL += ",";
					SQL += Singleton->ThResult->LevelClass
						(Singleton->ThResult->zone_data[i]);
				}
				for (; i < 60; i++)
				{
					SQL += ",";
					SQL += 5; // ��� ������ (�� ������ �����)
				}
				SQL += ")";
				TPr::pr(SQL);
				E = new CExecSQL(SQL);
				ret = E->IsOk();
				delete E;
				if (ret != "Ok")
				{
					TPr::pr(AnsiString("SaveTubeToDB: ") + ret);
				}
			}
		}
	}

}

// ----------------------------------------------------------------------------
void SaveTubeToFile(TIniFile* _ini)
{
	TIniFile* ini = _ini;
	AnsiString DirPath = ini->ReadString("OtherSettings", "TubePath",
		"d:\RAG\Defectoscope\Tubes");
	// ��������� ����� ����������� ���� � ������� �������� ������, ���� �� ������ ���������
	CheckNumberOfFilesInDirectory(ini, DirPath);

	// ��������� �������� ��� ����� �����
	AnsiString FileName = DirPath + "\\Tube_";
	time_t t;
	time(&t);
	tm ltm = *localtime(&t);
	AnsiString fn;
	FileName.cat_printf("%.2d%.2d%.2d_%.2d%.2d%.2d.dkb", ltm.tm_year - 100,
		ltm.tm_mon + 1, ltm.tm_mday, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
	TPr::pr(FileName);
	// ������� ������ ����, ����� �������� � ���� ��������� ������
	try
	{
		FILE* file = fopen(FileName.c_str(), "wb");
		if (file == NULL)
		{
			AnsiString a = "Save: �� ���� ������� ���� ��� ������: ";
			a += FileName;
			FATAL(a);
		}
		// FILE *file;
		// file = fopen(FileName.c_str(), "a");
		// if (file == NULL)
		// {
		// AnsiString a =
		// "Save: �� ���� ������� ���� ��� ������: ";
		// a += FileName;
		// FATAL(a);
		// }
		// fclose(file);
		// // ���������� ������
		// Singleton->CrossResult->SaveTubeToFile(FileName);
		// // ���������� ������
		// Singleton->LinearResult->SaveTubeToFile(FileName);
		// // ������������� (������ zone_data)
		// Singleton->ThResult->SaveTubeToFile(FileName);
		// //��������� ������ � �������� ��� ������������
		// ADCSettForm->SaveTubeSettingsToFile(FileName);
		// ���������� ������
		Singleton->CrossResult->SaveTubeToFile(file);
		// ���������� ������
		Singleton->LinearResult->SaveTubeToFile(file);
		// ������������� (������ zone_data)
		Singleton->ThResult->SaveTubeToFile(file);
		// ��������� ������ � �������� ��� ������������
		ADCSettForm->SaveTubeSettingsToFile(file);
		fclose(file);
	}
	catch (...)
	{
		Application->MessageBoxW(L"�� ������� ��������� ����", L"������",
			MB_ICONERROR | MB_OK);
	}
}

// -----------------------------------------------------------------------------
void CheckNumberOfFilesInDirectory(TIniFile* _ini, AnsiString _directory)
{
	TIniFile* ini = _ini;
	HANDLE dir;
	WIN32_FIND_DATA file_data;
	wchar_t wdirect[256];
	AnsiString directory = _directory + "/*";
	directory.WideChar(wdirect, 256);
	if ((dir = FindFirstFile(wdirect, &file_data)) == INVALID_HANDLE_VALUE)
		return; /* ������ �� ������� */

	int count = 0; // ����� ������ � ��������
	AnsiString oldestTubeName = ""; // ��� ������ ������� �����
	char oldestTubeTime[26]; // ����� ��������� ������ ������� �����
	char timebuf[26]; // ����� ��������� �������� �����
	struct _stat buf; // ������ �������� �����
	int result; // ��������� ������ ���������� �����
	AnsiString Proto; // ����� ��� ���������

	do
	{
		AnsiString file_name = file_data.cFileName;
		AnsiString full_file_name = _directory + "/" + file_name;
		const bool is_directory =
			(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[1] == '.')
			continue;

		if (is_directory)
			continue;

		count++;
		result = _stat(full_file_name.c_str(), &buf);
		if (result != 0)
		{
			Proto = "�� ����� �������� ������ �� ����� � ������: " +
				full_file_name;
			TPr::pr(Proto);
			continue;
		}
		else
		{
			ctime_s(timebuf, 26, &buf.st_mtime);
			if (oldestTubeName == "")
				// ��������� ������ ���������� ����� ����� ������
			{
				for (int i = 0; i < 26; i++)
					oldestTubeTime[i] = timebuf[i];
				oldestTubeName = full_file_name;
			}
			else
			{
				if (oldestTubeTime < timebuf)
					// ��������� ��� ���������� ����� ������
				{
					for (int i = 0; i < 26; i++)
						oldestTubeTime[i] = timebuf[i];
					oldestTubeName = full_file_name;
				}
			}
		}
	}
	while (FindNextFile(dir, &file_data));
	FindClose(dir);
	// ��������� �������� ����� ����
	if (!ini->ValueExists("OtherSettings", "MaxCountSaveTubes"))
		ini->WriteInteger("OtherSettings", "MaxCountSaveTubes", 1000);
	int maxCount = ini->ReadInteger("OtherSettings", "MaxCountSaveTubes", 1000);
	if (count >= maxCount) // ���� �������� �������� - ������� ����� ������
	{
		if (remove(oldestTubeName.c_str()))
		{
			Proto = "�� ����� ������� ����: " + oldestTubeName;
			TPr::pr(Proto);
			return;
		}
	}
}

// --------------------------------------------------------------------------
int CheckCutReason(int _zone, int _module)
{
	// ��������� ������ ���� (����� ������������ � ������
	// ��� ����������� �������� � ����� ����)
	int zone = _zone - 1;
	if ((Singleton->SumResult->zones < zone) || (zone < 0)) // ������
	{
		TPr::pr("������: ��� �� ��������� �����");
		return 0;
	}
	switch (_module)
	{
	case 1:
		{
			if (Singleton->ThResult->zones > 0)
			{
				if (Singleton->ThResult->LevelClass
					(Singleton->ThResult->zone_data[zone]) == 0)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
	case 2:
		{
			if (Singleton->CrossResult->zones > 0)
			{
				if (Singleton->CrossResult->zone_data[zone] == 0)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
	case 3:
		{
			if (Singleton->LinearResult->zones > 0)
			{
				if (Singleton->LinearResult->zone_data[zone] == 0)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
	default:
		{
			TPr::pr("������: �� ��������� ������ ��� �������� ����");
			return 0;
		}
	}
}

// --------------------------------------------------------------------------
int CheckModBrack(int _module)
{
	switch (_module)
	{
	case 1:
		{
			if (Singleton->ThResult->zones > 0)
			{
				for (int i = 0; i < Singleton->ThResult->zones; ++i)
				{
					if (Singleton->ThResult->LevelClass
						(Singleton->ThResult->zone_data[i]) == 0)
						return 1; // ���� - ����������
				}
				return 0;
			}
			else
				return 0;
		}
	case 2:
		{
			if (Singleton->CrossResult->zones > 0)
			{
				for (int i = 0; i < Singleton->CrossResult->zones; ++i)
				{
					if (Singleton->CrossResult->zone_data[i] == 0)
						return 1; // ���� - ����������
				}
				return 0;
			}
			else
				return 0;
		}
	case 3:
		{
			if (Singleton->LinearResult->zones > 0)
			{
				for (int i = 0; i < Singleton->LinearResult->zones; ++i)
				{
					if (Singleton->LinearResult->zone_data[i] == 0)
						return 1; // ���� - ����������
				}
				return 0;
			}
			else
				return 0;
		}
	default:
		{
			TPr::pr(
				"������: �� ��������� ������ ��� �������� ������� ��������");
			return 0;
		}
	}
}
// --------------------------------------------------------------------------
