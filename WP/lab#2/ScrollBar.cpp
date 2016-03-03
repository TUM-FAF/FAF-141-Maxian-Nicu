//
// Created by Maxian Nicu on 3/1/2016.
//

#include "ScrollBar.h"

ScrollBar::ScrollBar(HWND root) : Widget(root,"ScrollBar","Scroll Bar",SBS_HORZ|SBS_TOPALIGN|SBS_LEFTALIGN){

}

void ScrollBar::setRange(int min, int max) {
    this->min = min;
    this->max = max;
    SetScrollRange(instance,SB_CTL|SB_HORZ,min,max, true);
}

int ScrollBar::getValue() {
    return GetScrollPos(instance,SB_CTL|SB_HORZ);
}


void ScrollBar::setValue(int value) {
    SetScrollPos(instance, SB_CTL, value, TRUE);
}

void ScrollBar::handleMessage(UINT message, WPARAM wParam, LPARAM lParam) {
    if(GetWindowLong((HWND)lParam,GWL_ID) == this->getId()){
        int CurPos = 0;
        CurPos = GetScrollPos(instance, SB_CTL);

        switch (LOWORD(wParam))
        {
            case SB_TOP:
                CurPos = 0;
                break;

            case SB_LINEUP:
                if (CurPos > 0)
                    CurPos--;
                break;

            case SB_THUMBPOSITION:
                CurPos = HIWORD(wParam);
                break;

            case SB_THUMBTRACK:
                CurPos = HIWORD(wParam);
                break;

            case SB_LINERIGHT:
                if (CurPos < max)
                    CurPos++;
                break;

            case SB_RIGHT:
                CurPos = max;
                break;

            case SB_ENDSCROLL:
                break;
        }
        setValue(CurPos);

    }
}
