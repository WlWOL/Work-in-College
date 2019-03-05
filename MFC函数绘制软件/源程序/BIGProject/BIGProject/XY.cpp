#include "StdAfx.h"
#include "painting.h"

//----------------------------背景
void CP_BK::draw(HDC hdc)
{
	HBRUSH hBrush = (WHITE_BRUSH);//填充点实心的画刷
	HPEN hPen;//边框画笔
			  //画边框
	if (getIsBorder())
	{
		hPen = ::CreatePen(PS_SOLID, 1, getColorBorder());
	}
	else
	{
		hPen = ::CreatePen(PS_NULL, 1, getColorBorder());
	}
	::SelectObject(hdc, hPen);
	//填充
	if (getIsSolid())
	{
		hBrush = ::CreateSolidBrush(getColorSolid());
		::SelectObject(hdc, hBrush);
	}
	::Rectangle(hdc, rectBK.left, rectBK.top, rectBK.left + getWidth(), rectBK.top + getHeight());
	::DeleteObject(hPen);
	if (getIsSolid())
	{
		::DeleteObject(hBrush);
	}
}
CP_BK::CP_BK()
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 100;
	rect.bottom = 100;
	CP_BK::setRectBK(rect);
	setIsSolid(true);
	setIsBorder(true);
	setColorBorder(RGB(0, 0, 0));
	setColorSolid(RGB(0, 0, 0));
}
void CP_BK::setIsBorder(BOOL isBorder)
{
	this->isBorder = isBorder;
}
BOOL CP_BK::getIsBorder()
{
	return isBorder;
}
void CP_BK::setIsSolid(BOOL isSolid)
{
	this->isSolid = isSolid;
}
BOOL CP_BK::getIsSolid()
{
	return isSolid;
}
void CP_BK::setColorBorder(COLORREF colorBorder)
{
	this->colorBorder = colorBorder;
}
COLORREF CP_BK::getColorBorder()
{
	return colorBorder;
}
void CP_BK::setColorSolid(COLORREF colorSolid)
{
	this->colorSolid = colorSolid;
}
COLORREF CP_BK::getColorSolid()
{
	return colorSolid;
}
void  CP_BK::setHeight(int height)
{
	this->height = height;
}
int  CP_BK::getHeight()
{
	return height;
}
void  CP_BK::setWidth(int width)
{
	this->width = width;
}
int  CP_BK::getWidth()
{
	return width;
}
void  CP_BK::setRectBK(RECT rectBK)
{
	this->rectBK = rectBK;
	setHeight(rectBK.bottom - rectBK.top);
	setWidth(rectBK.right - rectBK.left);
}
RECT  CP_BK::getRectBK()
{
	return rectBK;
}

