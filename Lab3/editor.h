#pragma once

#include "Resource.h"

class Editor
{
public:
	Editor();
	virtual ~Editor();
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	void OnPaint(HWND);
};

class ShapeEditor : public Editor
{
protected:
	bool isDrawing = false;
	long xstart, ystart, xend, yend;
public:
	ShapeEditor(void);
	virtual ~ShapeEditor();
	void OnLBdown(HWND) override;
	void OnLBup(HWND) override;
	void OnMouseMove(HWND) override;
	void OnPaint(HWND);
};

class PointEditor : public ShapeEditor
{
	void OnLBdown(HWND) override;
};

class LineEditor : public ShapeEditor
{
	void OnLBdown(HWND) override;
	void OnLBup(HWND) override;
	void OnMouseMove(HWND) override;
};

class RectEditor : public ShapeEditor
{
	void OnLBdown(HWND) override;
	void OnLBup(HWND) override;
	void OnMouseMove(HWND) override;
};

class EllipseEditor : public ShapeEditor
{
	void OnLBdown(HWND) override;
	void OnLBup(HWND) override;
	void OnMouseMove(HWND) override;
};
