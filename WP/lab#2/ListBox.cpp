//
// Created by Maxian Nicu on 2/29/2016.
//

#include <iostream>
#include "ListBox.h"

ListBox::ListBox(HWND root) : Widget(root,"ListBox","ListBox",LBS_NOTIFY|LBS_SORT) {
}

void ListBox::addItem(std::string item) {
    SendMessage(instance,LB_ADDSTRING,0,(LPARAM)item.c_str());
}

std::string ListBox::getSelectedItem() {
    wchar_t s[255];
    SendMessageW(instance, LB_GETTEXT,(WPARAM)getSelectedItemIndex(),(LPARAM)s);
    std::wstring wstr(s);
    std::string str(wstr.begin(),wstr.end());
    return str;
}

int ListBox::getSelectedItemIndex() {
    return SendMessage(instance,LB_GETCURSEL,0,0);
}
