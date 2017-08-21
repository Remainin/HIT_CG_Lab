
// GraphLab1View.cpp : CGraphLab1View 类的实现
//

#include "stdafx.h"
#include <iostream>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GraphLab1.h"
#endif

#include "GraphLab1Doc.h"
#include "GraphLab1View.h"

#define PI 3.1415926535
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphLab1View

IMPLEMENT_DYNCREATE(CGraphLab1View, CView)

BEGIN_MESSAGE_MAP(CGraphLab1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DARYPOLYGON, &CGraphLab1View::OnDarypolygon)
	ON_COMMAND(ID_FILLPOLYGON, &CGraphLab1View::OnFillpolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLEAR, &CGraphLab1View::OnClear)
	ON_COMMAND(ID_shift, &CGraphLab1View::Onshift)
	ON_COMMAND(ID_rotate, &CGraphLab1View::Onrotate)
	ON_COMMAND(ID_magnify, &CGraphLab1View::Onmagnify)
	ON_COMMAND(ID_shrink, &CGraphLab1View::Onshrink)
	ON_COMMAND(ID_shear, &CGraphLab1View::Onshear)
	ON_COMMAND(ID_cut, &CGraphLab1View::Oncut)
	ON_COMMAND(ID_fillByLine, &CGraphLab1View::Onfillbyline)
	ON_COMMAND(ID_drawXY, &CGraphLab1View::Ondrawxy)
	ON_COMMAND(ID_syX, &CGraphLab1View::Onsyx)
	ON_COMMAND(ID_syY, &CGraphLab1View::Onsyy)
	ON_COMMAND(ID_syXY, &CGraphLab1View::Onsyxy)
	ON_COMMAND(ID_Animate, &CGraphLab1View::OnAnimate)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGraphLab1View 构造/析构

CGraphLab1View::CGraphLab1View()
{
	// TODO:  在此处添加构造代码
	m_pointNum = 0;
	m_point.clear();
}

CGraphLab1View::~CGraphLab1View()
{
}

BOOL CGraphLab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphLab1View 绘制

