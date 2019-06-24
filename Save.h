//---------------------------------------------------------------------------

#ifndef SaveH
#define SaveH
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
//������ ������ �� ����� � �� ��� ����������
void SaveTubeToDB(TIniFile* _ini);
//������ ������ �� ����� � ����
void SaveTubeToFile(TIniFile* _ini);
//��������� ����� ����������� ���� � ����� � ������� ��������� ��� ���������� ���������
void CheckNumberOfFilesInDirectory(TIniFile* _ini, AnsiString _directory);
//��������� ������� ����� �� ������ � ���������� ����
int CheckCutReason(int _zone, int _module);
//��������� ��������� �� ���� �� ������
int CheckModBrack(int _module);
#endif
