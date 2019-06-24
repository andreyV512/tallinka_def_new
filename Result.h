// ---------------------------------------------------------------------------
#ifndef ResultH
#define ResultH
#include "ResultBase.h"
#include <vector>
#include "uFViewZoneS.h"
#include "uFViewZoneD.h"
#include "uFRViewZone.h"
#include "CBank.h"
using namespace std;

// ! ����� ���������� �������������
class Result : public ResultBase
{
	friend class ButterworthFilter;

private:
	// ! ��������������� ������� ��� ����������
	void _medianfilter(double* signal, double* result, int N);

	// ! ������ ���� ��� ��������� ����������
	int WidthMedianFilter;
	// ! ���� 0 �� ������� ��������, ���� 1 ��������
	int TypeView;
	// ! ���� ������ ������ ����������
	int shiftZone;
	// ! ����� �������
	int sens;
	// ! ���� ������ ������ ���������� ��� ������� ����������
	int startZone;
	// ! ���������� ��� ������ ����������
	int countZone;

	void ComputeFiltered(int _zone, int _sensor, bool _isLinear);

	void CalcDeadsZoneBegin(int _ZoneLength, int _Begin, int _zone,
		int _ZoneSize);
	void CalcDeadsEnd(int _ZoneLength, int _End, int _zones);

protected:
	// ! �����������
	Result(int _sensors, TIniFile* _ini, TComponent* _Owner);

	// ! ����� ��� ��������� ��������� �� ������� (0-������ �� ������, 1-�������� ������)
	TFViewZoneD* SensorFormD;
	TFViewZoneS* SensorFormS;
	// ! ���-�� ��������� ������ ������� ����
	double meas_dead_zone_start;
	// ! ���-�� ��������� ������ ������� ����
	double meas_dead_zone_finish;
	vector<double>gain;

	virtual void PutDataOnChartX(TFViewZoneD* _F, int zone, int sensor);

	virtual void PutSourceDataOnChartX(TFViewZoneS* _F, int zone, int sensor)
	{
	};


	vector<vector<vector<double> > >Median_Data;
	// ! ����� ����
	int zone_length;
	// ! ������ �������������� �������� - �� ���� �������� , �� ���� ����� [����][������][���������]
	vector<vector<vector<double> > >FilteredOut_Data;
	vector<vector<vector<double> > >FilteredIn_Data;

	virtual void ComputeSensorClass(int _zone, int _sensor);
	double AbsMaxV(vector<double>_v, int _zone);
	double LevelClass(double _level);
	// ! ������� ���� �� ������� ��������� ���� � �����������
	void __fastcall SeriesDblClick(TChartSeries *Sender, int ValueIndex,
		TMouseButton Button, TShiftState Shift, int X, int Y);

	// ����.������.���������
	vector<vector<vector<double> > >Source_Data;
	bool isMedianFilter;

	// ! ������� ������, �������� ������� "zone_data" � "sensor_data"
	void ComputeZoneData(bool isLinear);
	void LoadSettings(void);
public:
	// ! ����������
	virtual ~Result();
	// ! @brief ��������� ������
	// ! @param signal - �������� ������
	// ! @param result - �������������� ������
	// ! @param N - ����� �������
	void medianfilter(double* signal, double* result, int N);

	// ! ������� ���� � ������ �����(mm.)
	int dead_zone_start;
	// ! ̸����� ���� � ����� �����(mm.)
	int dead_zone_finish;

	// ! ������������ ������ �� ������� data �� ������ ���
	void FillData(vector<vector<double> >sourceData);
	// ! ������������ ������ �� ������� data �� ������ ���
	void FillDataR(vector<vector<double> > * _SD);
	// ! ���������� ���� ���������/�������/����
	TColor ZoneColor(double meas, bool _IsDead);
	// ! ������� ��� ���������
	void DeleteData();
	// ! ������������� ��� �������� ��������
	void SetGains(vector<double>_Gain);
	// ! ������������� �������� 1 ����������� �������
	void SetSensorGain(double _gain, int sensor);
	// ! ��������� ������������ ���� � �������� �������
	// ! ������ True ���� ���� ����������, ����� false
	bool AddZone(vector<vector<double> >new_data, bool isLinear = false);
	// ! ������������� ���������� ���������� ��������
	void AutoCalibration(int zone);
	void PutDataOnFrame(TFRViewZone* _fr, int zone, int sensor,
		TColor zoneColor);
	// ! ��������� ������ �� ����� � ���� (���������)
//	void SaveTubeToFile(UnicodeString FileName);
	void SaveTubeToFile(FILE *file);
	// ! �������� ������ �� ����� �� ����� (����������)
	void LoadTubeFromFile(FILE *file);
	bool AddBankZone(CBank* _bank, bool _isLinear);
	// �����������
	// ! ���������� ��������������� ������
	vector<vector<vector<double> > >GetFilteredOut_Data();
	vector<vector<vector<double> > >GetFilteredIn_Data();
	// ! ���������� ������������ �������� ��������
	vector<double>GetGain();
	double GetSensorGain(int sensor);
	// ! ���������� ������ � ������� �����
	vector<vector<bool> >GetDeads();
	// ! ���������� ����� ����
	int GetZoneLength();
	// -----
	//���������� �������������� ��������
	void Calibrate(int _zone, int _sensor,bool* _mb);
	double GetMaxZoneSensor(int _zone, int _sensor);
	//������ ��������� ������� �������

};
#endif