void CGraphLab1View::OnDraw(CDC* /*pDC*/)
{
	CGraphLab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CGraphLab1View 打印

BOOL CGraphLab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphLab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CGraphLab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CGraphLab1View 诊断

#ifdef _DEBUG
void CGraphLab1View::AssertValid() const
{
	CView::AssertValid();
}

void CGraphLab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphLab1Doc* CGraphLab1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphLab1Doc)));
	return (CGraphLab1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGraphLab1View 消息处理程序


void CGraphLab1View::OnDarypolygon()
{
	// TODO:  在此添加命令处理程序代码
	graphType = 1;
}


void CGraphLab1View::OnFillpolygon()
{
	// TODO:  在此添加命令处理程序代码
	graphType = 2;
	CDC *pDC = GetWindowDC();
	int boundary = pDC->GetPixel(m_point[0].x, m_point[0].y);
	int filledColor = RGB(255, 0, 0);
	int x = floor((((m_point[0].x + m_point[1].x) / 2) + ((m_point[1].x + m_point[2].x) / 2))/2);
	int y = floor((((m_point[0].y + m_point[1].y) / 2) + ((m_point[1].y + m_point[2].y) / 2)) / 2);
	fillBySeed(boundary, filledColor, x, y, pDC);
}

void CGraphLab1View::fillBySeed(int boundary, int filledColor, int x, int y, CDC* pDC)
{
	pDC->SetPixel(x, y, RGB(255, 0, 0));
	if (pDC->GetPixel(x - 1, y) != boundary && pDC->GetPixel(x - 1, y) != filledColor){
		fillBySeed(boundary, filledColor, x - 1, y, pDC);
	}
	if (pDC->GetPixel(x, y+1) != boundary && pDC->GetPixel(x, y+1) != filledColor){
		fillBySeed(boundary, filledColor, x, y+1, pDC);
	}
	if (pDC->GetPixel(x +1, y) != boundary && pDC->GetPixel(x + 1, y) != filledColor){
		fillBySeed(boundary, filledColor, x + 1, y, pDC);
	}
	if (pDC->GetPixel(x, y-1) != boundary && pDC->GetPixel(x, y-1) != filledColor){
		fillBySeed(boundary, filledColor, x, y-1, pDC);
	}
}

void CGraphLab1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (graphType == 1){
		m_point.push_back(point);
		m_pointNum++;
	}
	if (graphType == 3){
		m_point.push_back(point);
		m_pointNum++;
	}
	if (graphType == 4){
		if (m_pointNum == 1){
			if (point.x < m_point[0].x){
				CPoint temp = m_point[0];
				m_point.clear();
				m_point.push_back(point);
				m_point.push_back(temp);
				m_pointNum++;
			}
			else
			{
				m_point.push_back(point);
				m_pointNum++;
			}
		}
		else{
			m_point.push_back(point);
			m_pointNum++;
		}
	}
	if (graphType == 5){
		xy.push_back(point);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CGraphLab1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (graphType == 5){
		CDC *pDC = GetWindowDC();
		int x, y;
		int x0 = xy[0].x;
		int y0 = xy[1].y;
		x = x0;
		y = y0;
		for (; y >= xy[0].y; y--){
			pDC->SetPixel(x, y, RGB(255, 0, 0));
		}
		x = x0;
		y = y0;
		for (; x <= xy[1].x; x++){
			pDC->SetPixel(x, y, RGB(255, 0, 0));
		}
		xy_x = x0;
		xy_y = y0;
	}
	if (graphType == 1){
		int i;
		for (i = 0; i < m_pointNum; i++){
			int t;
			if (i < m_pointNum - 1){
				t = i + 1;
			}
			else{
				t = 0;
			}
			drawLineMid(m_point[i], m_point[t]);
			Sleep(5);
		}
	}
	//m_pointNum = 0;
	//m_point.clear();
	if (graphType == 4){
		CDC *pDC = GetWindowDC();
		judgeLocation(0, myNode);
		judgeLocation(1, myNode);
		if (myNode[0].one == 0 && myNode[1].one == 0 &&
			myNode[0].two == 0 && myNode[1].two == 0 &&
			myNode[0].three == 0 && myNode[1].three == 0 &&
			myNode[0].four == 0 && myNode[1].four == 0){
			pDC->MoveTo(m_point[0].x, m_point[0].y);
			pDC->LineTo(m_point[1].x, m_point[1].y);
		}
		else if (myNode[0].one*myNode[1].one +
			myNode[0].two*myNode[1].two +
			myNode[0].three*myNode[1].three +
			myNode[0].four*myNode[1].four >0){
			//discard
		}
		else if (myNode[0].one*myNode[1].one +		//partial in
			myNode[0].two*myNode[1].two +
			myNode[0].three*myNode[1].three +
			myNode[0].four*myNode[1].four == 0 && ((
			myNode[0].one == 0 && myNode[0].two == 0 &&
			myNode[0].three == 0 && myNode[0].four == 0)||
			(myNode[1].one == 0 && myNode[1].two == 0 &&
			myNode[1].three == 0 && myNode[1].four == 0))){
			int a = m_point[0].y - m_point[1].y;
			int b = m_point[1].x - m_point[0].x;
			int c = (m_point[0].x * m_point[1].y) - (m_point[1].x * m_point[0].y);
			int x_top =( (-1 * c - b*y_max) / a);
			int x_low = (-1 * c - b*y_min) / a;
			int y_left = (-1 * c - a*x_min) / b;
			int y_right = (-1 * c - a*x_max) / b;

			
			if (y_min - 1 <= y_left && y_left <= y_max){
				if (y_right >= y_max + 1){
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_top, y_max);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_min, y_left);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
				else if (y_right <= y_min - 1){
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_low, y_min);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_min, y_left);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
				else{
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_max, y_right);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_min, y_left);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
			}
			else if (y_left > y_max){
				if (y_right >= y_max + 1){
					//discard
				}
				else if (y_right <= y_min - 1){
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_low, y_min);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_top, y_max);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
				else{
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_max, y_right);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_top, y_max);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
			}
			else if(y_left<y_min){
				if (y_right >= y_max + 1){
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_top, y_max);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_low, y_min);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
				else if (y_right <= y_min - 1){
					//discard
				}
				else{
					if (myNode[0].one == 0 && myNode[0].two == 0 &&
						myNode[0].three == 0 && myNode[0].four == 0){
						pDC->MoveTo(m_point[0].x, m_point[0].y);
						pDC->LineTo(x_max, y_right);
					}
					if (myNode[1].one == 0 && myNode[1].two == 0 &&
						myNode[1].three == 0 && myNode[1].four == 0){
						pDC->MoveTo(x_low, y_min);
						pDC->LineTo(m_point[1].x, m_point[1].y);
					}
				}
			}
			else{
				//discard
			}
		}
		else if ((myNode[0].one*myNode[1].one +			// all out
			myNode[0].two*myNode[1].two +
			myNode[0].three*myNode[1].three +
			myNode[0].four*myNode[1].four == 0 )&&
			!(myNode[0].one == 0 && myNode[0].three == 0 &&
			myNode[0].two == 0 && myNode[0].four == 0) &&
			!(myNode[1].one == 0 && myNode[1].three == 0 &&
			myNode[1].two == 0 && myNode[1].four == 0)){
			int a = m_point[0].y - m_point[1].y;
			int b = m_point[1].x - m_point[0].x;
			int c = (m_point[0].x * m_point[1].y) - (m_point[1].x * m_point[0].y);
			int x_top = ((-1 * c - b*y_max) / a);
			int x_low = (-1 * c - b*y_min) / a;
			int y_left = (-1 * c - a*x_min) / b;
			int y_right = (-1 * c - a*x_max) / b;

			if (y_min - 1 <= y_left && y_left <= y_max){
				if (y_right >= y_max + 1){
					pDC->MoveTo(x_min, y_left);
					pDC->LineTo(x_top, y_max);
				}
				else if (y_right <= y_min - 1){
					pDC->MoveTo(x_min, y_left);
					pDC->LineTo(x_low, y_min);
				}
				else{
					pDC->MoveTo(x_min, y_left);
					pDC->LineTo(x_max, y_right);
				}
			}
			else if (y_left > y_max){
				if (y_right >= y_max + 1){
					//discard
				}
				else if (y_right <= y_min - 1){
					pDC->MoveTo(x_top, y_max);
					pDC->LineTo(x_low, y_min);
				}
				else{
					pDC->MoveTo(x_top, y_max);
					pDC->LineTo(x_max, y_right);
				}
			}
			else if(y_left<y_min){
				if (y_right >= y_max + 1){
					pDC->MoveTo(x_low, y_min);
					pDC->LineTo(x_top, y_max);
				}
				else if (y_right <= y_min - 1){
					//discard
				}
				else{
					pDC->MoveTo(x_low, y_min);
					pDC->LineTo(x_max, y_right);
				}
			}
			else{
				//discard
			}
		}
		else{
			//discard
		}
		m_point.clear();
		m_pointNum = 0;
	}
	if (graphType == 3){
		CDC *pDC = GetWindowDC();
		int x0, y0,x1,y1;
		if (m_point[0].x <= m_point[1].x){
			x0 = m_point[0].x;
			x1 = m_point[1].x;
		}
		else{
			x1 = m_point[0].x;
			x0 = m_point[1].x;
		}
		if (m_point[0].y <= m_point[1].y){
			y0 = m_point[0].y;
			y1 = m_point[1].y;
		}
		else{
			y1 = m_point[0].y;
			y0 = m_point[1].y;
		}

		int x, y;

		for (x = x0,y = y0; x <= x1; x++){
			pDC->SetPixel(x, y, RGB(0, 255, 0));
		}
		for (x = x1, y = y0; y <= y1; y++){
			pDC->SetPixel(x, y, RGB(0, 255, 0));
		}
		for (x = x1, y = y1; x >= x0; x--){
			pDC->SetPixel(x, y, RGB(0, 255, 0));
		}
		for (x = x0, y = y1; y >= y0; y--){
			pDC->SetPixel(x, y, RGB(0, 255, 0));
		}

		x_min = x0;
		x_max = x1;
		y_min = y0;
		y_max = y1;
		m_point.clear();
		m_pointNum = 0;
		graphType = 4;
	}
	CView::OnRButtonDown(nFlags, point);
}

