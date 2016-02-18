//
// Created by Maxian Nicu on 2/17/2016.
//

#ifndef WP1_TEXTEDIT_H
#define WP1_TEXTEDIT_H

#include "TextWidget.h"
#include <string>

class TextEdit : public TextWidget {
private:
public:
    TextEdit(HWND root);
    std::string getText();
};


#endif //WP1_TEXTEDIT_H
