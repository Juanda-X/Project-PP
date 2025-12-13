#include <ncurses/curses.h>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void batas(int lebar, int tinggi) {
    for(int i = 0; i < lebar; i++) {
        mvprintw(0, i, "#");
        mvprintw(tinggi, i, "#"); 
    }

    for(int i = 0; i < tinggi; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, lebar - 1, "#");
    }
}

struct batu {
    int x, y;
};

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

    vector<batu> batuan;

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

        mvprintw(tinggi - 2, pemain, "A");
        mvprintw(tinggi + 3, 0, "Tekan q Untuk Menyerah");

        // posisi batu secara acak
        if(rand() % 5 == 0) {
            batu b;
            b.x = rand() % lebar;
            b.y = 0;
            batuan.push_back(b);
        }

        // Menggerakkan batu dari atas ke bawah
        for(size_t i = 0; i < batuan.size(); i++) {
            batuan[i].y++;

            // Batu menghilang ketika sudah sampai di batas bawah
             if(batuan[i].y >= tinggi) {
                batuan.erase(batuan.begin() + i);
                i--;
                continue;
             }
            
        }

        for(auto &b : batuan) {
            mvprintw(b.y, b.x, "*");
        }

        refresh();
        napms(35);
    }


    endwin();
    return 0;
}