void CGraphLab1View::judgeLocation(int number, Node myNode[]){
	int x, y;
	x = m_point[number].x;
	y = m_point[number].y;
	if (y > y_max){
		myNode[number].one = 1;
	}
	else{
		myNode[number].one = 0;
	}
	if (y < y_min){
		myNode[number].two = 1;
	}
	else{
		myNode[number].two = 0;
	}
	if (x > x_max){
		myNode[number].three = 1;
	}
	else{
		myNode[number].three = 0;
	}
	if (x < x_min){
		myNode[number].four = 1;
	}
	else{
		myNode[number].four = 0;
	}
}


void CGraphLab1View::drawLineMid(CPoint p1, CPoint p2)
{
	CDC *pDC = GetWindowDC();
	/*for (int i = 100; i < 500; i++){
		pDC->SetPixel(CPoint(i, 100), RGB(255, 0, 0));
	}*/
	//pDC->MoveTo(p1);
	//pDC->LineTo(p2);
	if (p1.x > p2.x){
		swap(p1.x, p2.x);
		swap(p1.y, p2.y);
	}
	int x = p1.x;
	int y = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;
	if (x > x2){
		swap(x, x2);
		swap(y, y2);
	}
	int a = y - y2;
	int b = x2 - x;
	int c = (x*y2) - (x2*y);
	int d;
	if (a*b < 0){
		if (abs(a) <= abs(b)){
			d = 2 * a + b;
			int i = 0;
			for (; x <= x2; i++){
				pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
				Sleep(1);
				if (d >= 0){
					x = x + 1;
					d = d + 2*a;
					continue;
				}
				else{
					d = d + 2*a + 2*b;
					x = x + 1;
					y = y + 1;
					continue;
				}
			}
		}
		else{
			d = a + 2*b;
			int i = 0;
			for (; y <= y2; i++){
				pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
				Sleep(1);
				if (d > 0){
					x = x + 1;
					y = y + 1;
					d = d + 2*a+2*b;
					continue;
				}
				else{
					d = d +2*b;
					y = y + 1;
					continue;
				}
			}
		}
	}
	if (a*b > 0){
		
		if (abs(a) <= abs(b)){
			d = 2 * a - b;
			int i = 0;
			for (; x <= x2; i++){
				pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
				Sleep(1);
				if (d >= 0){
					d = d + 2 * a - 2 * b;
					x = x + 1;
					y = y - 1;
					continue;
				}
				else{
					x = x + 1;
					d = d + 2 * a;
					continue;
				}
			}
		}
		else{
			d = -a + 2 * b;
			int i = 0;
			for (; y >= y2; i++){
				pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
				Sleep(1);
				if (d > 0){
					d = d - 2 * b;
					y = y - 1;
					continue;
				}
				else{
					x = x + 1;
					y = y - 1;
					d = d + 2 * a - 2 * b;
					continue;
				}
			}
		}
	}
	if (a == 0){
		int i = 0;
		for (; x <= x2; i++){
			pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
			x++;
		}
	}
	if (b == 0){
		int i = 0;
		int temp;
		if (y > y2){
			temp = y2;
			y2 = y;
			y = temp;
		}
		for (; y <= y2; i++){
			pDC->SetPixel(CPoint(x, y), RGB(0, 255, 0));
			y++;
		}
	}
}


