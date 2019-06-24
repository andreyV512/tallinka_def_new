#pragma hdrstop
#include "SummaryResult.h"
#include "Global.h"
#include <Series.hpp>
#include "Protocol.h"
#pragma package(smart_init)

SummaryResult::SummaryResult(int _sensors, TIniFile* _ini)
	: ResultBase((short)_sensors, _ini)
{
	SummaryResult::zones = 0;
	cut1 = cut2 = 0;

	decision = "";
}

// ---------------------------------------------------------------------------
SummaryResult::~SummaryResult()
{
	SummaryResult::zone_data.~DynamicArray();
}

// ---------------------------------------------------------------------------
TColor SummaryResult::ZoneColor(double meas)
{
	// ���������� ���� ���� � ����������� �� ���������� ���������� � ���� ����
	if (meas == 1)
		return Good;
	else if (meas == 0)
		return Brack;
	else
		return Class2;
}

// ---------------------------------------------------------------------------
void SummaryResult::PutResultOnChart(void)
{
	// ������ ��������� �� ����� �� ����� �;
	for (int j = 0; j <= Globals::max_zones; j++)
	{
		if (j < zones)
			FRM->Chart1->Series[0]->AddXY(j, 1, "", ClassColor(zone_data[j]));
		else
			FRM->Chart1->Series[0]->AddXY(j, 0, "", clWhite);
	}
}

// ---------------------------------------------------------------------------
void SummaryResult::MakeDecision()
{
	// ��������� ������� �� �����, ��������� �������� �����
	bool flag = false;
	// �������������, ��� ������� ������� ����� ������� 2-�� �������, ���� �������� ����������� ������ �����
	bool class2 = false; // ������� ����� ����� ������� 2-�� �������
	short temp = 0; // ����� �������� ������� � �����
	short tcut1 = 0; // ��������� ������ ���
	cut1 = cut2 = 0; // ����� �� ��������� ���
	decision = ""; // ������� �� �������
	if (min_good_length > 0)
	{
		for (int i = 0; i < zones; i++)
		{
			if (zone_data[i] == 2)
				temp++;
			else if (zone_data[i] == 0)
			{
				if (temp >= min_good_length)
				{
					cut2 = (short) i;
					cut1 = (short) i - temp;
					class2 = flag;
				}
				temp = 0;
				tcut1 = i + 1;
				flag = false;
			}
			else if (zone_data[i] == 1)
			{
				flag = true;
				temp++;
			}
		}

		if (temp < min_good_length && cut2 == 0 && cut1 == 0)
			decision = "����";
		else if (temp >= min_good_length)
		{
			if (flag)
				decision = "����� 2";
			else
				decision = "�����";
			cut1 = tcut1;
			cut2 = 0;
		}
		else if (cut1 > 0 || cut2 > 0)
		{
			if (class2)
				decision = "����� 2";
			else
				decision = "�����";
		}

		// ������ ����-�� ������
		if (end_cut > 0 && decision != "����")
		{
			if (cut2 == 0)
				cut2 = zones;
			int f1 = (end_cut - cut1 > 0) ? (end_cut - cut1) : (0);
			int f2 = (end_cut - zones + cut2 > 0) ? (end_cut - zones + cut2) : (0);
			if (cut2 - cut1 - f1 - f2 < min_good_length)
				decision = "����";
		}
		// �������� ��� ����������
		if (cut1 > 0)
			cut1++;
	}
	// ������ �� ������� - ����� ���� - ����� �����
	else
	{
		bool brack = false;
		for (int i = 0; i < zones; i++)
		{
			if (zone_data[i] == 0)
			{
				brack = true;
				break;
			}
			else if (zone_data[i] == 1)
				class2 = true;
		}
		if (brack)
			decision = "����";
		else if (class2)
			decision = "����� 2";
		else
			decision = "�����";
	}
}
void SummaryResult::MakeDecision2()
{

}

// ---------------------------------------------------------------------------
void SummaryResult::Bind(TFRSum* _FRM)
{
	FRM = _FRM;
}
