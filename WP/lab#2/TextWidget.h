//
// Created by Maxian Nicu on 2/17/2016.
//

#ifndef WP1_TEXTWIDGET_H
#define WP1_TEXTWIDGET_H


#include "Widget.h"

class TextWidget : public Widget {
private:
public:
    TextWidget(HWND root,LPCSTR lpClassName,LPCTSTR lpWindowName);
    void setText(LPCTSTR text);
};


#endif //WP1_TEXTWIDGET_H
