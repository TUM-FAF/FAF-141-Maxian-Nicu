// lab4wp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "lab4wp.h"

#define MAX_LOADSTRING 100
#define TIMER_UPDATE 1

vector<Figure> figures;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



void collideWindowRect(Figure *figure,HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	if (figure->collidesHorizontalLine(0) || figure->collidesHorizontalLine(rect.bottom - rect.top)) {
		figure->invertVelocityY();
		figure->increaseVelocity();
	}
	if (figure->collidesVerticalLine(0) || figure->collidesVerticalLine(rect.right - rect.left)) {
		figure->invertVelocityX();
		figure->flipFigure();
	}
}

int checkFigureCollide(Figure *figure)
{
	int count = 0;
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		Figure *second = &(*it);
		if(figure != second)
			if(figure->collides(*second)){
				if (figure->getX() < second->getX()) {
					figure->invertVelocityX();
				}
				if (figure->getY() < second->getY()) {
					figure->invertVelocityY();
				}
				figure->update();

				if (figure->getType() == second->getType())
				{
					figure->setRandomColor();
					second->setRandomColor();
					count++;
				}
			}
	}
	
	return count;
}


void createRandomFigure(HWND hWnd,int x=-1,int y = -1)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	Figure figure(15 + rand() % 10, 50 + rand() % (rect.right - rect.left - 100), 50 + rand() % (rect.bottom - rect.top - 100));
	figure.setRandomColor();
	figure.setRandomVelocity();
	figure.setRandomRadius();
	if (rand() % 2 == 0)
		figure.setCircle();
	else
		figure.setSquare();
	
	if(x != -1 && y != -1)
	{
		figure.setPosition(x, y);
	} else
	{
		while (checkFigureCollide(&figure))
		{
			figure.setPosition(50 + rand() % (rect.right - rect.left - 100), 50 + rand() % (rect.bottom - rect.top - 100));
		}
	}
	figures.push_back(figure);
}

void update(HWND hWnd)
{

	RECT rect;
	GetClientRect(hWnd, &rect);

	int count = 0;

	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		Figure *figure = &(*it);
		figure->update();
		collideWindowRect(figure, hWnd);
		count += checkFigureCollide(figure);
	}
	for (int i = 0; i < count; i++)
	{
		if (figures.size() < 10)
			createRandomFigure(hWnd);
	}
	InvalidateRect(hWnd, &rect, false);
}


VOID OnPaint(HDC hdc)
{
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		Figure figure = *it;
		figure.paint(hdc);
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4WP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4WP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4WP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


void changeSpeed(bool increase)
{
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		Figure *figure = &(*it);
		if (increase)
			figure->increaseVelocity();
		else
			figure->decreaseVelocity();
	}
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdcMem;
	RECT rect;
	HBITMAP hbmMem;
	int width;
	int height;
	HANDLE hOld;


	switch (message)
	{
	case WM_CREATE:{
		SetTimer(hWnd,             // handle to main window 
			TIMER_UPDATE,            // timer identifier 
			40,                 // 25 frames per seconds
			(TIMERPROC)NULL);
		for (int i = 0; i < 3; i++) {
			createRandomFigure(hWnd);
		}
		break;
	}
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_UPDATE:
			update(hWnd);
			break;
		}
		break;
	case WM_MOUSEWHEEL: {
		int zDelta = (short)HIWORD(wParam);
		if(zDelta > 0)
			changeSpeed(true);
		else
			changeSpeed(false);
		break;
	}
    case WM_PAINT:
        {
			GetClientRect(hWnd, &rect);
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;

			hdc = BeginPaint(hWnd, &ps);

			// Create an off-screen DC for double-buffering
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, width, height);

			hOld = SelectObject(hdcMem, hbmMem);
			OnPaint(hdcMem);

			// Transfer the off-screen DC to the screen
			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

			// Free-up the off-screen DC
			SelectObject(hdcMem, hOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);
			return 0;

        }
        break;
	case WM_LBUTTONDOWN: {
		createRandomFigure(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	}
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
