#pragma once
#include <afx.h>
class CLine :
	public CObject
{
	CPoint m_From, m_To;
	COLORREF m_col;
public:
	CLine() {};
	CLine(CPoint From, CPoint To, COLORREF Col) {
		m_From = From;
		m_To = To;
		m_col = Col;
	}
	void Draw(CDC* pDC) {
		CPen pen(PS_SOLID, 16, m_col);
		pDC->SelectObject(&pen);
		pDC->MoveTo(m_From);
		pDC->LineTo(m_To);
		
	}
};

