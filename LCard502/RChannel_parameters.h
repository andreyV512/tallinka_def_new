#ifndef RChannel_parametersH
#define RChannel_parametersH
//---------------------------------------------------------------------------
class RChannel_parameters
{
public:
	RChannel_parameters()
	{
		range = 0;
		logicalChannel = 0;
		collectedMode = 0;
	}
	// ! @brief ������� ��������
	// ! @li 0 �������� +/-10V
	// ! @li 1 �������� +/-5V
	// ! @li 2 �������� +/-2V
	// ! @li 3 �������� +/-1V
	// ! @li 4 �������� +/-0.5V
	// ! @li 5 �������� +/-0.2V
	unsigned int range;
	// ! ����� ����������� ������ 0-31
	unsigned int logicalChannel;
	// ! @brief ����� �����
	// ! @li 0 ��������� ���������� ������������ ����� �����
	// ! @li 1 ���������������� ��������� ����������
	// ! @li 2 ��������� ������������ ����
	unsigned int collectedMode;
};
//---------------------------------------------------------------------------
#endif