void CGraphLab1View::OnClear()
{
	// TODO:  在此添加命令处理程序代码
	CDC* pDC;
	pDC = GetWindowDC();

	m_point.clear();
	m_pointNum = 0;

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
}



void CGraphLab1View::Onshift()
{
	// TODO:  在此添加命令处理程序代码
	int i = xy_x - m_point[0].x;
	int j = xy_y - m_point[0].y;
	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		if (k == 0){
			pDC->MoveTo(m_point[k].x + i, m_point[k].y + j);
		}
		else if (k <= m_pointNum - 1){
			pDC->LineTo(m_point[k].x + i, m_point[k].y + j);
		}
		else{
			pDC->LineTo(m_point[0].x + i, m_point[0].y + j);
		}
	}

}


void CGraphLab1View::Onrotate()
{
	// TODO:  在此添加命令处理程序代码
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x*cos(PI / 2) - y*sin(PI / 2)-i;
			changed_y = x*sin(PI / 2) + y*cos(PI / 2)-j;
			pDC->MoveTo(changed_x,changed_y);
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x*cos(PI / 2) - y*sin(PI / 2) - i;
			changed_y = x*sin(PI / 2) + y*cos(PI / 2) - j;
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGraphLab1View::Onmagnify()
{
	// TODO:  在此添加命令处理程序代码
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x * 2-i;
			changed_y = y * 2-j;
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGraphLab1View::Onshrink()
{
	// TODO:  在此添加命令处理程序代码
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x * 0.5 - i;
			changed_y = y * 0.5 - j;
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGraphLab1View::Onshear()
{
	// TODO:  在此添加命令处理程序代码
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x+(y/tan(PI/4)) - i;
			changed_y = y-j;
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}

void CGraphLab1View::Onsyx()
{
	// TODO:  在此添加命令处理程序代码

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x, m_point[k].y + 2*(xy_y - m_point[k].y));
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x;
			y = m_point[k].y;
			changed_x = x;
			changed_y = y + 2 * (xy_y - m_point[k].y);
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x, m_point[0].y+ 2 * (xy_y - m_point[0].y));
		}
	}
}

void CGraphLab1View::Onsyy()
{
	// TODO:  在此添加命令处理程序代码
	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x+ 2 * (xy_x - m_point[k].x), m_point[k].y);
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x;
			y = m_point[k].y;
			changed_x = x + 2 * (xy_x - m_point[k].x);
			changed_y = y;
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x + 2 * (xy_x - m_point[0].x), m_point[0].y);
		}
	}
}