//----------------------------有网的背景
void  CP_NetBK::draw(HDC hdc)
{
	CP_BK::draw(hdc);
	CP_Line line;
	if (getIsXNet())
	{
		list<CP_Line>::iterator it;
		for (it = xLines.begin(); it != xLines.end(); it++)
		{
			it->draw(hdc);
		}
	}
	if (getIsYNet())
	{
		list<CP_Line>::iterator it;
		for (it = yLines.begin(); it != yLines.end(); it++)
		{
			it->draw(hdc);
		}
	}

};
CP_NetBK::CP_NetBK()
{
	setNetWidth(1);
	setIsXNet(true);
	setIsYNet(true);
	setColorNet(RGB(7, 61, 7));                       //网格颜色
	setXOffset(15);                                //网格间距X
	setYOffset(15);                                //网格间距Y
	autoCreateXNet();
	autoCreateYNet();
}
void  CP_NetBK::setRectBK(RECT rectBK)
{
	CP_BK::setRectBK(rectBK);
	autoCreateXNet();
	autoCreateYNet();
}
void CP_NetBK::setXOffset(int xOffset)
{
	this->xOffset = xOffset;
}
int CP_NetBK::getXOffset()
{
	return xOffset;
}
void CP_NetBK::setYOffset(int yOffset)
{
	this->yOffset = yOffset;
}
int CP_NetBK::getYOffset()
{
	return yOffset;
}
//自动生成X网线
void CP_NetBK::autoCreateXNet()
{
	if (getIsXNet()) {
		while (!xLines.empty()) {
			xLines.pop_back();
		}
		int beginX = getRectBK().left;
		int endX = getRectBK().left + getWidth();
		int beginBoud = getRectBK().top;
		int endBoud = getRectBK().top + getHeight();
		CP_Line line;
		POINT pt;
		pt.x = beginX;
		pt.y = beginBoud;
		CP_Point beginPoint;
		beginPoint.setPt(pt);
		CP_Point endPoint;
		pt.x = beginX;
		pt.y = endBoud;
		endPoint.setPt(pt);
		line.setLine(beginPoint, endPoint);
		line.setColorLine(getColorNet());
		line.setWidth(getNetWidth());
		line.setIsDrawPoint(false);
		while (beginX + xOffset <= endX) {
			CP_Line tempLine = line;
			POINT pt;
			pt.x = beginX;
			pt.y = beginBoud;
			CP_Point beginPoint;
			beginPoint.setPt(pt);
			CP_Point endPoint;
			pt.x = beginX;
			pt.y = endBoud;
			endPoint.setPt(pt);
			tempLine.setLine(beginPoint, endPoint);
			xLines.push_back(tempLine);
			beginX += xOffset;
		}
	}
}
//自动生成Y网线
void CP_NetBK::autoCreateYNet()
{
	if (getIsYNet()) {
		while (!yLines.empty()) {
			yLines.pop_back();
		}
		int beginY = getRectBK().top;
		int endY = getRectBK().top + getHeight();
		int beginBoud = getRectBK().left;
		int endBoud = getRectBK().left + getWidth();
		CP_Line line;
		POINT pt;
		pt.x = beginBoud;
		pt.y = beginY;
		CP_Point beginPoint;
		beginPoint.setPt(pt);
		CP_Point endPoint;
		pt.x = endBoud;
		pt.y = endY;
		endPoint.setPt(pt);
		line.setLine(beginPoint, endPoint);
		line.setColorLine(getColorNet());
		line.setWidth(getNetWidth());
		line.setIsDrawPoint(false);
		while (beginY + yOffset <= endY) {
			CP_Line tempLine = line;
			POINT pt;
			pt.x = beginBoud;
			pt.y = beginY;
			CP_Point beginPoint;
			beginPoint.setPt(pt);
			CP_Point endPoint;
			pt.x = endBoud;
			pt.y = beginY;
			endPoint.setPt(pt);
			tempLine.setLine(beginPoint, endPoint);
			yLines.push_back(tempLine);
			beginY += yOffset;

		}
	}
}
void CP_NetBK::setNetWidth(int netWidth)
{
	this->netWidth = netWidth;
}
int CP_NetBK::getNetWidth()
{
	return netWidth;
}
void CP_NetBK::setIsYNet(BOOL isYNet)
{
	this->isYNet = isYNet;
}
BOOL CP_NetBK::getIsYNet()
{
	return isYNet;
}
void CP_NetBK::setIsXNet(BOOL isXNet)
{
	this->isXNet = isXNet;
}
BOOL CP_NetBK::getIsXNet()
{
	return isXNet;
}

void CP_NetBK::setColorNet(COLORREF colorNet)
{
	this->colorNet = colorNet;
}
COLORREF CP_NetBK::getColorNet()
{
	return colorNet;
}

