#include <ncurses/curses.h>

const int lebar = 75;
const int tinggi = 25;

char map[tinggi][lebar+1];
int px, py; // posisi pemain

// Inisialisasi atau cetak map
void init_map() {
    for(int i = 0; i < tinggi; i++) {
        for(int j = 0; j < lebar; j++) {
            if(i == 0 || i == tinggi - 1 || j == 0 || j == lebar - 1)
                map[i][j] = '#';
            else
                map[i][j] = ' ';
        }
        map[i][lebar] = '\0';
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_map();

    px = 2; py = 2;
    map[py][px] = 'P';

    // cetak map ke layar
    for(int cetak = 0; cetak < tinggi; cetak++) {
        mvprintw(cetak, 0, "%s", map[cetak]);
    }

    mvprintw(tinggi, 0, "\n WASD atau panah untuk bergerak dan q untuk keluar");
    refresh();

    // switch case untuk menggerakkan pemain
    bool gerak = true;
    while(gerak) {
        int gerak2 = getch();
        int gx = px, gy = py;
        switch(gerak2) {
            case 'q':
            gerak = false;
            break;

            case KEY_UP:
            case 'w':
            gy = py - 1;
            break;

            case KEY_DOWN:
            case 's':
            gy = py + 1;
            break;

            case KEY_LEFT:
            case 'a':
            gx = px - 1;
            break;

            case KEY_RIGHT:
            case 'd':
            gx = px + 1;
            break;

            default:
            break;
        }
        // Agar bisa berubah posisi
        if(gx != px || gy != py) {
            if(gy >= 0 && gy < tinggi && gx >= 0 && gx < lebar) {
                if(map[gy][gx] != '#') {
                    map[py][px] = ' ';
                    px = gx; py = gy;
                    map[py][px] = 'P';
                }
            }
        }

        // Cetak ulang posisi pemain
        for(int cetak = 0; cetak < tinggi; cetak++) {
            mvprintw(cetak, 0, map[cetak]);
        }
    }

    endwin();
    return 0;
}