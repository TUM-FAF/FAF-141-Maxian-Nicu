//
// Created by Maxian Nicu on 3/1/2016.
//

#ifndef WP2_SCROLLBAR_H
#define WP2_SCROLLBAR_H


#include "Widget.h"

class ScrollBar : public Widget {
private:
    int min;
    int max;
public:
    ScrollBar(HWND root);
    void setRange(int min,int max);
    int getValue();
    void setValue(int value);
    void handleMessage(UINT message, WPARAM wParam, LPARAM lParam);
};


#endif //WP2_SCROLLBAR_H
