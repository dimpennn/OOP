#pragma once

#include "Resource.h"

class ShapeEditor;

class ShapeObjectsEditor
{
private:
	ShapeEditor* pse = nullptr;
	int currentMenu = 0;
	HWND hWndToolbar = nullptr;
public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();
	void CreateToolbar(HWND);
	void OnNotify(HWND, WPARAM, LPARAM);
	void OnSize(HWND);
	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};
