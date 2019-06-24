#ifndef SummaryResultH
#define SummaryResultH
#include "ResultBase.h"
#include <Chart.hpp>
#include "uTFRSum.h"
class SummaryResult : public ResultBase
{
private:
	TFRSum* FRM;
public:
	//! �����������
	SummaryResult(int _sensors,TIniFile* _ini);
	//! ����������
	~SummaryResult();
	//! ����� ���� ���� 1 � 2
	short cut1,cut2;
	//! ����������� ������ �������
	short min_good_length;
	//! ������� � ����� ������ �����
	short end_cut;
	//! ������� � ����� (�����, ����, ����� 2)
	String decision;
	//! ���������� ���� ����
	TColor ZoneColor(double meas);
	// ������ ��������� �� �����
	void PutResultOnChart(void);
	//! ��������� ������� �� ���� ����� � ��������� ���� ������
	void MakeDecision();
	void MakeDecision2();
	void Bind(TFRSum* _FRM);
};
#endif
