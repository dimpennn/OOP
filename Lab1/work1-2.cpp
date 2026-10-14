#include "pch.h"
#include "framework.h"
#include "work1-2.h"

INT_PTR CALLBACK Work1_2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Func_MOD2(HWND hWnd) {
    return DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Work1_2);
}

INT_PTR CALLBACK Work1_2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDOK:
            EndDialog(hDlg, IDOK);
            return (INT_PTR)TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return (INT_PTR)TRUE;
        case IDPREVIOUS:
            EndDialog(hDlg, IDPREVIOUS);
            return (INT_PTR)TRUE;
        default:
            break;
        }
    }
    return (INT_PTR)FALSE;
}
