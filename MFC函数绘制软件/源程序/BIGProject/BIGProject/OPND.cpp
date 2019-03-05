// OPND.cpp: implementation of the OPND class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPND.h"
#include <stdio.h>
#include <stdlib.h>
                                                                 
#include <malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OPND::OPND()
{

}

OPND::~OPND()
{

}

int OPND::InitOPND()
{
	base=(double *)malloc(STACK_INIT_SIZE*sizeof(double));
	if(!base)
	{
		MessageBox(NULL,L"��̬�����ڴ�ʧ��!",L"������ʾ",MB_OK);
		return 0;
	}
	top=base;
	size=STACK_INIT_SIZE;
	return 1;
} 

double OPND::GetTop()
{
	double e;
	if(base==top)
		return 0;
	e=*(top-1);
	return e;
}

int OPND::Push(double e)
{
	if(top-base>=size)
	{	
		base=(double *)realloc(base,(STACK_INIT_SIZE+STACKINCREMENT)*sizeof(double));
		if(!base)
		{
			MessageBox(NULL,L"��̬�����ڴ�ʧ��!",L"������ʾ",MB_OK);
			return 0;
		}
		top=base+size;
		size+=STACKINCREMENT;
	}
	*top++=e;
	return 1;
}	

double OPND::Pop()
{
	double e;
	if(base==top)
	{   
		MessageBox(NULL,L"ջ��!",L"������ʾ",MB_OK);                      //��֪Ϊ�Σ�ԭ��ע����
		return 0;
	}
	e=*--top;
	return e;
}