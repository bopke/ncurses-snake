#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"

class CSnake : public CFramedWindow {
public:
    CSnake::CSnake(CRect r, char _c = ' ') :
            CFramedWindow(r, _c) {
    }

};

#endif
