
#pragma once
#include "stdafx.h"
//#include"atlstr.h"

class CGraphDlg
{
// Construction
public:
	double Pow(double ,double );
	double Operate(double ,char ,double );
	char Precede(char ,char);//判断运算符优先级
	int In(char );//判断运算符和运算数
	double Calculate(TCHAR *, double);
private:
	UINT m_num;
	char *m_stop;

};
