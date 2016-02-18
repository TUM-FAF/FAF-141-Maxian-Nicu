#include <windows.h>
#include <iostream>
#include <windowsx.h>
#include "Widget.h"
#include "Button.h"
#include "TextEdit.h"
#include "Label.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[] = "WindowsApp";

TextEdit *textA,*textB;
Button *buttonA,*buttonB,*superButton;
Label *labelA,*labelB,*labelHello;
RECT container;


//fonts
HFONT primaryFont = CreateFont(18,0,0,0,FW_DONTCARE,TRUE, TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                         CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, VARIABLE_PITCH,TEXT("Arial"));

HFONT secondaryFont = CreateFont(18,0,0,0,FW_DONTCARE,FALSE, FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));

//color
long primaryColor = RGB(0,0,0);
long secondaryColor = RGB(5,0,161);
long whiteColor = RGB(255,255,255);

void createButtons(HWND hwnd){
    buttonA = new Button(hwnd);
    buttonA->setText("Button A");
    buttonA->setSize(150,20);
    buttonA->setPosition(100,0);

    buttonB = new Button(hwnd);
    buttonB->setText("Button B");
    buttonB->setSize(100,20);
    buttonB->setPosition(100,20);

    superButton = new Button(hwnd);
    superButton->setText("Focus !");
    superButton->setSize(400,20);
}

void createText(HWND hwnd){
    labelA = new Label("Label A");
    labelB = new Label("Label B");
    labelHello = new Label("Done with Pride and Prejudice by Nicu Maxian");
}

void createTextInput(HWND hwnd){
    textA = new TextEdit(hwnd);
    textA->setText("Enter text here");
    textA->setSize(100,20);
    textA->setPosition(0,0);

    textB = new TextEdit(hwnd);
    textB->setText("Enter text here");
    textB->setSize(125,20);
    textB->setPosition(0,20);
}

void draw(HWND hwnd){
    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    textA->setPosition(container.left,container.top);
    textB->setPosition(container.left,container.top+20);
    buttonA->setPosition(container.left+100,container.top);
    buttonB->setPosition(container.left+125,container.top+20);
    superButton->setPosition(container.left,container.top+40);


    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hwnd, &ps);
    SetBkMode(hDC,TRANSPARENT);


    labelA->draw(hDC, container.left+280,container.top+0);

    SelectObject(hDC,primaryFont);
    SetTextColor(hDC,(COLORREF)secondaryColor);
    labelHello->draw(hDC, container.left,container.top+60);


    //setting font for labelB
    SelectObject(hDC,secondaryFont);
    SetTextColor(hDC,(COLORREF)secondaryColor);

    labelB->draw(hDC, container.left+250,container.top+20);
    EndPaint(hwnd, &ps);
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            "WP Lab#1",  /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            CW_USEDEFAULT,                 /* The programs width */
            CW_USEDEFAULT,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT window;

    GetWindowRect(hwnd,&window);
    container.left = (window.right - window.left)/2 - 200;
    container.right = (window.right - window.left)/2 + 200;
    container.top = (window.bottom-window.top)/2 - 60;
    container.bottom = (window.bottom-window.top)/2 + 60;

    switch (message) {
        /*case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_MINIMIZE){
                ExitProcess(0);
                return 0;
            }
            break;*/
        case WM_CREATE:
            createButtons(hwnd);
            createText(hwnd);
            createTextInput(hwnd);
            break;
        case WM_COMMAND:
            if (wParam == buttonA->getId()) {
                labelA->setText(textA->getText());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            }
            if (wParam == buttonB->getId()) {
                labelB->setText(textB->getText());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            }
            if (wParam == superButton->getId()){
                RECT rect;
                GetWindowRect(hwnd, &rect);
                int x = rect.left;
                int y = rect.top;
                if (rect.left == 0){
                    x = 100-rand()%200;
                    y = 100-rand()%200;
                    switch(rand()%3) {
                        case 0 :
                            superButton->setText("Are you tired ? :D");
                            break;
                        case 1 :
                            superButton->setText("Maybe you want to try another trick ?");
                            break;
                        case 2 :
                            superButton->setText("Not funny ?! Click again ! :D");
                            x = 30;
                            y = 40;
                            break;
                    }
                }
                rect.left = 0;
                rect.right -= x;
                rect.bottom -= y;
                rect.top = 0;
                SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                             SWP_FRAMECHANGED);
                break;
            }
            break;
        case WM_PAINT:
            draw(hwnd);
            break;
        case WM_SIZE:
            draw(hwnd);
            if (wParam == SIZE_MINIMIZED){
                ExitProcess(0);
            }
            if (wParam == SIZE_MAXIMIZED){
                MessageBox(hwnd,"This features is not available in demo.","Sorry",MB_OK|MB_ICONASTERISK);
                return 0;
            }
            break;
        case WM_MOVE:{
            int x = rand()%20 + 230;
            HBRUSH brush = CreateSolidBrush(RGB(x,x,x));
            SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;}
        case WM_CLOSE:
            MessageBox(hwnd,"NOOOOO ! YOU CANNOT EXIT !!!!","UTM",MB_OK|MB_ICONSTOP);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_GETMINMAXINFO:{
            MINMAXINFO *mmi = (MINMAXINFO *) lParam;
            mmi->ptMinTrackSize.x = 420;
            mmi->ptMinTrackSize.y = 140;
            return 0;
        }
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC) wParam;
            if ((GetDlgItem(hwnd, textB->getId()) == (HWND) lParam)) {
                SetTextColor(hdc, (COLORREF)whiteColor);

                SetBkColor(hdc,(COLORREF)primaryColor);
                return (LRESULT)CreateSolidBrush((COLORREF)primaryColor);
            }
        }
        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC) wParam;
            if ((GetDlgItem(hwnd, textB->getId()) == (HWND) lParam)) {
                SetTextColor(hdc, (COLORREF)whiteColor);

                SetBkColor(hdc,(COLORREF)primaryColor);
                return (LRESULT)CreateSolidBrush((COLORREF)primaryColor);
            }
        } default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

