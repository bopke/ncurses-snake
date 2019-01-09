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
    bool pause = true;
    bool help = true;
    int course = KEY_RIGHT;
    int level;
    vector <CPoint> parts;

    void draw() {
        gotoyx(parts[0].y + geom.topleft.y, parts[0].x + geom.topleft.x);
        printc('*');
        for (unsigned int i = 1; i < parts.size(); i++) {
            gotoyx(parts[i].y + geom.topleft.y, parts[i].x + geom.topleft.x);
            printc('+');
        }
    }

    void drawPause() {
        int x = geom.topleft.x, y = geom.topleft.y;
        gotoyx(y + 2, x + 3);
        printl("h - toggle help information");
        gotoyx(y + 3, x + 3);
        printl("p - toggle play/pause mode");
        gotoyx(y + 4, x + 3);
        printl("r - restart game");
        gotoyx(y + 5, x + 3);
        printl("q - quit");
        gotoyx(y + 6, x + 3);
        printl("arrows - move snake (in play mode) or");
        gotoyx(y + 7, x + 12);
        printl("move window (in pause mode)");

    }

    void drawHelp() {
        int x = geom.topleft.x, y = geom.topleft.y;
        gotoyx(y + 2, x + 2);
        printl("Use arrows to move snake");
        gotoyx(y + 4, x + 2);
        printl("Eat as much food as you can.");
        gotoyx(y + 5, x + 2);
        printl("Also, dont die.");
        gotoyx(y + 7, x + 2);
        printl("press 'p' or 'r' to play or 'h' for help");

    }

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
        if (tolower(key) == 'p') {
            pause = !pause;
            if (!pause) {
                help = false;
            }
            return true;
        }
        if (tolower(key) == 'h' && pause) {
            help = !help;
            return true;
        }
        if (pause && tolower(key) == 'q') {
            exit(0);
        }
        if (!pause && ((key == KEY_UP && course != KEY_DOWN) || (key == KEY_DOWN && course != KEY_UP) ||
                       (key == KEY_LEFT && course != KEY_RIGHT) || (key == KEY_RIGHT && course != KEY_LEFT))) {
            course = key;
            return true;
        }
        if (CFramedWindow::handleEvent(key)) return true;
        return false;
    }

    void paint() {
        CFramedWindow::paint();
        gotoyx(geom.topleft.y - 1, geom.topleft.x);
        printl("| LEVEL: %d |", level);
        draw();
        if (pause) {
            if (help) drawHelp();
            else drawPause();
        }
    }
};

#endif
