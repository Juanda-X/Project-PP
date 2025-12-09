#include <ncurses/curses.h>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void batas(int lebar, int tinggi) {
    for(int i = 0; i < lebar; i++) {
        mvprintw(0, i, "#");
        mvprintw(tinggi - 1, i, "#");  // Perbaikan: gunakan tinggi-1 untuk border bawah
    }

    for(int i = 0; i < tinggi; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, lebar - 1, "#");
    }
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); 
    srand(time(NULL));

    int lebar = 40;
    int tinggi = 20;
    bool selesai = false;

    while(!selesai) {
        clear();
        batas(lebar, tinggi);
        refresh();
        napms(100);
    }


    endwin();
    return 0;
}