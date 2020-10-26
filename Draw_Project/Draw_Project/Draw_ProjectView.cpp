
// Draw_ProjectView.cpp: CDrawProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Draw_Project.h"
#endif

#include "Draw_ProjectDoc.h"
#include "Draw_ProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawProjectView

IMPLEMENT_DYNCREATE(CDrawProjectView, CView)

BEGIN_MESSAGE_MAP(CDrawProjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDrawProjectView 생성/소멸

CDrawProjectView::CDrawProjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_countLine = 0;
	m_countCircle = 0;
	m_mode = MODE_LINE;

}

CDrawProjectView::~CDrawProjectView()
{
}

BOOL CDrawProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDrawProjectView 그리기

void CDrawProjectView::OnDraw(CDC* pDC)
{
	CDrawProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < m_countCircle; i++)
	{
		pDC->Ellipse(m_circle1[i].x, m_circle1[i].y, m_circle2[i].x, m_circle2[i].y);
	}

	for (int i = 0; i < m_countLine; i++)
	{
		pDC->MoveTo(m_line1[i]);
		pDC->LineTo(m_line2[i]);
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CDrawProjectView 인쇄

BOOL CDrawProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDrawProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDrawProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDrawProjectView 진단

#ifdef _DEBUG
void CDrawProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawProjectDoc* CDrawProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawProjectDoc)));
	return (CDrawProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawProjectView 메시지 처리기


void CDrawProjectView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CDrawProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_mode = MODE_LINE;
	m_end = m_start = point;
	CView::OnLButtonDown(nFlags, point);

	
}


void CDrawProjectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_end = point;
	ReleaseCapture();
	m_line1[m_countLine] = m_start;
	m_line2[m_countLine] = m_end;
	m_countLine++;
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CDrawProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		CDC* pDC = GetDC();
		if (m_mode == MODE_LINE)
		{

			m_end = point;
			pDC->MoveTo(m_start);
			pDC->LineTo(m_end);

		}
		else
		{

			m_end = point;
			pDC->Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
		}
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CDrawProjectView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_mode = MODE_CIRCLE;
	m_end = m_start = point;
	CView::OnRButtonDown(nFlags, point);

	
}


void CDrawProjectView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_end = point;
	m_circle1[m_countCircle] = m_start;
	m_circle2[m_countCircle] = m_end;
	m_countCircle++;
	Invalidate();
	CView::OnRButtonUp(nFlags, point);

	
}
