#include "pch.h"
#include "framework.h"
#include "shape_editor.h"
#include "editor.h"
#include "shape.h"

Shape* pcshape[MAX_SHAPES_COUNT] = { nullptr };

ShapeObjectsEditor::ShapeObjectsEditor() {
    pse = nullptr;
}

ShapeObjectsEditor::~ShapeObjectsEditor() {
    if (pse) {
        delete pse;
        pse = nullptr;
    }
    for (int i = 0; i < MAX_SHAPES_COUNT; i++)
    {
        if (pcshape[i])
        {
            delete pcshape[i];
            pcshape[i] = nullptr;
        }
    }
}

void ShapeObjectsEditor::StartPointEditor() {
    if (pse)
        delete pse;
    pse = new PointEditor();
    currentMenu = IDM_POINT;
}

void ShapeObjectsEditor::StartLineEditor() {
    if (pse)
        delete pse;
    pse = new LineEditor();
    currentMenu = IDM_LINE;
}

void ShapeObjectsEditor::StartRectEditor() {
    if (pse)
        delete pse;
    pse = new RectEditor();
    currentMenu = IDM_RECT;
}

void ShapeObjectsEditor::StartEllipseEditor() {
    if (pse)
        delete pse;
    pse = new EllipseEditor();
    currentMenu = IDM_ELLIPSE;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd) {
    if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd) {
    if (pse) pse->OnLBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd) {
    if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) {

    if (pse) pse->OnPaint(hWnd);

    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(hWnd, &ps);
    for (int i = 0; i < MAX_SHAPES_COUNT; i++)
        if (pcshape[i])
            pcshape[i]->Show(hdc);
    EndPaint(hWnd, &ps);
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) {
    HMENU hMenu = GetMenu(hWnd);
    HMENU hSubMenu = GetSubMenu(hMenu, 1);

    if ((HMENU)wParam == hSubMenu) {
        CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);

        if (currentMenu) CheckMenuItem(hSubMenu, currentMenu, MF_CHECKED);
    }
}