//
// Created by Maxian Nicu on 2/17/2016.
//

#include <iostream>
#include "Label.h"

Label::Label(std::string text) {
    this->text = text;
}

void Label::setText(std::string text) {
    this->text = text;
}

void Label::draw(HDC hdc,int x,int y) {
    TextOut(hdc,x,y,text.c_str(),text.length());
}
