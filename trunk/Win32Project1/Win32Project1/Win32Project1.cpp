// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "Edmonds-Karp", CS_BYTEALIGNWINDOW|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
#define BUTTON_ID      1001



//void functie()
//{char szFileName[MAX_PATH];
//	HWND hwnd;
//GetModuleFileName(hInstance, szFileName, MAX_PATH);
//MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
//
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HWND hButton;

	switch (message)
	{
		case WM_CREATE:
      
       hButton = CreateWindow( "button", "?",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                980, 450, 
                20, 20,
                hWnd, (HMENU) BUTTON_ID,
                hInst, NULL );

	   hButton = CreateWindow( "button", "Start",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 10, 
                70, 20,
                hWnd, (HMENU) 1,
                hInst, NULL );

	    hButton = CreateWindow( "button", "Adauga",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 40, 
                70, 20,
                hWnd, (HMENU) 2,
                hInst, NULL );
		
		hButton = CreateWindow( "button", "Stergere",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 70, 
                70, 20,
                hWnd, (HMENU) 3,
                hInst, NULL );

		hButton = CreateWindow( "button", "Atrib/Modif",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 100, 
                70, 20,
                hWnd, (HMENU) 4,
                hInst, NULL );

		hButton = CreateWindow( "button", "Help!",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 130, 
                70, 20,
                hWnd, (HMENU) 5,
                hInst, NULL );

		hButton = CreateWindow( "button", "Exit",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 160, 
                70, 20,
                hWnd, (HMENU) 6,
                hInst, NULL );

      break;


	  hdc=GetDC(hWnd);
// funcţii de desenare
ReleaseDC(hWnd,hdc);

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 5:
			
		
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case 6:
			DestroyWindow(hWnd);
			break;
		case BUTTON_ID:
			MessageBox(0,"Proiect realizat de \n Mihai Florea \n Sava Marius","INFORMATII",0);//functie pentru buton
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