//----------------------------坐标系
void CP_CorSystem::draw(HDC hdc)
{
	corBK.draw(hdc);
	xLine.draw(hdc);
	yLine.draw(hdc);
	if (getIsDrawChars())
	{
		drawChars(hdc);
	}

}
//画刻度字符
void CP_CorSystem::drawChars(HDC hdc)
{
	HFONT hFont;
	hFont = ::CreateFont(getFontSize(), 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, getStrFontName());
	::SelectObject(hdc, hFont);
	if (getIsFontBKTransparent())
	{
		::SetBkMode(hdc, TRANSPARENT);

	}
	else
	{
		::SetBkMode(hdc, OPAQUE);

	}
	::SetTextColor(hdc, getFontColor());
	TCHAR strX[64];
	TCHAR strY[64];
	SIZE sizeBeginX;
	SIZE sizeBeginY;
	double beginX = 0.0;
	double beginY = 0.0;
	int xNums = (getRectCor().right - getOriginCor().x) / xSize.cx;
	int yNums = (getOriginCor().y - getRectCor().top) / xSize.cy;
	double perX = (double)xMax / (double)xNums;
	double perY = (double)yMax / (double)yNums;

	//X轴
	for (int i = 0; i < xNums; i++)
	{
		beginX += perX;
		if (i == 0)
		{
			_stprintf(strX, TEXT("%02.1f"), beginX);
		}
		else
		{
			_stprintf(strX, TEXT(" %02.1f"), beginX);
		}
		::GetTextExtentPoint32(hdc, strX, _tcslen(strX), &sizeBeginX);
		if (i == xNums - 1)
		{
			::TextOut(hdc, getOriginCor().x + perX * (i + 1) * getXLogicUnit() - perX  * getXLogicUnit() / 2 - 15,
				getOriginCor().y + 1, strX, _tcslen(strX));
		}
		else
		{
			::TextOut(hdc, getOriginCor().x + perX * (i + 1) * getXLogicUnit() - perX  * getXLogicUnit() / 2,
				getOriginCor().y + 1, strX, _tcslen(strX));
		}
	}

	//Y轴
	for (int j = 0; j < yNums; j++)
	{
		beginY += perY;

		_stprintf(strY, TEXT(" %01.1f"), beginY);
		::GetTextExtentPoint32(hdc, strY, _tcslen(strY), &sizeBeginY);

		::TextOut(hdc, getRectCor().left + 1,
			getOriginCor().y - perY * (j + 1) * getYLogicUnit(),
			strY, _tcslen(strY));

	}
	DeleteObject(hFont);
}
CP_CorSystem::CP_CorSystem()
{
	setStrFontName(TEXT("宋体"));
	setFontSize(12);//字体大小，高度
	setFontColor(RGB(26, 230, 26));
	setIsFontBKTransparent(TRUE);//透明字体背景色
	setIsDrawChars(TRUE);
	corType = Decare;//笛卡尔坐标系
					 //坐标系屏幕位置
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 100;
	rect.bottom = 100;
	setRectCor(rect);
	POINT pt;
	pt.x = 20;
	pt.y = 20;
	setOriginLogicCor(pt);//坐标原点
						  //设置X轴最大值，Y轴最大值，并调整单位逻辑
	setXMax(250);
	setYMax(1.0);
	pt.x = 0;
	pt = corToScreenPoint(pt);
	setOriginX(pt);
	pt.y = 0;
	pt = corToScreenPoint(pt);
	setOriginY(pt);
	autoCreateXLine();
	autoCreateYLine();
	xLine.setIsDrawPoint(false);
	yLine.setIsDrawPoint(false);
	setIsAllFillNet(false);
	autoCreateCorBK();
}
void CP_CorSystem::setOriginCor(POINT originCor)
{
	this->originCor = originCor;
}
POINT CP_CorSystem::getOriginCor()
{
	return originCor;
}
//逻辑坐标系原点
void CP_CorSystem::setOriginLogicCor(POINT originLogicCor)
{
	this->originLogicCor = originLogicCor;
	setOriginCor(corToScreenPoint(originLogicCor));//坐标原点
}
POINT CP_CorSystem::getOriginLogicCor()
{
	return originLogicCor;
}
//笛卡尔坐标转屏幕坐标
POINT CP_CorSystem::corToScreenPoint(POINT pt)
{
	pt.x = getRectCor().left + pt.x;
	pt.y = getRectCor().bottom - pt.y;
	return pt;
}
//当前笛卡尔系坐标转屏幕坐标
POINT CP_CorSystem::curCorToScreenPoint(POINT pt)
{
	pt.x = getOriginCor().x + pt.x;
	pt.y = getOriginCor().y - pt.y;
	return pt;
}
//逻辑坐标转当前笛卡尔系坐标
POINT CP_CorSystem::logicCorToCurCorPoint(double x, double y)
{
	POINT pt;
	pt.x = x * getXLogicUnit();
	pt.y = y * getYLogicUnit();
	return pt;

}
//自动生成X线
void CP_CorSystem::autoCreateXLine()
{
	switch (corType)
	{
	case Decare: {
		POINT pt = getOriginX();
		pt.y = getOriginCor().y;
		CP_Point beginPoint;
		beginPoint.setPt(pt);
		CP_Point endPoint;
		pt.x = getRectCor().right;
		endPoint.setPt(pt);
		xLine.setLine(beginPoint, endPoint);
		break;
	}
	default: {
		corType = Decare;
		autoCreateXLine();
		break;
	}

	}
}
//自动生成Y线
void CP_CorSystem::autoCreateYLine()
{
	switch (corType)
	{
	case Decare: {

		POINT pt = getOriginY();
		pt.x = getOriginCor().x;
		setOriginY(pt);
		CP_Point beginPoint;
		beginPoint.setPt(pt);
		CP_Point endPoint;
		pt.y = getRectCor().top;
		endPoint.setPt(pt);
		yLine.setLine(beginPoint, endPoint);
		break;
	}
	default: {
		corType = Decare;
		autoCreateYLine();
		break;
	}

	}
}
//自动生成坐标系背景
void CP_CorSystem::autoCreateCorBK()
{
	if (getIsAllFillNet())
	{
		switch (corType)
		{
		case Decare: {
			RECT rect;
			rect.left = getRectCor().left;
			rect.top = getRectCor().top;
			rect.right = getRectCor().right;
			rect.bottom = getRectCor().bottom;
			corBK.setRectBK(rect);
			break;
		}
		default: {
			corType = Decare;
			autoCreateCorBK();
			break;
		}

		}
	}
	else
	{
		switch (corType)
		{
		case Decare: {
			RECT rect;
			rect.left = getOriginCor().x;
			rect.top = getRectCor().top;
			rect.right = getRectCor().right;
			rect.bottom = getOriginCor().y;
			corBK.setRectBK(rect);
			break;
		}
		default: {
			corType = Decare;
			autoCreateCorBK();
			break;
		}

		}
	}
}
//自动生成逻辑坐标原点
void CP_CorSystem::autoCreateOriginLogicCor(HDC hdc)
{
	HFONT hFont;
	hFont = ::CreateFont(getFontSize(), 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, getStrFontName());
	::SelectObject(hdc, hFont);
	if (getIsFontBKTransparent())
	{
		::SetBkMode(hdc, TRANSPARENT);

	}
	else
	{
		::SetBkMode(hdc, OPAQUE);

	}
	::SetTextColor(hdc, getFontColor());
	TCHAR strX[64];
	TCHAR strY[64];
	_stprintf(strX, TEXT(" %02.1f"), (double)xMax);
	_stprintf(strY, TEXT(" %01.1f"), (double)yMax);
	::GetTextExtentPoint32(hdc, strX, _tcslen(strX), &xSize);
	::GetTextExtentPoint32(hdc, strY, _tcslen(strY), &ySize);
	DeleteObject(hFont);
	POINT originPoint;
	originPoint.x = ySize.cx + 2;
	originPoint.y = xSize.cy + 2;
	setOriginLogicCor(originPoint);
}
void CP_CorSystem::setHeight(int height)
{
	this->height = height;
}
int CP_CorSystem::getHeight()
{
	return height;
}
void CP_CorSystem::setWidth(int width)
{
	this->width = width;
}
int CP_CorSystem::getWidth()
{
	return width;
}
void CP_CorSystem::setOriginX(POINT originX)
{
	this->originX = originX;
}
POINT CP_CorSystem::getOriginX()
{

	return originX;
}
void CP_CorSystem::setOriginY(POINT originY)
{
	this->originY = originY;

}
POINT CP_CorSystem::getOriginY()
{
	return originY;
}
void CP_CorSystem::setIsAllFillNet(BOOL isAllFillNet)
{
	this->isAllFillNet = isAllFillNet;
}
BOOL CP_CorSystem::getIsAllFillNet()
{
	return isAllFillNet;
}
void CP_CorSystem::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
}
int CP_CorSystem::getFontSize()
{
	return fontSize;
}
void CP_CorSystem::setFontColor(COLORREF fontColor)
{
	this->fontColor = fontColor;
}
COLORREF CP_CorSystem::getFontColor()
{
	return fontColor;
}
void CP_CorSystem::setIsFontBKTransparent(BOOL isFontBKTransparent)
{
	this->isFontBKTransparent = isFontBKTransparent;
}
BOOL CP_CorSystem::getIsFontBKTransparent()
{
	return isFontBKTransparent;
}
void CP_CorSystem::setStrFontName(TCHAR *strFontName)
{
	_tcscpy(this->strFontName, strFontName);
}
TCHAR *CP_CorSystem::getStrFontName()
{
	return strFontName;
}
void CP_CorSystem::setIsDrawChars(BOOL isDrawChars)
{
	this->isDrawChars = isDrawChars;
}
BOOL CP_CorSystem::getIsDrawChars()
{
	return isDrawChars;
}
void CP_CorSystem::setXMax(int xMax)
{
	this->xMax = xMax;
	xLogicUnit = (getRectCor().right - getOriginCor().x) / (double)xMax;//在X轴上逻辑单位像素

}
int CP_CorSystem::getXMax()
{
	return xMax;
}
void CP_CorSystem::setYMax(int yMax)
{
	this->yMax = yMax;
	yLogicUnit = (getOriginCor().y - getRectCor().top) / (double)yMax;//在Y轴上逻辑单位像素
}
int CP_CorSystem::getYMax()
{
	return yMax;
}
//在X轴上逻辑单位像素
double CP_CorSystem::getXLogicUnit()
{
	return xLogicUnit;
}
//在Y轴上逻辑单位像素
double CP_CorSystem::getYLogicUnit()
{
	return yLogicUnit;
}
//坐标系屏幕位置
void CP_CorSystem::setRectCor(RECT rectCor)
{
	this->rectCor = rectCor;
	setHeight(rectCor.bottom - rectCor.top);
	setWidth(rectCor.right - rectCor.left);
	setOriginLogicCor(getOriginLogicCor());
	POINT pt;
	pt.x = 0;
	pt = corToScreenPoint(pt);
	setOriginX(pt);
	pt.y = 0;
	pt = corToScreenPoint(pt);
	setOriginY(pt);
	autoCreateXLine();
	autoCreateYLine();
	autoCreateCorBK();
}
RECT CP_CorSystem::getRectCor()
{
	return rectCor;
}
//----------------------------线
void CP_Line::draw(HDC hdc)
{
	if (getIsDrawPoint())
	{
		leftPoint.draw(hdc);
		rightPoint.draw(hdc);
	}
	if (getIsDrawLine())
	{
		HPEN hPen;//边框画笔
		hPen = ::CreatePen(PS_SOLID, getWidth(), getColorLine());
		::SelectObject(hdc, hPen);
		::MoveToEx(hdc, leftPoint.getPt().x,
			leftPoint.getPt().y, NULL);
		::LineTo(hdc, rightPoint.getPt().x,
			rightPoint.getPt().y);
		::DeleteObject(hPen);
	}
}
void CP_Line::drawfunction(HDC hdc)
{
	if (getIsDrawPoint())
	{
		leftPoint.draw(hdc);
		rightPoint.draw(hdc);
	}
	if (getIsDrawLine())
	{
		HPEN hPen;//边框画笔
		hPen = ::CreatePen(PS_SOLID, getWidth(), getColorLine());
		::SelectObject(hdc, hPen);
		::MoveToEx(hdc, leftPoint.getPt().x,
			leftPoint.getPt().y, NULL);
		::LineTo(hdc, rightPoint.getPt().x,
			rightPoint.getPt().y);
		::DeleteObject(hPen);
	}
}
void CP_Line::setColorLine(COLORREF colorLine)
{
	this->colorLine = colorLine;
}
COLORREF CP_Line::getColorLine()
{
	return colorLine;
}
void  CP_Line::setIsDrawPoint(BOOL isDrawPoint)
{
	this->isDrawPoint = isDrawPoint;
}
BOOL  CP_Line::getIsDrawPoint()
{
	return isDrawPoint;
}
void CP_Line::setIsDrawLine(BOOL isDrawLine)
{
	this->isDrawLine = isDrawLine;
}
BOOL CP_Line::getIsDrawLine()
{
	return isDrawLine;
}
CP_Line::CP_Line()
{
	setWidth(2);                             //所画线条宽度
	setIsDrawPoint(false);
	setIsDrawLine(true);
	setColorLine(RGB(26, 230, 26));
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	leftPoint.setPt(pt);
	pt.x = 10;
	pt.y = 10;
	rightPoint.setPt(pt);
}
void CP_Line::setWidth(int width)
{
	this->width = width;
}
int CP_Line::getWidth()
{
	return width;
}
void CP_Line::setLine(CP_Point leftPoint, CP_Point rightPoint)
{
	setLeftPoint(leftPoint);
	setRightPoint(rightPoint);
}
void CP_Line::setLeftPoint(CP_Point leftPoint)
{
	this->leftPoint = leftPoint;
}
CP_Point CP_Line::getLeftPoint()
{
	return leftPoint;
}
void CP_Line::setRightPoint(CP_Point rightPoint)
{
	this->rightPoint = rightPoint;
}
CP_Point CP_Line::getRightPoint()
{
	return rightPoint;
}
CP_Line& CP_Line::operator =(CP_Line &line)
{
	setWidth(line.getWidth());
	setIsDrawPoint(line.getIsDrawPoint());
	setIsDrawLine(line.getIsDrawLine());
	setColorLine(line.getColorLine());
	leftPoint = line.getLeftPoint();
	rightPoint = line.getRightPoint();
	return *this;
}

