#pragma once
#include "stdafx.h"
#include<list>
using namespace std;



typedef struct tagData          //���߽ṹ��          
{
	int ptBeginX, ptBeginY;		//�߶����  
	int ptEndX, ptEndY;			//�߶��յ�  
}PAINTDATA;



//----------------------------ͼ����
class CShape
{
public:
	virtual void draw(HDC hdc) = 0;
};

//----------------------------��
class CP_Point :public CShape {
protected:
	POINT pt;//������
	int width;//���	
	BOOL isSolid;//�Ƿ�ʵ��
	BOOL isBorder;
	COLORREF colorBorder;//�߿���ɫ
	COLORREF colorSolid;//ʵ����ɫ
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

//----------------------------��
class CP_Line :public CShape {
protected:
	CP_Point leftPoint;
	CP_Point rightPoint;
	int width;
	COLORREF colorLine;
	BOOL isDrawPoint;//�Ƿ��������˵ĵ�
	BOOL isDrawLine;//�Ƿ����� 
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

//----------------------------����
class CP_BK :public CShape {
protected:
	RECT rectBK;
	int width;
	int height;
	BOOL isSolid;//�Ƿ�ʵ��
	BOOL isBorder;
	COLORREF colorBorder;//�߿���ɫ
	COLORREF colorSolid;//ʵ����ɫ
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

//----------------------------�����ı���
class CP_NetBK :public CP_BK {
protected:
	int xOffset;//�����귽����
	int yOffset;//�����귽����
	COLORREF colorNet;//������ɫ
	int netWidth;//���߿��
	BOOL isXNet;//�����Ƿ���ʾ
	BOOL isYNet;//�����Ƿ���ʾ
	list <CP_Line> xLines;//X�����ϵ��ߣ���ֱ�ģ��������µ���
	list <CP_Line> yLines;//Y�����ϵ��ߣ�ˮƽ�ģ��������ҵ���
public:
	virtual void draw(HDC hdc);
	CP_NetBK();
	virtual void setRectBK(RECT rectBK);
	void autoCreateXNet();//�Զ�����X����
	void autoCreateYNet();//�Զ�����Y����
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
//----------------------------����ϵ
class CP_CorSystem :public CShape {
public:
	enum CorType { Decare = 1 };//����ϵ����(Ŀǰ�͵ѿ�������ϵ)
protected:
	POINT originCor;//����ϵԭ��
	POINT originLogicCor;//�߼�����ϵԭ��
	POINT originX;//X�����
	POINT originY;//Y�����
	CorType corType;
	CP_Line xLine;
	CP_Line yLine;
	int height;
	int width;
	RECT rectCor;//����ϵ��Ļλ��
	BOOL isAllFillNet;//�Ƿ�ȫ����������
	CP_NetBK corBK;//����ϵ����
	TCHAR strFontName[256];//��������
	int fontSize;//�����С���߶�
	COLORREF fontColor;//������ɫ
	BOOL isFontBKTransparent;//���屳���Ƿ�͸��
	BOOL isDrawChars;//�Ƿ񻭿̶��ַ�
	int xMax;//X�����ֵ
	int yMax;//Y�����ֵ
	double xLogicUnit;//��X�����߼���λ����
	double yLogicUnit;//��Y�����߼���λ����
	SIZE xSize, ySize;
public:
	virtual void draw(HDC hdc);
	void drawChars(HDC hdc);//���̶��ַ�
	CP_CorSystem();
	void setOriginCor(POINT originCor);
	POINT getOriginCor();
	//�߼�����ϵԭ��
	void setOriginLogicCor(POINT originLogicCor);
	POINT getOriginLogicCor();
	void autoCreateXLine();//�Զ�����X��
	void autoCreateYLine();//�Զ�����Y��
	void autoCreateCorBK();//�Զ���������ϵ����
	void autoCreateOriginLogicCor(HDC hdc);//�Զ������߼�����ԭ��
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
	POINT corToScreenPoint(POINT pt);//�ѿ�������ת��Ļ����
	POINT curCorToScreenPoint(POINT pt);//��ǰ�ѿ���ϵ����ת��Ļ����
	POINT logicCorToCurCorPoint(double x, double y);//�߼�����ת��ǰ�ѿ���ϵ����
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
	double getXLogicUnit();//��X�����߼���λ����
	double getYLogicUnit();//��Y�����߼���λ����
	void setRectCor(RECT rectCor);//����ϵ��Ļλ��
	RECT getRectCor();
};
//----------------------------�߼����ݽṹ

struct CLogicData {
	double x;
	double y;
};


//----------------------------��ʾ���
class CPanel
{
protected:
	CP_BK bk;//����
	CP_CorSystem corSystem;//����ϵϵͳ
	list <CShape *> pannelDrawList;//��ʾ����ͼ����
	list <CLogicData> pannelDataList;//�������б������ⲿ�����ĵ����ݣ�
	list <CP_Point> pannelPointList;//�������б��ڲ���ͼ�ã�
	list <CP_Line> pannelLineList;//���б��ڲ���ͼ�ã�
	CLogicData *pCLogicDataList;//�ⲿ�ɸ�������
public:
	CPanel(void);
	~CPanel(void);
	virtual void draw(HDC hdc, int x);
	void drawLines(HDC hdc,int x);//����
	void setPanelRect(RECT rect);//��������λ��
	void setCP_CorSystemRect(RECT rect);//��������ϵͳ��λ��
	void setBKRect(RECT rect);//���ñ�����λ��
	void setPannelDataList(list <CLogicData> *pPannelDataList);//�ⲿ�ɸ�������
	CP_CorSystem &getCorSystem();
	CP_BK &getBK();
	list <CLogicData> &getPannelDataList();//�������б������ⲿ�����ĵ����ݣ�
	list <CP_Point> &getPannelPointList();//�������б��ڲ���ͼ�ã�
	list <CP_Line> &getPannelLineList();//���б��ڲ���ͼ�ã�
	void clearDataList();//��յ������б������ⲿ�����ĵ����ݣ�
	void clearPannelPointList();//��յ������б������ⲿ�����ĵ����ݣ�
	void clearPannelLineList();//��յ������б������ⲿ�����ĵ����ݣ�
	void addData(double x, double y);//���ⲿ��ӵ㣨�������ݣ�
	void finishAddDataList();//��ɶ���������ӣ��Զ������ߺ͵��б�
	void autoCreatePointList();//�Զ����ɵ������б��ڲ���ͼ�ã�
	void autoCreateLineList();//�Զ��������б��ڲ���ͼ�ã�
};
