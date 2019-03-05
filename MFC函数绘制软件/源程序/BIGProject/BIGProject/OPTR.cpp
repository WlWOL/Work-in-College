// OPTR.cpp: implementation of the OPTR class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "OPTR.h"

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

OPTR::OPTR()
{

}

OPTR::~OPTR()
{

}

int OPTR::InitOPTR()
{
	base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!base)
	{
		MessageBox(NULL,L"动态分配内存失败!",L"错误提示",MB_OK);
		return 0;
	}
	top=base;
	size=STACK_INIT_SIZE;
	return 1;
}

int OPTR::Push(char e)
{
	if(top-base>=size)
	{	
		base=(char *)realloc(base,(STACK_INIT_SIZE+STACKINCREMENT)*sizeof(char));
		if(!base)
		{
			MessageBox(NULL,L"动态分配内存失败!",L"错误提示",MB_OK);
			return 0;
		}
		top=base+size;
		size+=STACKINCREMENT;
	}
	*top=e;
	top++;
	return 1;
}

char OPTR::Pop()
{
	char e;
	if(base==top)
	{
		MessageBox(NULL, L"栈空!", L"错误提示",MB_OK);
		return 0;
	}
	e=*--top;
	return e;
}

char OPTR::GetTop()
{
	char e=NULL;
	if(base==top)
	{
		MessageBox(NULL,L"栈空!",L"错误提示",MB_OK);
		return e;
	}
	e=*(top-1);
	return e;
}
