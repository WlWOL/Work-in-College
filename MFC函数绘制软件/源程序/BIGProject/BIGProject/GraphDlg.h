
#pragma once
#include "stdafx.h"
//#include"atlstr.h"

class CGraphDlg
{
// Construction
public:
	double Pow(double ,double );
	double Operate(double ,char ,double );
	char Precede(char ,char);//�ж���������ȼ�
	int In(char );//�ж��������������
	double Calculate(TCHAR *, double);
private:
	UINT m_num;
	char *m_stop;

};
