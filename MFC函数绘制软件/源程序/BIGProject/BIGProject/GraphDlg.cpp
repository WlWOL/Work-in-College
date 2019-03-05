// GraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphDlg.h"
#include "math.h"
#include "OPTR.h"
#include "OPND.h"
#include <stdlib.h>
//#include"atlstr.h"
void TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
extern int flag = 0;
//根据运算符优先级进行运算符和运算数进栈、出栈、计算操作
double CGraphDlg::Calculate(TCHAR * functionxxx, double x)
{

	double a=0,b=0;
	char e;
	char *p;
	p = (char*)malloc(100 * sizeof(char));
	size_t converted = 0;
	OPTR s;
	OPND q;
	s.InitOPTR ();
	q.InitOPND ();
	wcstombs_s(&converted,p, 100, functionxxx, _TRUNCATE);
	char md[10] = "#";
	strcat(p, md);
	//p = functionxxx.GetBuffer(100);
	s.Push('#');
	while(*p!='#'||s.GetTop()!='#')

	{
		if(In(*p)==3)
			return 0;
		else if(In(*p)==2&&flag==0)
		{
			double A;
			if(*p=='x')
			{
				q.Push (x);
				p++;
			}
			else
			{
				A=strtod(p,&m_stop);
				q.Push (A);
				p=m_stop;
			}
		}
			
		else
			switch(Precede(s.GetTop(),*p))
			{
				case '<': 
					if(*p=='s'&&*(p+1)=='h')
					{
						s.Push ('h');
						p++;p++;
						break;
					}
					else if(*p=='c'&&*(p+1)=='h')
					{
						s.Push ('H');
						p++;p++;
						break;
					}
					else if(*p=='t'&&*(p+1)=='h')
					{
						s.Push ('T');
						p++;p++;
						break;
					}
					else if(*p=='l'&&*(p+1)=='n')
					{
						s.Push ('l');
						p++;p++;
						break;
					}
					else if(*p=='l'&&*(p+1)=='g')
					{
						s.Push ('L');
						p++;p++;
						break;
					}
					else if(*p=='c'&&*(p+1)=='o'&&*(p+2)=='t')
					{
						s.Push ('C');
						p++;p++;p++;
						break;
					}
					else if(*p=='s'&&*(p+1)=='i'&&*(p+2)=='n'||*p=='c'&&*(p+1)=='o'&&*(p+2)=='s'||*p=='t'&&*(p+1)=='a'&&*(p+2)=='n')
					{
						
						s.Push (*p);
						p++;p++;p++;
						break;
					}
					else if(*p=='('&&(*(p+1)=='#'||*(p+1)=='+'||*(p+1)=='-'||*(p+1)=='*'||*(p+1)=='/'||*(p+1)=='^'||*(p+1)==')'))
					{
						flag=2;return 0;
					}
					else if(*p=='+'||*p=='-'||*p=='*'||*p=='/'||*p=='#'||*p=='('||*p==')'||*p=='^')
					{
						s.Push (*p);
						p++;
						break;
					}
					else 
					{
						flag=3;
						return 0;
					}
				case '=': 
					if(*(p+1)!='#'&&*(p+1)!='+'&&*(p+1)!='-'&&*(p+1)!='*'&&*(p+1)!='/'&&*(p+1)!='^'&&*(p+1)!=')')
					{
						flag=2;return 0;
					}
					e=s.Pop(); p++; break;
				case '>': 
					if(s.GetTop ()=='s')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push(sin(b));
							break;
						}
						
					}
					else if(s.GetTop ()=='c')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push(cos(b));
							break;
						}
						
					}
					else if(s.GetTop ()=='t')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push(tan(b));
							break;
						}
						
					}
					else if(s.GetTop ()=='C')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push(1/tan(b));
							break;
						}
						
					}
					else if(s.GetTop ()=='^')
					{
						b=q.Pop();
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();							 
							a=q.Pop(); 
							q.Push(Operate(a,e,b));
							break;
						}
					}
					else if(s.GetTop ()=='l')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							if(b>0)
								q.Push(log(b));
							else
								q.Push(0);
							break;
						}
					}
					else if(s.GetTop ()=='L')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							if(b>0)
								q.Push(log10(b));
							else
								q.Push(0);
							break;
						}
					}
					else if(s.GetTop ()=='h')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push((Pow(2.71828,b)-Pow(2.71828,-b))/2);
							break;
						}
					}
					else if(s.GetTop ()=='H')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push((Pow(2.71828,b)+Pow(2.71828,-b))/2);
							break;
						}
					}
					else if(s.GetTop ()=='T')
					{
						if(q.base==q.top )
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop();
							b=q.Pop();
							q.Push((Pow(2.71828,b)-Pow(2.71828,-b))/(Pow(2.71828,b)+Pow(2.71828,-b)));
							break;
						}
					}
					else 
					{
						b=q.Pop();
						if(q.base==q.top )       
						{
							flag=2;return 0;
						}
						else
						{
							e=s.Pop(); 
							a=q.Pop(); 
							q.Push(Operate(a,e,b));
							break;
						}
					}

				case 'E': flag=2;return 0;
				default:break;
			}

	}
