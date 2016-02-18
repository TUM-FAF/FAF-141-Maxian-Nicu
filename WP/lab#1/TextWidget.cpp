//
// Created by Maxian Nicu on 2/17/2016.
//

#include "TextWidget.h"


TextWidget::TextWidget(HWND root, LPCSTR lpClassName, LPCTSTR lpWindowName) : Widget(root,lpClassName,lpWindowName){

}

void TextWidget::setText(LPCTSTR text) {
    SetWindowText(instance,text);
}
