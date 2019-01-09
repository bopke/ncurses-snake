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
    int course = KEY_RIGHT;
    int level;
    vector <CPoint> parts;
public:
    CSnake(CRect r, char _c = ' ') :
            CFramedWindow(r, _c) {
        srand(time(NULL));
        int headPosX = rand() / RAND_MAX * 13 + 4;
        int headPosY = rand() / RAND_MAX * 40 + 2;
        parts.push_back(CPoint(headPosX, headPosY));
        parts.push_back(CPoint(headPosX - 1, headPosY));
        parts.push_back(CPoint(headPosX - 2, headPosY));
    }

    bool handleEvent(int key) {
        if ((key == KEY_UP && course != KEY_DOWN) || (key == KEY_DOWN && course != KEY_UP) ||
            (key == KEY_LEFT && course != KEY_RIGHT) || (key == KEY_RIGHT && course != KEY_LEFT)) {
            course = key;
            return true;
        }
        if (CFramedWindow::handleEvent(key)) return true;
        return false;
    }

    void draw() {
        gotoyx(parts[0].y + geom.topleft.y, parts[0].x + geom.topleft.x);
        printc('*');
        for (unsigned int i = 1; i < parts.size(); i++) {
            gotoyx(parts[i].y + geom.topleft.y, parts[i].x + geom.topleft.x);
            printc('+');
        }
    }

    void paint() {
        CFramedWindow::paint();
        gotoyx(geom.topleft.y - 1, geom.topleft.x);
        printl("| LEVEL: %d |", level);
        draw();
    }
};

#endif
