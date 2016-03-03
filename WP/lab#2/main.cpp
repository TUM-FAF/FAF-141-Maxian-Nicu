#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "Label.h"
#include "ListBox.h"
#include "ScrollBar.h"

#define ID_EXIT 9001
#define ID_ABOUT 9002
#define ID_HELP 9003
#define ID_BKG_CHANGE 9004

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WinAPP";

Label *first,*second,*third,*selectedItem;
ListBox *listBox;

Label *R,*G,*B;
ScrollBar *scrollBarR,*scrollBarG,*scrollBarB;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_ASTERISK);
    wincl.hIconSm = LoadIcon (NULL,IDI_ERROR);

    //try to load icon
    HANDLE  hIcon = LoadImage(0,"icon.ico",IMAGE_ICON,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
    if (hIcon){
        std::cout << "Icon loaded" << std::endl;
        wincl.hIcon = (HICON)hIcon;
        wincl.hIconSm = (HICON)hIcon;
    }
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            "WP Lab#2",  /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)){
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);

    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void showHelp(){
    MessageBox(NULL, "Developed by Nicu Maxian", "About", MB_ICONINFORMATION);

}

std::string concat(std::string a,int b){
    char numstr[21];
    sprintf(numstr,"%d",b);
    return a+numstr;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message){
        /* handle the messages */
        case WM_CREATE:{
            HMENU hmenu = CreateMenu();
            AppendMenu(hmenu,MF_STRING,ID_ABOUT,"&About");
            AppendMenu(hmenu,MF_STRING,ID_HELP,"&Help");
            AppendMenu(hmenu,MF_STRING,ID_EXIT,"E&xit");
            SetMenu(hwnd,hmenu);

            //register shourtcut
            RegisterHotKey(hwnd,ID_BKG_CHANGE,MOD_CONTROL,VK_SPACE);

            first = new Label("First label...please scroll down :))");
            second = new Label("Second label...You can scroll down or up :D");
            third = new Label("Third label...Scroll up :)");
            selectedItem = new Label("Selected item");
            R = new Label("R");
            G = new Label("G");
            B = new Label("B");


            listBox = new ListBox(hwnd);
            listBox->setSize(200,200);
            listBox->setPosition(100,80);
            listBox->addItem("Chisinau");
            listBox->addItem("Floresti");
            listBox->addItem("Balti");
            listBox->addItem("Comrat");
            listBox->addItem("Edinet");
            listBox->addItem("Soroca");
            listBox->addItem("Cimislia");
            scrollBarR = new ScrollBar(hwnd);
            scrollBarG = new ScrollBar(hwnd);
            scrollBarB = new ScrollBar(hwnd);
            scrollBarR->setPosition(0, 0);
            scrollBarG->setPosition(0, 20);
            scrollBarB->setPosition(0, 40);
            scrollBarR->setSize(100, 20);
            scrollBarG->setSize(100, 20);
            scrollBarB->setSize(100, 20);
            scrollBarR->setRange(0,255);
            scrollBarG->setRange(0,255);
            scrollBarB->setRange(0,255);

            break;}
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd,&ps);

            RECT rect;
            GetWindowRect(hwnd, &rect);
            int x = rect.right - rect.left;
            first->draw(hdc, x, 100);
            second->draw(hdc, x, 400);
            third->draw(hdc, x, 800);
            selectedItem->draw(hdc,100,60);


            R->setText(concat("R : ",scrollBarR->getValue()));
            G->setText(concat("G : ",scrollBarG->getValue()));
            B->setText(concat("B : ",scrollBarB->getValue()));

            R->draw(hdc,0,0);
            G->draw(hdc,0,20);
            B->draw(hdc,0,40);
            EndPaint(hwnd,&ps);
            break;
        }

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_ABOUT:
                    showHelp();
                    break;
                case ID_HELP:
                    MessageBox(NULL, "This section is not available in DEMO version :D", "Help", MB_ICONERROR);
                    break;
                case ID_EXIT:
                    PostQuitMessage(0);
                    break;
            }
            if (LOWORD(wParam) == listBox->getId()){
                if (HIWORD(wParam) == LBN_SELCHANGE){
                    selectedItem->setText(listBox->getSelectedItem());
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                }
            }
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_F1:
                    showHelp();
                    break;
            }
            break;
        case WM_HOTKEY:
            if(wParam == ID_BKG_CHANGE){
                int r = rand()%256;
                int g = rand()%256;
                int b = rand()%256;
                HBRUSH brush = CreateSolidBrush(RGB(r,g,b));
                scrollBarR->setValue(r);
                scrollBarG->setValue(g);
                scrollBarB->setValue(b);
                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            }
            break;
        case WM_HSCROLL:{
            scrollBarR->handleMessage(message,wParam,lParam);
            scrollBarG->handleMessage(message,wParam,lParam);
            scrollBarB->handleMessage(message,wParam,lParam);

            HBRUSH brush = CreateSolidBrush(RGB(scrollBarR->getValue(),scrollBarG->getValue(),scrollBarB->getValue()));
            SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);

            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;}
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}