//
// Created by Maxian Nicu on 2/17/2016.
//

#include "TextEdit.h"

TextEdit::TextEdit(HWND root) : TextWidget(root,"EDIT","EDIT"){

}

std::string TextEdit::getText() {
    TCHAR buff[1024];
    int size = GetWindowText(instance,buff,1024);
    return std::string(buff);
}
