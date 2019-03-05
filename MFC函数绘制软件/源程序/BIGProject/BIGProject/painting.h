#pragma once
#include "stdafx.h"
#include<list>
using namespace std;



typedef struct tagData          //画线结构体          
{
	int ptBeginX, ptBeginY;		//线段起点  
	int ptEndX, ptEndY;			//线段终点  
}PAINTDATA;



//----------------------------图形类
class CShape
{
public:
	virtual void draw(HDC hdc) = 0;
};

//----------------------------点
class CP_Point :public CShape {
protected:
	POINT pt;//点坐标
	int width;//宽度	
	BOOL isSolid;//是否实心
	BOOL isBorder;
	COLORREF colorBorder;//边框颜色
	COLORREF colorSolid;//实心颜色
public:
	virtual void draw(HDC hdc);
	CP_Point();
	void setPt(POINT point);
	POINT getPt();
	void setWidth(int width);
	int getWidth();
	void setIsSolid(BOOL isSolid);
	BOOL getIsSolid();
	void setIsBorder(BOOL isBorder);
	BOOL getIsBorder();
	void setColorBorder(COLORREF colorBorder);
	COLORREF getColorBorder();
	void setColorSolid(COLORREF colorSolid);
	COLORREF getColorSolid();
	CP_Point& operator =(CP_Point &point);
};

//----------------------------线
class CP_Line :public CShape {
protected:
	CP_Point leftPoint;
	CP_Point rightPoint;
	int width;
	COLORREF colorLine;
	BOOL isDrawPoint;//是否画连线两端的点
	BOOL isDrawLine;//是否画连线 
public:
	virtual void draw(HDC hdc);
	virtual void drawfunction(HDC hdc);
	CP_Line();
	void setIsDrawPoint(BOOL isDrawPoint);
	BOOL getIsDrawPoint();
	void setIsDrawLine(BOOL isDrawLine);
	BOOL getIsDrawLine();
	void setWidth(int width);
	int getWidth();
	void setColorLine(COLORREF colorLine);
	COLORREF getColorLine();
	void setLine(CP_Point leftPoint, CP_Point rightPoint);
	void setLeftPoint(CP_Point leftPoint);
	CP_Point getLeftPoint();
	void setRightPoint(CP_Point rightPoint);
	CP_Point getRightPoint();
	CP_Line& operator =(CP_Line &line);

};

//----------------------------背景
class CP_BK :public CShape {
protected:
	RECT rectBK;
	int width;
	int height;
	BOOL isSolid;//是否实心
	BOOL isBorder;
	COLORREF colorBorder;//边框颜色
	COLORREF colorSolid;//实心颜色
public:
	virtual void draw(HDC hdc);
	CP_BK();
	virtual void setRectBK(RECT rectBK);
	RECT getRectBK();
	void setHeight(int height);
	int getHeight();
	void setWidth(int width);
	int getWidth();
	void setIsSolid(BOOL isSolid);
	BOOL getIsSolid();
	void setIsBorder(BOOL isBorder);
	BOOL getIsBorder();
	void setColorBorder(COLORREF colorBorder);
	COLORREF getColorBorder();
	void setColorSolid(COLORREF colorSolid);
	COLORREF getColorSolid();
};

