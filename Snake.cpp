#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>   // usleep
using namespace std;
#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            printw("X");
        }
    }
    
    void Ve(Point Qua){
    for (int i = 0; i < DoDai; i++){
        gotoxy(A[i].x, A[i].y);
        cout<<"X";

    }
    gotoxy(Qua.x, Qua.y); cout<<"*";
}

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;
    }
    
    void DiChuyen(int Huong, Point& Qua){
    for (int i = DoDai-1; i>0; i--)
        A[i] = A[i-1];

    if (Huong==0) A[0].x = A[0].x + 1;
    if (Huong==1) A[0].y = A[0].y + 1;
    if (Huong==2) A[0].x = A[0].x - 1;
    if (Huong==3) A[0].y = A[0].y - 1;

    if ((A[0].x == Qua.x) && (A[0].y == Qua.y)){
        DoDai++;
        Qua.x = rand()%(MAXX-MINX)+MINX;
        Qua.y = rand()%(MAXY-MINY)+MINY;
    }
}
};

int main() {
    initscr();          // bật ncurses
    noecho();           // không hiện ký tự nhập
    curs_set(0);        // ẩn con trỏ
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() không chờ

    CONRAN r;
    int Huong = 0;

    while (1) {
        int t = getch();     // lấy phím không chặn

        if (t != ERR) {
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's' || t == 'x') Huong = 1;
        }

        clear();             // thay cho system("cls")
        r.Ve();
        r.DiChuyen(Huong);

        refresh();
        usleep(300000);      // Sleep(300)
    }

    endwin(); // tắt ncurses
    return 0;
}

// GOTOXY kiểu Linux
void gotoxy(int column, int line) {
    move(line, column);   // (y, x)
}
