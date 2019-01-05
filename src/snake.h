#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include <cstdlib>

#include "winsys.h"
#include "cpoint.h"

class CSnake : public CFramedWindow {
private:
    vector <CPoint> parts;
public:
    CSnake(CRect r, char _c = ' ') :
            CFramedWindow(r, _c) {
        srand(time(NULL));
        int headPosX = rand() / RAND_MAX * 18;
        int headPosY = rand() / RAND_MAX * 41 + 2;
        parts.push_back(CPoint(headPosX,headPosY));
        parts.push_back(CPoint(headPosX,headPosY-1));
        parts.push_back(CPoint(headPosX,headPosY-2));
    }

};

#endif
