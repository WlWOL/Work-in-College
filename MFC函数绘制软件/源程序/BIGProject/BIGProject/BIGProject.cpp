// BIGProject.cpp : 定义应用程序的入口点。
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

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HDC BufferHDC;
HBITMAP Bmp;
//static 	CLogicData logicData;
//static	list <CLogicData> pannelDataList;
static double scalex = 1.00;			//x轴初始比例
static double scaley = 1.00;			//y轴初始比例
static double ratio = 1.0;			//x:y比例


static 	CLogicData logicData;
typedef list<CLogicData> pannelDataListall;


std::vector<pannelDataListall>datas;




CPanel pannel;
CGraphDlg optionfunction;

// 此代码模块中包含的函数的前向声明: 
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

	// TODO: 在此放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BIGPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BIGPROJECT));

	MSG msg;

	// 主消息循环: 
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
double ChangeX(double X)                 //坐标转换
{
	X = X - 298;
	X = 1000 * scalex * X / (1000 - 298);        //1000是当前X轴最大值
	return X;
}
double ChangeY(double Y)                  //坐标转换
{
	Y = Y*-1 + 536;
	Y = 1000 * scaley * Y / 536;           //500是当前Y轴最长值
	return Y;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	static RECT rect;
	static int cxChar, cyChar;

	static pannelDataListall *pannelDataList = NULL;       //数组指针
	static pannelDataListall *pannelDataList2 = NULL;
	POINT point = { 0,0 };
	static int iClick = 0;  //鼠标单击次数       

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
		HWND hButton3 = CreateWindow(L"Button", L"线段", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 5, 40, 40, hWnd, (HMENU)IDB_LINE, hInst, NULL);
		edit1 = CreateWindow(L"edit", L"请输入函数", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 46, 556, 848, 20, hWnd, (HMENU)IDB_edit, hInst, NULL);
		hButton5 = CreateWindow(L"Button", L"确认", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_FLAT | BS_PUSHBUTTON, 900, 556, 40, 25, hWnd, (HMENU)IDB_MOVE_VIEW, hInst, NULL);      //确认函数
		HWND TEXTAREA = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 5, 50, 250, 500, hWnd, (HMENU)IDB_TEXTAREA, hInst, NULL);        //描述区域																	
		CurrentState = None;
	}
	return 0;
	case WM_CONTEXTMENU:
	{
		//加载菜单资源  
		HMENU hroot = LoadMenu((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDC_BIGPROJECT));
		if (hroot)
		{
			// 获取第四个弹出菜单  
			HMENU hpop = GetSubMenu(hroot, 3);
			// 获取鼠标右击是的坐标 
			GetCursorPos(&point);		//获取光标的位置，以屏幕坐标表示
			int px = point.x;
			int py = point.y;
			ScreenToClient(hWnd, &point);		//屏幕坐标转换到客户区坐标


												//显示快捷菜单 
			if (point.x>260 && point.x<1000 && point.y>0 && point.y<550)
			{
				TrackPopupMenu(hpop,
					TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
					px,
					py,
					0,
					(HWND)wParam,
					NULL);
				// 用完后要销毁菜单资源  
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
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDB_MOVE_OBJ:
			CurrentState = None;
			MessageBox(hWnd, L"您点击了第一个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_POINT:
			CurrentState = None;
			MessageBox(hWnd, L"您点击了第二个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_LINE:
			if (CurrentState == Line)
				CurrentState = None;
			else
				CurrentState = Line;
			
			break;
		case ID_32816:			//右键菜单缩放25%
			scalex = scalex*0.25;
			scaley = scaley*0.25;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32817:			//右键菜单缩放50%
			scalex = scalex*0.50;
			scaley = scaley*0.50;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32818:			//右键菜单缩放150%
			scalex = scalex*(double)2 / 3;
			scaley = scaley*(double)2 / 3;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32819:			//右键菜单缩放125%
			scalex = scalex*0.80;
			scaley = scaley*0.80;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32820:			//右键菜单缩放80%
			scalex = scalex*1.25;
			scaley = scaley*1.25;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32821:			//右键菜单缩放66%
			scalex = scalex*1.50;
			scaley = scaley*1.50;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32822:			//右键菜单缩放50%
			scalex = scalex*2.00;
			scaley = scaley*2.00;

			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_32823:			//右键菜单缩放25%
			scalex = scalex*4.0;
			scaley = scaley*4.0;

			pannel.draw(BufferHDC, 0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32827:			//右键菜单x:y比例1：10
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32827, MF_BYCOMMAND);
			ratio = 10;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32828:			//右键菜单x:y比例1：5
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32828, MF_BYCOMMAND);
			ratio = 5.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32829:			//右键菜单x:y比例1：2
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32829, MF_BYCOMMAND);
			ratio = 2.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32830:			//右键菜单x:y比例1：1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32830, MF_BYCOMMAND);
			ratio = 1.00;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32831:			//右键菜单x:y比例2：1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32831, MF_BYCOMMAND);
			ratio = 0.50;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32832:			//右键菜单x:y比例5：1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32832, MF_BYCOMMAND);
			ratio = 0.20;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_X32833:			//右键菜单x:y比例10：1
			CheckMenuRadioItem(hpop, ID_X32827, ID_X32833, ID_X32833, MF_BYCOMMAND);
			ratio = 0.10;
			scaley = scalex*ratio;
			pannel.draw(BufferHDC,0);
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case IDB_MOVE_VIEW:  //...本来整了个移动，改成确认用了，ID懒得改了
			GetWindowText(edit1, functiontext, 100);
			wsprintf(functiontInfo, TEXT("您的函数：y = %s\r"), functiontext);
			MessageBox(hWnd, functiontInfo, TEXT("信息提示"), MB_ICONINFORMATION);
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

		// TODO: 在此处添加使用 hdc 的任何绘图代码...

		TextOut(hdc, 25, 560, L"y =", 3);


		TransparentBlt(hdc, 260, 0, 740, 550, BufferHDC, 0, 0, 999,999, 0xFE00FE);



		//坐标系统面板

		//绘制坐标系统面板
		RECT rect;
		rect.left = 260;
		rect.top = 0;
		rect.bottom = 550;
		rect.right = 1000;
		//根据当前的HDC自动设置合适的坐标原点
		//改变坐标系统位置
		pannel.setPanelRect(rect);
		pannel.getCorSystem().autoCreateOriginLogicCor(hdc);
		pannel.getCorSystem().setXMax(1000 * scalex);//设置X轴最大值
		pannel.getCorSystem().setYMax(1000 * scaley);//设置Y轴最大值
													 //改变坐标系统位置
		pannel.setPanelRect(rect);

		//绘制坐标系统
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

// “关于”框的消息处理程序。
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
