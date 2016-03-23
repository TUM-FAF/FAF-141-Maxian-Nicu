// Lab3WP.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab3WP.h"
#include <vector>

#define MAX_LOADSTRING 100

COLORREF colors[NUMBER_OF_COLORS] = {
	RGB(0, 0, 0),
	RGB(255, 0, 0),
	RGB(0, 255, 0),
	RGB(0, 0, 255),
	RGB(255, 0, 255)
};
int currentColor = 0;
Drawing *drawing;
Drawing *pendingDrawing;
std::vector<Drawing*> drawings;
bool isDrawing;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID				OnPaint(HDC hdc);
VOID				SendMouseMessage(HWND hwnd);
VOID				BeginPaint(Drawing *dw);
VOID				EndPaint();
POINT				GetCursorPosition(HWND hwnd);

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
	LoadString(hInstance, IDC_LAB3WP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3WP));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3WP));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB3WP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void OpenDialog(HWND hwnd);

void setDrawing(Drawing *dr)
{
	pendingDrawing = dr;
	pendingDrawing->setColor(colors[currentColor]);
}

void undo(HWND hwnd)
{
	if (!drawings.empty())
	{
		drawings.pop_back();
		InvalidateRect(hwnd, 0, TRUE);
	}
}

void changeColor(HWND hwnd)
{
	currentColor++;
	if (currentColor >= NUMBER_OF_COLORS)
		currentColor = 0;
	if (drawing != NULL)
		drawing->setColor(colors[currentColor]);
	InvalidateRect(hwnd, 0, TRUE);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	HDC hdcBuf;
	HBITMAP hbmBuf;
	HBITMAP hOldBmp;
	int width;
	int height;

	switch (message)
	{
	case WM_CREATE:
		RegisterHotKey(hWnd, IDHK_CHANGE_COLOR, MOD_CONTROL, VK_SPACE);
		RegisterHotKey(hWnd, IDHK_DRAW_CIRCLE, MOD_CONTROL, 0x43);
		RegisterHotKey(hWnd, IDHK_DRAW_RECTANGLE, MOD_CONTROL, 0x52);
		RegisterHotKey(hWnd, IDHK_DRAW_LINE, MOD_CONTROL, 0x4C);
		RegisterHotKey(hWnd, IDHK_DRAW_HAND, MOD_CONTROL, 0x48);
		RegisterHotKey(hWnd, IDHK_DRAW_BEZIER, MOD_CONTROL, 0x42);
		RegisterHotKey(hWnd, IDHK_DRAW_POLYGON, MOD_CONTROL, 0x50);
		RegisterHotKey(hWnd, IDHK_DRAW_WIDTH_INCREASE, MOD_CONTROL, 0x51);
		RegisterHotKey(hWnd, IDHK_DRAW_WIDTH_DECREASE, MOD_CONTROL, 0x41);
		RegisterHotKey(hWnd, IDHK_DRAW_ERASER, MOD_CONTROL, 0x44);

		RegisterHotKey(hWnd, IDHK_DRAW_UNDO, MOD_CONTROL, 0x5A);

		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_BITMAP:
			OpenDialog(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_DRAW_LINE:
			drawing = new Line();
			setDrawing(new Line());
			break;
		case ID_DRAW_ELLIPSE:
			setDrawing(new EllipseDrawing());
			break;
		case ID_DRAW_RECTANGLE:
			setDrawing(new RectangleDrawing());
			break;
		case ID_DRAW_FREEHAND:
			setDrawing(new FreeHand());
			break;
		case ID_DRAW_BELZIER:
			setDrawing(new BezierDrawing());
			break;
		case ID_DRAW_POLYGON:
			setDrawing(new PolygonDrawing());
			break;
		case ID_DRAW_ERASER:
			setDrawing(new Eraser());
			break;
		case ID_ACTION_UNDO:
			undo(hWnd);
			break;
		case ID_ACTION_CHANGECOLOR:
			changeColor(hWnd);
			break;
		case ID_ACTION_INCREASESTROKEWIDTH:
			if (drawing != NULL)
				drawing->increaseWidth();
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case ID_ACTION_DECREASESTROKEWIDTH:
			if (drawing != NULL)
				drawing->decreaseWidth();

			InvalidateRect(hWnd, 0, TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYUP:

		if (isDrawing && drawing != NULL)
		{
			switch (wParam) {
			case VK_ESCAPE:
				drawing->onInterrupt();
				if (drawing->isFinished()){
					EndPaint();
				}
				InvalidateRect(hWnd, 0, TRUE);
				break;

			}
		}
		break;
	case WM_MOUSEMOVE:
		InvalidateRect(hWnd, 0, TRUE);
		if (isDrawing)
		{
			drawing->onMove(GetCursorPosition(hWnd));
		}
		break;
	case WM_HOTKEY:
		switch (wParam)
		{
		case IDHK_CHANGE_COLOR:
			changeColor(hWnd);
			break;
		case IDHK_DRAW_RECTANGLE:
			setDrawing(new RectangleDrawing());
			break;
		case IDHK_DRAW_CIRCLE:
			setDrawing(new EllipseDrawing());
			break;
		case IDHK_DRAW_LINE:
			setDrawing(new Line());
			break;
		case IDHK_DRAW_HAND:
			setDrawing(new FreeHand());
			break;
		case IDHK_DRAW_BEZIER:
			setDrawing(new BezierDrawing());
			break;
		case IDHK_DRAW_POLYGON:
			setDrawing(new PolygonDrawing());
			break;
		case IDHK_DRAW_ERASER:
			setDrawing(new Eraser());
			break;
		case IDHK_DRAW_UNDO:
			undo(hWnd);
			break;
		case IDHK_DRAW_WIDTH_INCREASE:
			if (drawing != NULL)
				drawing->increaseWidth();
			InvalidateRect(hWnd, 0, TRUE);
			break;
		case IDHK_DRAW_WIDTH_DECREASE:
			if (drawing != NULL)
				drawing->decreaseWidth();

			InvalidateRect(hWnd, 0, TRUE);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		if (isDrawing)
		{
			SendMouseMessage(hWnd);

			if (drawing->isFinished()){
				EndPaint();
			}
			InvalidateRect(hWnd, 0, TRUE);
		}
		else
		{
			if (pendingDrawing != NULL){
				BeginPaint(pendingDrawing);
				pendingDrawing = NULL;
				SendMouseMessage(hWnd);
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		GetClientRect(hWnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;


		hdcBuf = CreateCompatibleDC(hdc);


		hbmBuf = CreateCompatibleBitmap(hdc, width, height);
		hOldBmp = (HBITMAP)SelectObject(hdcBuf, hbmBuf);
		Rectangle(hdcBuf, 0, 0, width, height);

		OnPaint(hdcBuf);

		BitBlt(hdc, 0, 0, width, height, hdcBuf, 0, 0, SRCCOPY);
		SelectObject(hdcBuf, hOldBmp);

		DeleteDC(hdcBuf);
		DeleteObject(hbmBuf);


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return 1;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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

VOID OnPaint(HDC hdc)
{
	//first object
	TRIVERTEX        vert[2];
	GRADIENT_RECT    gRect;
	vert[0].x = 0;
	vert[0].y = 0;
	vert[0].Red = 0x0000;
	vert[0].Green = 0x0000;
	vert[0].Blue = 0x0000;
	vert[0].Alpha = 0x0000;

	vert[1].x = 100;
	vert[1].y = 32;
	vert[1].Red = 0xFF00;
	vert[1].Green = 0x0000;
	vert[1].Blue = 0xff00;
	vert[1].Alpha = 0x0000;

	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;
	GradientFill(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);

	//second
	vert[0].x = 0;
	vert[0].y = 32;
	vert[0].Red = 0x0000;
	vert[0].Green = 0x8000;
	vert[0].Blue = 0xFF00;
	vert[0].Alpha = 0x0000;

	vert[1].x = 100;
	vert[1].y = 64;
	vert[1].Red = 0x0000;
	vert[1].Green = 0xd000;
	vert[1].Blue = 0xd000;
	vert[1].Alpha = 0x0000;

	// Create a GRADIENT_RECT structure that 
	// references the TRIVERTEX vertices. 
	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;

	// Draw a shaded rectangle. 
	GradientFill(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);

	for (std::vector<Drawing*>::iterator it = drawings.begin(); it != drawings.end(); ++it) {
		Drawing *drawing = *it;

		drawing->onDraw(hdc);
	}
	if (drawing != NULL)
		drawing->onDraw(hdc);


}

void OpenDialog(HWND hwnd)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));
	//mbstowcs_s(wtext, szFileName, strlen(szFileName) + 1);//Plus null

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = L"BMP Files (*.bmp)\0*.bmp\0";
	//ofn.lpstrFile = wtext;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"bmp";
	if (GetOpenFileName(&ofn))
	{
		// Do something usefull with the filename stored in szFileName 
	}
}


VOID SendMouseMessage(HWND hwnd)
{
	if (drawing == NULL || isDrawing == false)
		return;

	drawing->onClick(GetCursorPosition(hwnd));
}

POINT GetCursorPosition(HWND hwnd)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);

	return p;
}

void BeginPaint(Drawing* dw)
{
	isDrawing = true;
	drawing = dw;
}

void EndPaint()
{
	isDrawing = false;
	drawings.push_back(drawing);
	drawing = NULL;
}
