
// Draw_ProjectView.h: CDrawProjectView 클래스의 인터페이스
//

#pragma once


class CDrawProjectView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDrawProjectView() noexcept;
	DECLARE_DYNCREATE(CDrawProjectView)

// 특성입니다.
public:
	CDrawProjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDrawProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint m_circle1[100];
	CPoint m_circle2[100];
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	CPoint m_line1[100];
	CPoint m_line2[100];
	CPoint m_start;
	CPoint m_end;
	enum { MODE_LINE, MODE_CIRCLE };
	int m_mode;
	int m_countLine;
	int m_countCircle;
};

#ifndef _DEBUG  // Draw_ProjectView.cpp의 디버그 버전
inline CDrawProjectDoc* CDrawProjectView::GetDocument() const
   { return reinterpret_cast<CDrawProjectDoc*>(m_pDocument); }
#endif

