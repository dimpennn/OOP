#include "pch.h"
#include "framework.h"
#include "editor.h"
#include "shape.h"

extern Shape* pcshape[MAX_SHAPES_COUNT];
extern int nCurrentShapeCount;

Editor::Editor() {}
Editor::~Editor() {}

ShapeEditor::ShapeEditor() : xstart(0), ystart(0), xend(0), yend(0) {}
ShapeEditor::~ShapeEditor() {}

void ShapeEditor::OnLBdown(HWND hWnd) {
	isDrawing = true;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = xend = pt.x;
	ystart = yend = pt.y;
}

void ShapeEditor::OnLBup(HWND hWnd) {}

void ShapeEditor::OnMouseMove(HWND hWnd) {}

void ShapeEditor::OnPaint(HWND hWnd) {}

// PointEditor
void PointEditor::OnLBdown(HWND hWnd) {
	ShapeEditor::OnLBdown(hWnd);
	PointShape* pSh = new PointShape();
	pSh->Set(xstart, ystart, xend, yend);

	for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
		if (pcshape[i] == nullptr) {
			pcshape[i] = pSh;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

// LineEditor
void LineEditor::OnLBdown(HWND hWnd) {
	ShapeEditor::OnLBdown(hWnd);
}

void LineEditor::OnLBup(HWND hWnd) {
	isDrawing = false;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	LineShape* pSh = new LineShape();
	pSh->Set(xstart, ystart, xend, yend);

	for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
		if (pcshape[i] == nullptr) {
			pcshape[i] = pSh;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void LineEditor::OnMouseMove(HWND hWnd) {
	if (!isDrawing) return;

	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xstart, ystart, NULL);
	LineTo(hdc, xend, yend);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	MoveToEx(hdc, xstart, ystart, NULL);
	LineTo(hdc, xend, yend);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

// RectEditor
void RectEditor::OnLBdown(HWND hWnd) {
	ShapeEditor::OnLBdown(hWnd);
}

void RectEditor::OnLBup(HWND hWnd) {
	isDrawing = false;
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	RectShape* pSh = new RectShape();
	pSh->Set(xstart, ystart, xend, yend);

	for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
		if (pcshape[i] == nullptr) {
			pcshape[i] = pSh;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void RectEditor::OnMouseMove(HWND hWnd) {
	if (!isDrawing) return;

	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc, xstart, ystart, xend, yend);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	Rectangle(hdc, xstart, ystart, xend, yend);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

// EllipseEditor
void EllipseEditor::OnLBdown(HWND hWnd) {
	ShapeEditor::OnLBdown(hWnd);
}

void EllipseEditor::OnLBup(HWND hWnd) {
	isDrawing = false;
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	EllipseShape* pSh = new EllipseShape();
	pSh->Set(xstart, ystart, xend, yend);

	for (int i = 0; i < MAX_SHAPES_COUNT; i++) {
		if (pcshape[i] == nullptr) {
			pcshape[i] = pSh;
			break;
		}
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void EllipseEditor::OnMouseMove(HWND hWnd) {
	if (!isDrawing) return;

	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	long xcentr_old = (2 * xstart) - xend;
	long ycentr_old = (2 * ystart) - yend;

	Ellipse(hdc, xcentr_old, ycentr_old, xend, yend);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	long xcentr_new = (2 * xstart) - xend;
	long ycentr_new = (2 * ystart) - yend;

	Ellipse(hdc, xcentr_new, ycentr_new, xend, yend);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}
