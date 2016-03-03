//
// Created by Maxian Nicu on 2/5/2016.
//

#ifndef WP1_WIDGET_H
#define WP1_WIDGET_H


#include <windows.h>

class Widget {
protected:
    HWND instance;
    HWND root;
    RECT getLocalCoordinates();
    int id;
public:
    Widget(HWND root,LPCSTR lpClassName,LPCTSTR lpWindowName);
    Widget(HWND root,LPCSTR lpClassName,LPCSTR lpWindowName,int style);
    RECT getRect();
    int getWidth();
    int getHeight();
    int getXPosition();
    int getYPosition();
    void setDrawingStyle(long style);
    void setPosition(int x,int y);
    void setSize(int width,int height);
    int getId();
};


#endif //WP1_WIDGET_H
