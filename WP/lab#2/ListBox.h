//
// Created by Maxian Nicu on 2/29/2016.
//

#ifndef WP2_LISTBOX_H
#define WP2_LISTBOX_H


#include <string>
#include "Widget.h"

class ListBox : public Widget {

public:
    ListBox(HWND root);
    void addItem(std::string item);
    std::string getSelectedItem();
    int getSelectedItemIndex();
};


#endif //WP2_LISTBOX_H
