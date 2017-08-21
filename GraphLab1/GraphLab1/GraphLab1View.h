
// GraphLab1View.h : CGraphLab1View 类的接口
//

using namespace std;
#pragma once

#include <vector>

class CGraphLab1View : public CView
{
protected: // 仅从序列化创建
	CGraphLab1View();
	DECLARE_DYNCREATE(CGraphLab1View)

// 特性
public:
	CGraphLab1Doc* GetDocument() const;
	typedef struct{
		int one, two, three, four;
	}Node;
	Node myNode[2];
	int y_max, x_max, x_min, y_min;
	int xy_x, xy_y;
	int m_pointNum;
	int graphType;
	int m_radius, m_animX, m_animY, m_stepX, m_stepY;
	CBrush m_brush, m_backbrush;
	CDC* m_pDC;
	vector<CPoint> m_point;
	vector<CPoint> xy;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphLab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDarypolygon();
	afx_msg void OnFillpolygon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void drawLineMid(CPoint p1,CPoint p2);
	afx_msg void OnClear();
	void fillBySeed(int boundary,int filledColor, int x,int y,CDC* p);
	afx_msg void Onshift();
	afx_msg void Onrotate();
	afx_msg void Onmagnify();
	afx_msg void Onshrink();
	afx_msg void Onshear();
	afx_msg void Oncut();
	void judgeLocation(int number,Node myNode[]);
	afx_msg void Onfillbyline();
	afx_msg void Ondrawxy();
	afx_msg void Onsyx();
	afx_msg void Onsyy();
	afx_msg void Onsyxy();
	afx_msg void OnAnimate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // GraphLab1View.cpp 中的调试版本
inline CGraphLab1Doc* CGraphLab1View::GetDocument() const
   { return reinterpret_cast<CGraphLab1Doc*>(m_pDocument); }
#endif

