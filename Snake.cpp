#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

#define MINX 2
#define MINY 2
#define MAXX 50
#define MAXY 22

void gotoxy(int column, int line);
void VeKhung();

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[200];
    int DoDai;
    int Score;

    CONRAN() {
        DoDai = 3;
        Score = 0;
        A[0] = {10, 10};
        A[1] = {11, 10};
        A[2] = {12, 10};
    }

    void Ve(Point Qua) {
        // Vẽ rắn
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            printw("X");
        }
        // Vẽ quả
        gotoxy(Qua.x, Qua.y);
        printw("*");
    }

    bool DiChuyen(int Huong, Point& Qua) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;

        // ❌ Nếu chạm tường → GAME OVER
        if (A[0].x <= MINX || A[0].x >= MAXX ||
            A[0].y <= MINY || A[0].y >= MAXY) {
            return false;
        }

        // ✔ Nếu ăn quả
        if (A[0].x == Qua.x && A[0].y == Qua.y) {
            DoDai++;
            Score++;

            Qua.x = rand() % (MAXX - MINX - 2) + MINX + 1;
            Qua.y = rand() % (MAXY - MINY - 2) + MINY + 1;
        }

        return true;
    }
};

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    CONRAN r;
    int Huong = 0;
    Point Qua;

    srand(time(0));
    Qua.x = rand() % (MAXX - MINX - 2) + MINX + 1;
    Qua.y = rand() % (MAXY - MINY - 2) + MINY + 1;

    while (true) {
        int t = getch();
        if (t != ERR) {
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's' || t == 'x') Huong = 1;
        }

        clear();
        VeKhung();

        // Hiển thị điểm
        gotoxy(2, 0);
        printw("Score: %d", r.Score);

        // Di chuyển + kiểm tra thua
        if (!r.DiChuyen(Huong, Qua)) {
            gotoxy(20, MAXY + 2);
            printw("GAME OVER! Your score: %d", r.Score);
            refresh();
            usleep(2000000);
            break;
        }

        r.Ve(Qua);

        refresh();
        usleep(150000);
    }

    endwin();
    return 0;
}

void gotoxy(int column, int line) {
    move(line, column);
}

void VeKhung() {
    for (int x = MINX; x <= MAXX; x++) {
        gotoxy(x, MINY);
        printw("#");
        gotoxy(x, MAXY);
        printw("#");
    }

    for (int y = MINY; y <= MAXY; y++) {
        gotoxy(MINX, y);
        printw("#");
        gotoxy(MAXX, y);
        printw("#");
    }
}