void CGraphLab1View::Onsyxy()
{
	// TODO:  在此添加命令处理程序代码
	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++){
		int x, y;
		int changed_x, changed_y;
		if (k == 0){
			pDC->MoveTo(m_point[k].x + 2 * (xy_x - m_point[k].x), m_point[k].y + 2 * (xy_y - m_point[k].y));
		}
		else if (k <= m_pointNum - 1){
			x = m_point[k].x;
			y = m_point[k].y;
			changed_x = x + 2 * (xy_x - m_point[k].x);
			changed_y = y + 2 * (xy_y - m_point[k].y);
			pDC->LineTo(changed_x, changed_y);
		}
		else{
			pDC->LineTo(m_point[0].x + 2 * (xy_x - m_point[0].x), m_point[0].y + 2 * (xy_y - m_point[0].y));
		}
	}
}


void CGraphLab1View::Oncut()
{
	// TODO:  在此添加命令处理程序代码
	graphType = 3;

}



void CGraphLab1View::Onfillbyline()
{
	// TODO:  在此添加命令处理程序代码
	CDC* pDC;
	pDC = GetWindowDC();
	int ymin, ymax, xmax, xmin;
	ymin = m_point[0].y;
	ymax = m_point[0].y;
	xmax = m_point[0].x;
	xmin = m_point[0].x;
	for (int i = 1; i < m_pointNum; i++){
		if (m_point[i].x < xmin){
			xmin = m_point[i].x;
		}
		if (m_point[i].x > xmax){
			xmax = m_point[i].x;
		}
		if (m_point[i].y < ymin){
			ymin = m_point[i].y;
		}
		if (m_point[i].y > ymax){
			ymax = m_point[i].y;
		}
	}
	int x, y;
	int judgenow,flag;
	y = ymin+3;
	for (; y < ymax-1; y++){
		x = xmin-1;
		judgenow = 0;
		flag = 0;
		for (; x < xmax; x++){
			if (judgenow % 2 == 0 && flag == 1 && pDC->GetPixel(x, y) == RGB(0, 255, 0)){
				continue;
			}
			if (judgenow % 2 == 0){
				flag = 0;
			}
			if (judgenow % 2 == 1 && flag == 1 && pDC->GetPixel(x, y) == RGB(0, 255, 0)){
				continue;
			}
			if (pDC->GetPixel(x, y) == RGB(0, 255, 0)){
				judgenow++;
				flag = 1;
				continue;
			}
			if (judgenow % 2 == 1){
				flag = 0;
				pDC->SetPixel(x, y, RGB(255, 0, 0));
			}
		}
	}
}


void CGraphLab1View::Ondrawxy()
{
	// TODO:  在此添加命令处理程序代码
	graphType = 5;
}


void CGraphLab1View::OnAnimate()
{
	// TODO:  在此添加命令处理程序代码
	m_radius = 100;

	m_animX = m_radius;
	m_animY = m_radius+100;

	m_stepX = 5;

	SetTimer(1, 50, NULL);
}


void CGraphLab1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rect;

	m_pDC = GetWindowDC();
	GetClientRect(rect);
	m_animX += m_stepX;
	if (m_animX + m_radius >= rect.right - m_radius){
		m_stepX = -m_stepX;
	}
	if (m_animX - m_radius <= rect.left){
		m_stepX = -m_stepX;
	}
	m_brush.CreateSolidBrush(RGB(m_animX / 2 * m_animY / 2 %256 , 0, 0));
	m_backbrush.CreateSolidBrush(RGB(m_animX * 77 % 256, m_animY * 37 % 256, m_animX * 13 % 256));
	m_pDC->FillRect(rect, &m_backbrush);
	//m_pDC->SelectObject(m_brush);


	CRect my = { m_animX-m_radius, m_animY-m_radius, m_animX+m_radius, m_animY+m_radius };

	CFont font;

	font.CreateFont(
		50, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial") // nPitchAndFamily Arial
		);
	m_pDC->SelectObject(&font);
	m_pDC->SetTextColor(RGB(m_animX%256, m_animY%256, m_animX*m_animY%256));

	m_pDC->SetBkColor(RGB(0, 0, 0));

	m_pDC->DrawText(_T("张茗帅"), &my, DT_CENTER);

	m_pDC->SelectObject(m_brush);
	m_pDC->Ellipse(m_animX - 53, m_animY+60, m_animX -27, m_animY +80);
	m_pDC->Ellipse(m_animX , m_animY + 60, m_animX+26, m_animY + 80);
	
	m_pDC->Ellipse(m_animX - 23, m_animY + 85, m_animX - 4, m_animY + 95);
	ReleaseDC(m_pDC);
	m_brush.DeleteObject();
	m_backbrush.DeleteObject();


	CView::OnTimer(nIDEvent);
}