//	m_expression.ReleaseBuffer ();
	if(q.top-q.base>1){flag=2;return 0;} 
	return  q.GetTop ();
}
//判断运算符和运算数
int CGraphDlg::In(char ch)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch=='#'||ch==')'||ch=='s'||ch=='c'||ch=='t'||ch=='l'||ch=='h'||ch=='H'||ch=='T'||ch=='^')	
		return 1;
	 if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'||ch=='x')
		return 2;
	else
	{
		flag=3;
		return 3;
	}
}
//判断运算符优先级
char CGraphDlg::Precede(char s,char c)
{

	switch(s)
    {
        case '+':                 
        case '-':
             if(c=='+'||c=='-')
                 return '>';
             else if(c=='*'||c=='/')
                 return '<';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return '>';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T'||c=='^')
                 return '<';
             else if(c=='#')
                 return '>';
        case '*':
        case '/':
             if(c=='+'||c=='-')
                 return '>';
             else if(c=='*'||c=='/')
                 return '>';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return '>';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T'||c=='^')
                 return '<';
             else if(c=='#')
                 return '>';
        case '(':
             if(c=='+'||c=='-')
                 return '<';
             else if(c=='*'||c=='/')
                 return '<';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return '=';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T'||c=='^')
                 return '<';
             else if(c=='#')
                 return 'E';
        case ')':
             if(c=='+'||c=='-')
                 return '>';
             else if(c=='*'||c=='/')
                 return '>';
             else if(c=='(')
                 return 'E';
             else if(c==')')
                 return '>';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T'||c=='^')
                 return 'E';
             else if(c=='#')
                 return '>';
        case '#':
             if(c=='+'||c=='-')
                 return '<';
             else if(c=='*'||c=='/')
                 return '<';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return 'E';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T'||c=='^')
                 return '<';
             else if(c=='#')
                 return '=';
		case 's':
		case 'c':
		case 't':
		case 'C':
		case 'l':
		case 'L':
		case 'h':
		case 'H':
		case 'T':
             if(c=='+'||c=='-')
                 return '>';
             else if(c=='*'||c=='/')
                 return '>';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return '>';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T')
                 return 'E';
			 else if(c=='^')
                 return '<';
             else if(c=='#')
                 return '>';
		case '^':
             if(c=='+'||c=='-')
                 return '>';
             else if(c=='*'||c=='/')
                 return '>';
             else if(c=='(')
                 return '<';
             else if(c==')')
                 return '>';
			 else if(c=='s'||c=='c'||c=='t'||c=='C'||c=='l'||c=='L'||c=='h'||c=='H'||c=='T')
                 return 'E';
			 else if(c=='^')
                 return '<';
             else if(c=='#')
                 return '>';
        default:
             break;
	}
	return 'E';
}
//加减乘除方
double CGraphDlg::Operate(double a,char e,double b)
{
	double result=1;
	if(e=='+')
		result= a+b;
	else if(e=='-')
		result= a-b;
	else if(e=='*')
		result= a*b;
	else if(e=='/'&&b!=0)
		result= a/b;
	else if(e=='/'&&b==0)
		{
	
			flag=1;
			return 0;
		}
	else if(e=='^')
	{
		if(a==0)
			result =0;
		else
			result = pow(a,b);
	}
	return result;
	
}
//方2
double CGraphDlg::Pow(double a, double b)
{
	double result;
	if(b==0)
		result=1;
	else if(b>0)
		result=pow(a,b);
	else if(b<0)
		result=1/pow(a,-b);
	return result;
}

