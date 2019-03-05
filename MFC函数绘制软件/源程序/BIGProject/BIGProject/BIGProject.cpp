// BIGProject.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BIGProject.h"
#include "painting.h"
#include <vector>
#include <WindowsX.h>
#include "GraphDlg.h"
#include "math.h"
#include "OPTR.h"
#include "OPND.h"
using namespace std;

enum _CurrentState {
	Line = 2,
	Point = 1,
	None = 0,
}CurrentState;

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

HDC BufferHDC;
HBITMAP Bmp;
//static 	CLogicData logicData;
//static	list <CLogicData> pannelDataList;
static double scalex = 1.00;			//x���ʼ����
static double scaley = 1.00;			//y���ʼ����
static double ratio = 1.0;			//x:y����


static 	CLogicData logicData;
typedef list<CLogicData> pannelDataListall;


std::vector<pannelDataListall>datas;




CPanel pannel;
CGraphDlg optionfunction;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣

	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BIGPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BIGPROJECT));

	MSG msg;

	// ����Ϣѭ��: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIGPROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BIGPROJECT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 650, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
double ChangeX(double X)                 //����ת��
{
	X = X - 298;
	X = 1000 * scalex * X / (1000 - 298);        //1000�ǵ�ǰX�����ֵ
	return X;
}
double ChangeY(double Y)                  //����ת��
{
	Y = Y*-1 + 536;
	Y = 1000 * scaley * Y / 536;           //500�ǵ�ǰY���ֵ
	return Y;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	static RECT rect;
	static int cxChar, cyChar;

	static pannelDataListall *pannelDataList = NULL;       //����ָ��
	static pannelDataListall *pannelDataList2 = NULL;
	POINT point = { 0,0 };
	static int iClick = 0;  //��굥������       

	static HWND edit1;
	static HWND hButton5;
	TCHAR functiontext[100];
	TCHAR functiontInfo[200];
	switch (message)
	{
	case WM_SIZE:
		//	rect.left = 24 * cxChar;
		//	rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);


		return 0;
	case WM_CREATE:
	{
		PAINTSTRUCT ps;
		HDC hdc = GetDC(hWnd);
		BufferHDC = CreateCompatibleDC(hdc);
		Bmp = CreateCompatibleBitmap(hdc, 2560, 1440);
		ReleaseDC(hWnd, hdc);


		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		HWND hButton3 = CreateWindow(L"Button", L"�߶�", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 5, 40, 40, hWnd, (HMENU)IDB_LINE, hInst, NULL);
		edit1 = CreateWindow(L"edit", L"�����뺯��", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 46, 556, 848, 20, hWnd, (HMENU)IDB_edit, hInst, NULL);
		hButton5 = CreateWindow(L"Button", L"ȷ��", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_FLAT | BS_PUSHBUTTON, 900, 556, 40, 25, hWnd, (HMENU)IDB_MOVE_VIEW, hInst, NULL);      //ȷ�Ϻ���
		HWND TEXTAREA = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 5, 50, 250, 500, hWnd, (HMENU)IDB_TEXTAREA, hInst, NULL);        //��������																	
		CurrentState = None;
	}
	return 0;
	case WM_CONTEXTMENU:
	{
		//���ز˵���Դ  
		HMENU hroot = LoadMenu((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDC_BIGPROJECT));
		if (hroot)
		{
			// ��ȡ���ĸ������˵�  
			HMENU hpop = GetSubMenu(hroot, 3);
			// ��ȡ����һ��ǵ����� 
			GetCursorPos(&point);		//��ȡ����λ�ã�����Ļ�����ʾ
			int px = point.x;
			int py = point.y;
			ScreenToClient(hWnd, &point);		//��Ļ����ת�����ͻ�������


												//��ʾ��ݲ˵� 
			if (point.x>260 && point.x<1000 && point.y>0 && point.y<550)
			{
				TrackPopupMenu(hpop,
					TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
					px,
					py,
					0,
					(HWND)wParam,
					NULL);
				// �����Ҫ���ٲ˵���Դ  
				//DestroyMenu(hroot);
			}
		}
	}
	break;


	case WM_COMMAND:
	{
		auto hroot = GetMenu(hWnd);
		HMENU hpop = GetSubMenu(hroot, 3);
		char *pp="2*x#";
		int wmId = LOWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDB_MOVE_OBJ:
			CurrentState = None;
			MessageBox(hWnd, L"������˵�һ����ť��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_POINT:
			CurrentState = None;
			MessageBox(hWnd, L"������˵ڶ�����ť��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_LINE:
			if (CurrentState == Line)
				CurrentState = None;
			else
				CurrentState = Line;
			
			break;
		case ID_32816:			//�Ҽ��˵�����25%
			scalex = scalex*0.25;
			scaley = scaley*0.25;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32817:			//�Ҽ��˵�����50%
			scalex = scalex*0.50;
			scaley = scaley*0.50;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32818:			//�Ҽ��˵�����150%
			scalex = scalex*(double)2 / 3;
			scaley = scaley*(double)2 / 3;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32819:			//�Ҽ��˵�����125%
			scalex = scalex*0.80;
			scaley = scaley*0.80;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32820:			//�Ҽ��˵�����80%
			scalex = scalex*1.25;
			scaley = scaley*1.25;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32821:			//�Ҽ��˵�����66%
			scalex = scalex*1.50;
			scaley = scaley*1.50;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32822:			//�Ҽ��˵�����50%
			scalex = scalex*2.00;
			scaley = scaley*2.00;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32823:			//�Ҽ��˵�����25%
			scalex = scalex*4.0;
			scaley = scaley*4.0;

			pannel.draw(BufferHDC, 0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32827:			//�Ҽ��˵�x:y����1��10
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32827, MF_BYCOMMAND);
			ratio = 10;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32828:			//�Ҽ��˵�x:y����1��5
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32828, MF_BYCOMMAND);
			ratio = 5.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32829:			//�Ҽ��˵�x:y����1��2
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32829, MF_BYCOMMAND);
			ratio = 2.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32830:			//�Ҽ��˵�x:y����1��1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32830, MF_BYCOMMAND);
			ratio = 1.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32831:			//�Ҽ��˵�x:y����2��1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32831, MF_BYCOMMAND);
			ratio = 0.50;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32832:			//�Ҽ��˵�x:y����5��1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32832, MF_BYCOMMAND);
			ratio = 0.20;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32833:			//�Ҽ��˵�x:y����10��1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32833, MF_BYCOMMAND);
			ratio = 0.10;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case IDB_MOVE_VIEW:  //...�������˸��ƶ����ĳ�ȷ�����ˣ�ID���ø���
			GetWindowText(edit1, functiontext, 100);
			wsprintf(functiontInfo, TEXT("���ĺ�����y = %s\r"), functiontext);
			MessageBox(hWnd, functiontInfo, TEXT("��Ϣ��ʾ"), MB_ICONINFORMATION);
				pannelDataList2 = new pannelDataListall;
				double X, Y;
				for(X=0;X<5000;X++)
				{ 
					Y = optionfunction.Calculate(functiontext, X);
					pannelDataList2->push_back({ X,Y });
				}


				pannel.setPannelDataList(pannelDataList2);
				InvalidateRect(hWnd, NULL, FALSE);
				datas.push_back(*pannelDataList2);

			break;


		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...

		TextOut(hdc, 25, 560, L"y =", 3);


		TransparentBlt(hdc, 260, 0, 740, 550, BufferHDC, 0, 0, 999,999, 0xFE00FE);



		//����ϵͳ���

		//��������ϵͳ���
		RECT rect;
		rect.left = 260;
		rect.top = 0;
		rect.bottom = 550;
		rect.right = 1000;
		//���ݵ�ǰ��HDC�Զ����ú��ʵ�����ԭ��
		//�ı�����ϵͳλ��
		pannel.setPanelRect(rect);
		pannel.getCorSystem().autoCreateOriginLogicCor(hdc);
		pannel.getCorSystem().setXMax(1000 * scalex);//����X�����ֵ
		pannel.getCorSystem().setYMax(1000 * scaley);//����Y�����ֵ
													 //�ı�����ϵͳλ��
		pannel.setPanelRect(rect);

		//��������ϵͳ
		pannel.draw(hdc,0);
		EndPaint(hWnd, &ps);

	}
	break;

	case WM_LBUTTONDOWN:                               //2
	{
		double X, Y;
		X = GET_X_LPARAM(lParam);
		Y = GET_Y_LPARAM(lParam);
		X = ChangeX(X);
		Y = ChangeY(Y);
		if (CurrentState == Line)
		{
			pannelDataList = new pannelDataListall;
			pannelDataList->push_back({ X,Y });
		}
	}
	return 0;

	case WM_LBUTTONUP:                                //2
	{

		double X, Y;
		X = GET_X_LPARAM(lParam);
		Y = GET_Y_LPARAM(lParam);
		X = ChangeX(X);
		Y = ChangeY(Y);
		if (CurrentState == Line)
		{
			pannelDataList->push_back({ X,Y });
			pannel.setPannelDataList(pannelDataList);
			InvalidateRect(hWnd, NULL, FALSE);
			datas.push_back(*pannelDataList);
		}

	}
	return 0;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
