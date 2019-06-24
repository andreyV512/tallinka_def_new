#ifndef ResultBaseH
#define ResultBaseH
#include <IniFiles.hpp>
#include <Graphics.hpp>
#include <vector>
using namespace std;

// ! ����� ���������� �������������
class ResultBase
{
	friend class ButterworthFilter;

private:
protected:
	// ! �����������
	ResultBase(short _sensors, TIniFile* _ini);

	TIniFile* ini;
	// ! ������ �������� �������� �� ��������
	vector<vector<double> >sensor_data;
	// ! ������ �������� �������� - �� ���� �������� , �� ���� ����� [����][������][���������]
	vector<vector<bool> >Deads;
	int ZoneLength;

public:
	// ! ����������
	virtual ~ResultBase();

	// ! ���-�� ������������ ��� � ����������
	short zones;
	// ! ������ �������� �������� �� �����
	DynamicArray<double>zone_data;

	// ! ������� ��� ���������
	void DeleteData();

	// ! ���-�� ��������� � 1 ���� 1 �������
	int meas_per_zone;
	// ! ���-�� �������� (��������)
	short sensors;
	// ! ���-�� �������� �������� (��������)
	short sensors_a;
	// ! ���� ������� ����
	TColor Dead;
	// ! ���� �����
	TColor Brack;
	// ! ���� ������� ������
	TColor Class2;
	// ! ���� ������, ������� �����
	TColor Good;

	TColor ClassColor(double _cl);

	// ! ������ ������� - [0] - ����� �����, [1] - ����� ������ 2  (%)
	DynamicArray<double>borders;

	inline vector<vector<bool> >GetDeads()
	{
		return (Deads);
	};

	inline int GetZoneLength()
	{
		return (ZoneLength);
	}
};
#endif
