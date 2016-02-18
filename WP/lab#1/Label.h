//
// Created by Maxian Nicu on 2/17/2016.
//

#ifndef WP1_LABEL_H
#define WP1_LABEL_H


#include <windows.h>
#include <string>

class Label {
private:
    std::string text;
    int x;
    int y;
public:
    Label(std::string text);
    void setText(std::string text);
    void draw(HDC hdc,int x,int y);
};


#endif //WP1_LABEL_H
