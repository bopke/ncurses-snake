#ifndef __SNAKE_H__
#define __SNAKE_H__

typedef int i1;

#include <vector>
#include <cstdlib>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake : public CFramedWindow {
private:
    vector <CPoint> parts;
public:
    CSnake(CRect r, char _c = ' ') :
            CFramedWindow(r, _c) {
        srand(time(NULL));
        int headPosX = rand() / RAND_MAX * 18;
        int headPosY = rand() / RAND_MAX * 41 + 2;
        parts.push_back(CPoint(headPosX, headPosY));
        parts.push_back(CPoint(headPosX, headPosY - 1));
        parts.push_back(CPoint(headPosX, headPosY - 2));
    }

    void draw() {
        gotoyx(parts[0].y + geom.topleft.y, parts[0].x + geom.topleft.x);
        printc('*');
        for (unsigned int i = 1; i < parts.size(); i++) {
            gotoyx(parts[i].y + geom.topleft.y, parts[i].x + geom.topleft.x);
            printc('+');
        }
        CFramedWindow::paint();
    }
};

#endif