//----------------------------有网的背景
class CP_NetBK :public CP_BK {
protected:
	int xOffset;//横坐标方向间隔
	int yOffset;//纵坐标方向间隔
	COLORREF colorNet;//网线颜色
	int netWidth;//网线宽度
	BOOL isXNet;//网线是否显示
	BOOL isYNet;//网线是否显示
	list <CP_Line> xLines;//X坐标上的线，垂直的，从上往下的线
	list <CP_Line> yLines;//Y坐标上的线，水平的，从左往右的线
public:
	virtual void draw(HDC hdc);
	CP_NetBK();
	virtual void setRectBK(RECT rectBK);
	void autoCreateXNet();//自动生成X网线
	void autoCreateYNet();//自动生成Y网线
	void setXOffset(int xOffset);
	int getXOffset();
	void setYOffset(int yOffset);
	int getYOffset();
	void setNetWidth(int netWidth);
	int getNetWidth();
	void setIsXNet(BOOL isXNet);
	BOOL getIsXNet();
	void setIsYNet(BOOL isYNet);
	BOOL getIsYNet();
	void setColorNet(COLORREF colorNet);
	COLORREF getColorNet();

};
//----------------------------坐标系
class CP_CorSystem :public CShape {
public:
	enum CorType { Decare = 1 };//坐标系类型(目前就笛卡尔坐标系)
protected:
	POINT originCor;//坐标系原点
	POINT originLogicCor;//逻辑坐标系原点
	POINT originX;//X轴起点
	POINT originY;//Y轴起点
	CorType corType;
	CP_Line xLine;
	CP_Line yLine;
	int height;
	int width;
	RECT rectCor;//坐标系屏幕位置
	BOOL isAllFillNet;//是否全部覆盖网线
	CP_NetBK corBK;//坐标系背景
	TCHAR strFontName[256];//字体名字
	int fontSize;//字体大小，高度
	COLORREF fontColor;//字体颜色
	BOOL isFontBKTransparent;//字体背景是否透明
	BOOL isDrawChars;//是否画刻度字符
	int xMax;//X轴最大值
	int yMax;//Y轴最大值
	double xLogicUnit;//在X轴上逻辑单位像素
	double yLogicUnit;//在Y轴上逻辑单位像素
	SIZE xSize, ySize;
public:
	virtual void draw(HDC hdc);
	void drawChars(HDC hdc);//画刻度字符
	CP_CorSystem();
	void setOriginCor(POINT originCor);
	POINT getOriginCor();
	//逻辑坐标系原点
	void setOriginLogicCor(POINT originLogicCor);
	POINT getOriginLogicCor();
	void autoCreateXLine();//自动生成X线
	void autoCreateYLine();//自动生成Y线
	void autoCreateCorBK();//自动生成坐标系背景
	void autoCreateOriginLogicCor(HDC hdc);//自动生成逻辑坐标原点
	void setHeight(int height);
	int getHeight();
	void setWidth(int width);
	int getWidth();
	void setOriginX(POINT originX);
	POINT getOriginX();
	void setOriginY(POINT originY);
	POINT getOriginY();
	void setIsAllFillNet(BOOL isAllFillNet);
	BOOL getIsAllFillNet();
	POINT corToScreenPoint(POINT pt);//笛卡尔坐标转屏幕坐标
	POINT curCorToScreenPoint(POINT pt);//当前笛卡尔系坐标转屏幕坐标
	POINT logicCorToCurCorPoint(double x, double y);//逻辑坐标转当前笛卡尔系坐标
	void setFontSize(int fontSize);
	int getFontSize();
	void setFontColor(COLORREF fontColor);
	COLORREF getFontColor();
	void setIsFontBKTransparent(BOOL isFontBKTransparent);
	BOOL getIsFontBKTransparent();
	void setStrFontName(TCHAR *strFontName);
	TCHAR *getStrFontName();
	void setIsDrawChars(BOOL isDrawChars);
	BOOL getIsDrawChars();
	void setXMax(int xMax);
	int getXMax();
	void setYMax(int yMax);
	int getYMax();
	double getXLogicUnit();//在X轴上逻辑单位像素
	double getYLogicUnit();//在Y轴上逻辑单位像素
	void setRectCor(RECT rectCor);//坐标系屏幕位置
	RECT getRectCor();
};
//----------------------------逻辑数据结构

struct CLogicData {
	double x;
	double y;
};


//----------------------------显示面板
class CPanel
{
protected:
	CP_BK bk;//背景
	CP_CorSystem corSystem;//坐标系系统
	list <CShape *> pannelDrawList;//显示面板绘图链表
	list <CLogicData> pannelDataList;//点坐标列表（保存外部给出的点数据）
	list <CP_Point> pannelPointList;//点坐标列表（内部绘图用）
	list <CP_Line> pannelLineList;//线列表（内部绘图用）
	CLogicData *pCLogicDataList;//外部可给出数据
public:
	CPanel(void);
	~CPanel(void);
	virtual void draw(HDC hdc, int x);
	void drawLines(HDC hdc,int x);//画线
	void setPanelRect(RECT rect);//设置面板的位置
	void setCP_CorSystemRect(RECT rect);//设置坐标系统的位置
	void setBKRect(RECT rect);//设置背景的位置
	void setPannelDataList(list <CLogicData> *pPannelDataList);//外部可给出数据
	CP_CorSystem &getCorSystem();
	CP_BK &getBK();
	list <CLogicData> &getPannelDataList();//点坐标列表（保存外部给出的点数据）
	list <CP_Point> &getPannelPointList();//点坐标列表（内部绘图用）
	list <CP_Line> &getPannelLineList();//线列表（内部绘图用）
	void clearDataList();//清空点坐标列表（保存外部给出的点数据）
	void clearPannelPointList();//清空点坐标列表（保存外部给出的点数据）
	void clearPannelLineList();//清空点坐标列表（保存外部给出的点数据）
	void addData(double x, double y);//从外部添加点（坐标数据）
	void finishAddDataList();//完成对坐标点的添加，自动生成线和点列表
	void autoCreatePointList();//自动生成点坐标列表（内部绘图用）
	void autoCreateLineList();//自动生成线列表（内部绘图用）
};