//----------------------------点
void CP_Point::draw(HDC hdc)
{
	HBRUSH hBrush=(WHITE_BRUSH);//填充点实心的画刷
	HPEN hPen;//边框画笔
			  //画边框
	if (getIsBorder())
	{
		hPen = ::CreatePen(PS_SOLID, 1, getColorBorder());
	}
	else
	{
		hPen = ::CreatePen(PS_NULL, 1, getColorBorder());
	}
	::SelectObject(hdc, hPen);
	//填充
	if (getIsSolid())
	{
		hBrush = ::CreateSolidBrush(getColorSolid());
		::SelectObject(hdc, hBrush);
	}
	::Ellipse(hdc, getPt().x - getWidth() / 2, getPt().y - getWidth() / 2, getPt().x + getWidth() / 2, getPt().y + getWidth() / 2);
	::DeleteObject(hPen);
	if (getIsSolid())
	{
		::DeleteObject(hBrush);
	}
}

CP_Point& CP_Point::operator =(CP_Point &point)
{
	setPt(point.getPt());
	setWidth(point.getWidth());
	setIsSolid(point.getIsSolid());
	setColorBorder(point.getColorBorder());
	setColorSolid(point.getColorSolid());
	return *this;
}
CP_Point::CP_Point()
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	setPt(pt);
	setWidth(4);
	setIsSolid(true);
	setIsBorder(true);
	setColorBorder(RGB(26, 230, 26));
	setColorSolid(RGB(26, 230, 26));
}
void CP_Point::setPt(POINT point)
{
	this->pt = point;
}
POINT CP_Point::getPt()
{
	return pt;
}
void CP_Point::setWidth(int width)
{
	this->width = width;
}
int CP_Point::getWidth()
{
	return width;
}
void CP_Point::setIsSolid(BOOL isSolid)
{
	this->isSolid = isSolid;
}
void CP_Point::setIsBorder(BOOL isBorder)
{
	this->isBorder = isBorder;
}
BOOL CP_Point::getIsBorder()
{
	return isBorder;
}
BOOL CP_Point::getIsSolid()
{
	return isSolid;
}
void CP_Point::setColorBorder(COLORREF colorBorder)
{
	this->colorBorder = colorBorder;
}
COLORREF CP_Point::getColorBorder()
{
	return colorBorder;
}
void CP_Point::setColorSolid(COLORREF colorSolid)
{
	this->colorSolid = colorSolid;
}
COLORREF CP_Point::getColorSolid()
{
	return colorSolid;
}
//---------------------定义排序规则，这里按X轴顺序排列


