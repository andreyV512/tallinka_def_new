#ifndef ThicknessResultH
#define ThicknessResultH
#include "ResultBase.h"
#include <Chart.hpp>
#include "uTFRThick.h"
class ThicknessResult : public ResultBase
{
private:
	void LoadSettings0(void);
	TFRThick* FRM;
	bool IsDefect(double _meas);
public:
	//! �����������
	ThicknessResult(int _sensors,TIniFile* _ini);
	//! ����������
	~ThicknessResult();
	//! ���������� ���� ����
	TColor ZoneColor(double meas);
	//! ������������ ��������� �� ������������ �����
	void PutResultOnChart(void);
	//! ��������� ������ � ���� (������ zone_data)
//	void SaveTubeToFile(UnicodeString FileName);
	void SaveTubeToFile(FILE *file);
	//! ��������� ������ �� ����� (zone_data)
	void LoadTubeFromFile(FILE *file);
	double LevelClass(double _level);
	void LoadSettings(void);
	void Bind(TFRThick* _FRM);
	double MinThick(int _cut0,int _cut1);
};
#endif
