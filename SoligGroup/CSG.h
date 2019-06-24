#ifndef CSGH
#define CSGH
#include<System.hpp>
#include <Graphics.hpp>

class CSG
{
	// Группа прочности с атрибутами вероятности и цвета
public:
	CSG(void)
	{
		group = "?";
		probability = 0;
		color = clYellow;
	}

	AnsiString group;
	double probability;
	TColor color;

	AnsiString ToString();
};
#endif
