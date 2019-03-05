// OPTR.h: interface for the OPTR class.
//
#pragma once
#include "stdafx.h"

class OPTR  
{
public:
	int InitOPTR();
	OPTR();
	char GetTop();
	int Push(char e);
	char Pop();
	char *base;
	char *top;
	int size;
	virtual ~OPTR();

};

