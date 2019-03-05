// OPND.h: interface for the OPND class.
//
#pragma once
#include "stdafx.h"

class OPND  
{
public:
	OPND();
	double GetTop();
	int InitOPND();
	int Push(double e);
	double Pop();
	double *base;
	double *top;
	int size;
	virtual ~OPND();
};

