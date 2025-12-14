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
    int pemain = lebar / 2;
    bool selesai = false;

    while(!selesai) {
        clear();
        batas(lebar, tinggi);

        // Menggerakkan pemain ke kiri dan kanan
        int gerak = getch();
        switch(gerak) {
            case KEY_LEFT:
            case 'a':
                if(pemain > 1) pemain--;
                break;

            case KEY_RIGHT:
            case 'd':
                if(pemain < lebar - 2) pemain++;
                break;

            case 'q':
                selesai = true;
                break;
        }

        // cetak pemain
        mvprintw(tinggi - 2, pemain, "A");
        mvprintw(tinggi + 3, 0, "Tekan q Untuk Menyerah");

        refresh();
        napms(100);
    }


    endwin();
    return 0;
}