//----------------------------显示面板
void CPanel::draw(HDC hdc, int x)
{
	list<CShape *>::iterator it;                                         
	for (it = pannelDrawList.begin(); it != pannelDrawList.end(); it++)
	{
		(*it)->draw(hdc);
	}    
	if (x == 1)
	{
		drawLines(hdc, 1);                                       
	}
	if (x == 0)
	{
		drawLines(hdc, 0);                                       
	}
}
//画两类线(1)
void CPanel::drawLines(HDC hdc,int x)
{
	if (pannelLineList.empty())
	{
		return;
	}
	list<CP_Line>::iterator it;
	//if (x == 1)
	//{
	/*	int i = 1;
		for (it = pannelLineList.begin(); it != pannelLineList.end(); it++)
		{
			if (i % 2)
			{
				it->draw(hdc);
			}
			i++;
		}*/
	//}	
//if (x == 0)
	//{
	//	
		for (it = pannelLineList.begin(); it != pannelLineList.end(); it++)
		{	
			it->draw(hdc);
		}
	//}
}

//设置面板的位置
void  CPanel::setPanelRect(RECT rect)
{
	bk.setRectBK(rect);
	corSystem.setRectCor(rect);
	finishAddDataList();
}
//设置坐标系统的位置
void CPanel::setCP_CorSystemRect(RECT rect)
{
	corSystem.setRectCor(rect);
}
//设置背景的位置
void CPanel::setBKRect(RECT rect)
{
	bk.setRectBK(rect);

}
void CPanel::setPannelDataList(list <CLogicData> *pPannelDataList)
{
	if (pPannelDataList == NULL)
	{
		return;
	}
	clearDataList();
		list<CLogicData>::iterator it_LogicData;
		for (it_LogicData = pPannelDataList->begin(); it_LogicData != pPannelDataList->end(); it_LogicData++)
		{
			pannelDataList.push_back(*it_LogicData);
		}
	
}

