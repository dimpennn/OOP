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

void ShapeObjectsEditor::CreateToolbar (HWND hWnd) {

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    TBBUTTON tbb[5];                         //масив опису кнопок вікна 

    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;            //стандартне зображення 
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;         //тип елементу - кнопка 
    tbb[0].idCommand = IDM_POINT;     //цей ID буде у повідомленні 

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = IDM_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = IDM_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = IDM_ELLIPSE;

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;


    hWndToolbar = CreateToolbarEx(hWnd,       //батьківське вікно 
        WS_CHILD | WS_VISIBLE | WS_BORDER
        | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,   //ID дочірнього вікна 
        //Toolbar 
        5, hInstance, IDB_BITMAP1,
        tbb,
        5,            //кількість кнопок 
        24, 24, 24, 24,      //розташування та розміри 
        sizeof(TBBUTTON));
}

void ShapeObjectsEditor::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    LPNMHDR pnmh = (LPNMHDR)lParam;

    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom) {
        case IDM_POINT:
            lstrcpy(lpttt->szText, L"Point");
            break;
        case IDM_LINE:
            lstrcpy(lpttt->szText, L"Line");
            break;
        case IDM_RECT:
            lstrcpy(lpttt->szText, L"Rectangle");
            break;
        case IDM_ELLIPSE:
            lstrcpy(lpttt->szText, L"Ellipse");
            break;
        default: lstrcpy(lpttt->szText, L"Unknown");
        }
    }
}

void ShapeObjectsEditor::OnSize(HWND hWnd) {
    RECT rc, rw;
    if (hWndToolbar) {
        GetClientRect(hWnd, &rc);          //нові розміри головного вікна 
        GetWindowRect(hWndToolbar, &rw);   //потрібно знати висоту Toolbar 
        MoveWindow(hWndToolbar, 0, 0,
            rc.right - rc.left,  //ширина Toolbar як у головного вікна 
            rw.bottom - rw.top, FALSE);
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