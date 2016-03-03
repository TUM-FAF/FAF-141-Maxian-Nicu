//
// Created by Maxian Nicu on 2/5/2016.
//

#include "Widget.h"

Widget::Widget(HWND root,LPCSTR lpClassName,LPCTSTR lpWindowName) : Widget(root,lpClassName,lpWindowName,0) {

}


Widget::Widget(HWND root, LPCSTR lpClassName, LPCSTR lpWindowName, int style) {
    static int index = 0;
    id = index++;
    instance = CreateWindowEx(
            (DWORD)NULL,
            lpClassName,
            lpWindowName,
            WS_VISIBLE | WS_CHILD | style,
            0,0,100,100,
            root,
            (HMENU)id,
            (HINSTANCE)GetWindowLong(root,GWL_HINSTANCE),
            NULL
    );
}

int Widget::getWidth() {
    RECT rect = getRect();
    return rect.right - rect.left;
}

int Widget::getHeight() {
    RECT rect = getRect();
    return rect.bottom - rect.top;
}

int Widget::getXPosition() {
    RECT rect = getLocalCoordinates();

    return rect.right;
}

int Widget::getYPosition() {
    RECT rect = getLocalCoordinates();

    return rect.top;
}

RECT Widget::getRect() {
    RECT rect;
    GetWindowRect(instance,&rect);
    return rect;
}

RECT Widget::getLocalCoordinates()
{
    RECT Rect;
    GetWindowRect(instance, &Rect);
    MapWindowPoints(HWND_DESKTOP, GetParent(instance), (LPPOINT) &Rect, 2);
    return Rect;
}

void Widget::setDrawingStyle(long style) {
    SetWindowLongPtr(instance,GWL_STYLE,style |WS_CHILD |WS_VISIBLE);
}

void Widget::setPosition(int x, int y) {
    SetWindowPos(instance,HWND_TOP,x,y,getWidth(),getHeight(),SWP_FRAMECHANGED);
}

void Widget::setSize(int width, int height) {
    SetWindowPos(instance,HWND_TOP,getXPosition(),getYPosition(),width,height,SWP_FRAMECHANGED);
}

int Widget::getId() {
    return id;
}