CP_CorSystem &CPanel::getCorSystem()
{
	return corSystem;
}
CP_BK &CPanel::getBK()
{
	return bk;
}
//点坐标列表（保存外部给出的点数据）
list <CLogicData> &CPanel::getPannelDataList()
{
	return pannelDataList;
}
//点坐标列表（内部绘图用）
list <CP_Point> &CPanel::getPannelPointList()
{
	return pannelPointList;
}
//线列表（内部绘图用）
list <CP_Line> &CPanel::getPannelLineList()
{
	return pannelLineList;
}
//清空点坐标列表（保存外部给出的点数据）
void CPanel::clearDataList()
{
	while (!pannelDataList.empty()) {
		pannelDataList.pop_back();
	}
}
//清空点坐标列表（保存外部给出的点数据）
void CPanel::clearPannelPointList()
{
	while (!pannelPointList.empty()) {
		pannelPointList.pop_back();
	}
}
//清空点坐标列表（保存外部给出的点数据）
void CPanel::clearPannelLineList()
{
	while (!pannelLineList.empty()) {
		pannelLineList.pop_back();
	}
}
//从外部添加点（坐标数据）
void CPanel::addData(double x, double y)
{
	CLogicData logicData;
	logicData.x = x;
	logicData.y = y;
	pannelDataList.push_back(logicData);
}
//完成对坐标点的添加，自动生成线和点列表
void CPanel::finishAddDataList()
{
	autoCreatePointList();                       //把点加入列表
	autoCreateLineList();                         //把加入列表的点连成线
}
//自动生成点坐标列表（内部绘图用）
void  CPanel::autoCreatePointList()
{
	if (!pannelDataList.empty())
	{
		clearPannelPointList();
	}
	else
	{
		return;
	}
	list<CLogicData>::iterator it_LogicData;
	for (it_LogicData = pannelDataList.begin(); it_LogicData != pannelDataList.end(); it_LogicData++)
	{
		POINT pt;
		pt = getCorSystem().logicCorToCurCorPoint(it_LogicData->x, it_LogicData->y);
		pt = getCorSystem().curCorToScreenPoint(pt);
		CP_Point point;
		point.setPt(pt);
		pannelPointList.push_back(point);
	}

}
//自动生成线列表（内部绘图用）
void CPanel::autoCreateLineList()
{
	if (!pannelPointList.empty())
	{
		clearPannelLineList();
	}
	else
	{
		return;
	}
	list<CP_Point>::iterator it_CP_Point;
	int listSize = pannelPointList.size();
	CP_Point leftPoint;
	CP_Point rightPoint;
	int i = 0;
	for (it_CP_Point = pannelPointList.begin(); it_CP_Point != pannelPointList.end(); it_CP_Point++)
	{
		if (i == 0)
		{
			leftPoint = *it_CP_Point;
		}
		else if (i == 1)
		{
			rightPoint = *it_CP_Point;
			CP_Line line;
			line.setLine(leftPoint, rightPoint);
			pannelLineList.push_back(line);
		}
		else
		{
			leftPoint = rightPoint;
			rightPoint = *it_CP_Point;
			CP_Line line;
			line.setLine(leftPoint, rightPoint);
			pannelLineList.push_back(line);
		}
		i++;
	}
	if (i == 1)
	{
		rightPoint = leftPoint;
		CP_Line line;
		line.setLine(leftPoint, rightPoint);
		pannelLineList.push_back(line);
	}
}
CPanel::CPanel(void)
{
	while (!pannelDrawList.empty()) {
		pannelDrawList.pop_back();
	}
	pannelDrawList.push_back(&bk);
	pannelDrawList.push_back(&corSystem);
	pCLogicDataList = NULL;
}

CPanel::~CPanel(void)
{
}
