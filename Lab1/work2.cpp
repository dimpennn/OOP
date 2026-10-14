#include "pch.h"
#include "framework.h"
#include "work2.h"

WCHAR szGroup[MAX_LOADSTRING] = { 0 };
UINT indx;
WCHAR IM_o51[10] = L"IM - o51";

INT_PTR CALLBACK Work2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Func_MOD3(HWND hWnd) {
    return DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Work2);
}

INT_PTR CALLBACK Work2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendDlgItemMessageW(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)IM_o51);
        for (int i = 51; i <= 55; i++) {
            wsprintfW(szGroup, L"IM-%d", i);
            SendDlgItemMessageW(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)szGroup);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDOK:
            indx = SendDlgItemMessageW(hDlg, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessageW(hDlg, IDC_LIST1, LB_GETTEXT, indx, (LPARAM)szGroup);
            EndDialog(hDlg, IDOK);
            return (INT_PTR)TRUE;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}
