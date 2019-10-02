
// classpen2View.cpp: Cclasspen2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "classpen2.h"
#endif

#include "classpen2Doc.h"
#include "classpen2View.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cclasspen2View

IMPLEMENT_DYNCREATE(Cclasspen2View, CView)

BEGIN_MESSAGE_MAP(Cclasspen2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SEL_COL, &Cclasspen2View::OnSelCol)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// Cclasspen2View 생성/소멸

Cclasspen2View::Cclasspen2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cclasspen2View::~Cclasspen2View()
{
}

BOOL Cclasspen2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cclasspen2View 그리기
COLORREF col;
void Cclasspen2View::OnDraw(CDC* pDC) //pdc주석해제
{
	Cclasspen2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int n = pDoc->m_oa.GetSize();
	for (int i = 0; i < n; i++) {
		CLine* p;
		p = (CLine* )pDoc->m_oa[i];
		p->Draw(pDC);
	}
}	


// Cclasspen2View 인쇄

BOOL Cclasspen2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cclasspen2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cclasspen2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cclasspen2View 진단

#ifdef _DEBUG
void Cclasspen2View::AssertValid() const
{
	CView::AssertValid();
}

void Cclasspen2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cclasspen2Doc* Cclasspen2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cclasspen2Doc)));
	return (Cclasspen2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cclasspen2View 메시지 처리기


void Cclasspen2View::OnSelCol()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		col = dlg.GetColor();
	}

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

CPoint pnt;
void Cclasspen2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point, col);
		GetDocument()->m_oa.Add(p);
		Invalidate(false); //그림그리라마
	}
	pnt = point;
	CView::OnMouseMove(nFlags, point);
}
