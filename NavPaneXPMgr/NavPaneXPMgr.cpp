#include "stdafx.h"
#include "resource.h"
#include "helpers.h"
#include "..\navpanexp\settings.h"

#include "Commctrl.h"
#pragma comment(lib,"Comctl32.lib")


void OnApplySettings(HWND hDlg)
{
	DWORD dwSettings=0;

	dwSettings|=(BST_CHECKED==Button_GetCheck(GetDlgItem(hDlg, IDC_FAVPANE))) ? OPT_FAVPANE : 0;
	dwSettings|=(BST_CHECKED==Button_GetCheck(GetDlgItem(hDlg, IDC_FLDRPANE))) ? OPT_FLDRPANE : 0;
	dwSettings|=(BST_CHECKED==Button_GetCheck(GetDlgItem(hDlg, IDC_FOCUS))) ? OPT_FOCUS : 0;

	if (!ApplySettings(dwSettings)) MessageBeep(MB_ICONERROR);

}



//window proc for "framed white background" control
WNDPROC pOldWndProc;
LRESULT CALLBACK StaticBkgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg==WM_PAINT)
	{
		if (GetUpdateRect(hWnd, NULL, FALSE))
		{
			PAINTSTRUCT pPaint;
			HDC hDc=BeginPaint(hWnd, &pPaint);
			if (hDc)
			{
				RECT rc;
				if (GetClientRect(hWnd, &rc))
				{
					FillRect(hDc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					FrameRect(hDc, &rc, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
				}
			}
			EndPaint(hWnd, &pPaint);
		}
	return 0;
	}
return CallWindowProc(pOldWndProc, hWnd, uMsg, wParam, lParam);
}





INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			DBGTRACE("WM_INITDIALOG\n");

			//set dlg icon
			HICON hIcon = (HICON)::LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINDLG), 
				IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
			if (hIcon) SendMessage(hDlg, WM_SETICON, TRUE, (LPARAM)hIcon);
			HICON hIconSmall = (HICON)::LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAINDLG), 
				IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
			if (hIconSmall) SendMessage(hDlg, WM_SETICON, FALSE, (LPARAM)hIconSmall);

			DWORD dwsettings;
			LoadSettings(&dwsettings);
			Button_SetCheck(GetDlgItem(hDlg, IDC_FAVPANE), (dwsettings & OPT_FAVPANE));
			Button_SetCheck(GetDlgItem(hDlg, IDC_FLDRPANE), (dwsettings & OPT_FLDRPANE));
			Button_SetCheck(GetDlgItem(hDlg, IDC_FOCUS), (dwsettings & OPT_FOCUS));


			pOldWndProc = (WNDPROC)SetWindowLongPtr(GetDlgItem(hDlg, IDC_STATICBKG), GWLP_WNDPROC, (LONG_PTR)StaticBkgProc);
			CenterWindow(hDlg);
		}
		return (INT_PTR)TRUE;

	case WM_CTLCOLORSTATIC:
		switch (GetDlgCtrlID((HWND)lParam))
		{
			//controls on white bkg
			case IDC_COPYRIGHT:
				SetTextColor((HDC)wParam,GetSysColor(COLOR_GRAYTEXT));
			case IDC_STATICBKG:
			case IDC_GROUP1:
			case IDC_FAVPANE:
			case IDC_FLDRPANE:
			case IDC_FOCUS:
			case IDC_CUSTOM1:
			case IDC_CUSTOM2:
			case IDC_CUSTOM3:
				return (UINT_PTR)GetStockObject(WHITE_BRUSH);
		default:break;
		}
		break;

	case WM_COMMAND:
		switch LOWORD(wParam)
		{
			//RADIOBUTTON (not AUTORADIOBUTTON) buttons need settings state manualy
			case IDC_FAVPANE:
			case IDC_FLDRPANE:
				if (HIWORD(wParam)==BN_CLICKED)
				{
					BOOL bstate=!((BOOL)Button_GetCheck((HWND)lParam));
					if (bstate==BST_CHECKED)
					{
						Button_SetCheck(GetDlgItem(hDlg, IDC_FAVPANE), BST_UNCHECKED);
						Button_SetCheck(GetDlgItem(hDlg, IDC_FLDRPANE), BST_UNCHECKED);						
					}
					Button_SetCheck((HWND)lParam, bstate);
				}
				break;

			case IDC_APPLY:
				OnApplySettings(hDlg);
				break;
			case IDOK:
				OnApplySettings(hDlg);//apply and fallthrough
			case IDCANCEL:
				DBGTRACE("EndDialog\n");
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
		default:break;
		}

	break;
	}
return (INT_PTR)FALSE;
}


//main
#ifdef _ATL_MIN_CRT //release build
int WINAPI WinMainCRTStartup(void)//no crt
#else
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
#endif
{
	INITCOMMONCONTROLSEX cc;
	cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
	cc.dwICC=ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&cc);

	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAINDLG), HWND_DESKTOP, DlgProc);

#ifdef _ATL_MIN_CRT
	ExitProcess(0);
#endif
return 0;
}
