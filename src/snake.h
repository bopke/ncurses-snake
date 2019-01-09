#ifndef __SNAKE_H__
#define __SNAKE_H__

typedef int i1;

#include <vector>
#include <cstdlib>
#include <ctime>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake : public CFramedWindow {
private:
    bool pause = true;
    bool help = true;
    bool died = false;
    int course = KEY_RIGHT;
    int level = 0;
    CPoint food;
    vector <CPoint> parts;

    void reset() {
        pause = false;
        help = false;
        course = KEY_RIGHT;
        level = 0;
        srand(time(NULL));
        int headPosX = RAND_MAX % (geom.size.x - 5) + 1;
        int headPosY = RAND_MAX % (geom.size.y - 3) + 1;
        parts.push_back(CPoint(headPosX, headPosY));
        parts.push_back(CPoint(headPosX - 1, headPosY));
        parts.push_back(CPoint(headPosX - 2, headPosY));
        generateFood();
        paint();
    }

    void generateFood() {
        srand(time(NULL));
        CPoint candidate;
        do {
            candidate = CPoint(rand() % (geom.size.y - 2) + 1, rand() % (geom.size.x - 2) + 1);
            bool s = true;
            for (auto &part:parts) {
                if (part.x == candidate.x && candidate.y == part.x) {
                    s = false;
                    break;
                }
            }
            if (s) break;
        } while (true);
        food = candidate;
    }

    bool ate() {
        bool t = false;
        for (auto &part : parts) {
            if (part.x == food.x && part.y == food.y) {
                level++;
                t = true;
                break;
            }
        }
        if (t) {
            generateFood();
            return true;
        }
        return false;
    }

    void draw() {
        gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
        printc('O');
        gotoyx(parts[0].y + geom.topleft.y, parts[0].x + geom.topleft.x);
        printc('*');
        for (unsigned int i = 1; i < parts.size(); i++) {
            gotoyx(parts[i].y + geom.topleft.y, parts[i].x + geom.topleft.x);
            printc('+');
        }
    }

    void drawDead() {
        int x = geom.topleft.x, y = geom.topleft.y;
        gotoyx(y + 1, x + 1);
        printl("GAME OVER, result: %d", level);
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
        reset();
        pause = true;
        draw();
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
        if (tolower(key) == 'r') {
            reset();
            return true;
        }
        if (!pause && (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)) {
            if ((key == KEY_UP && course != KEY_DOWN) || (key == KEY_DOWN && course != KEY_UP) ||
                (key == KEY_LEFT && course != KEY_RIGHT) || (key == KEY_RIGHT && course != KEY_LEFT)) {
                course = key;
            }
            return true;
        }

        return
                CFramedWindow::handleEvent(key);
    }

    void paint() {
        CFramedWindow::paint();
        draw();
        if (!died) {
            gotoyx(geom.topleft.y - 1, geom.topleft.x);
            printl("| LEVEL: %d |", level);
        } else {
            drawDead();
        }
        if (pause) {
            if (help) drawHelp();
            else drawPause();
        }
    }
};

#endif
