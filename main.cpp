#include <ncurses/curses.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstring>

using namespace std;

struct batu {
    int x, y;
};

void batas(WINDOW* win, int lebar, int tinggi) {
    for(int i = 0; i < lebar; i++) {
        mvwprintw(win, 0, i, "#");
        mvwprintw(win, tinggi - 1, i, "#");

    for(int i = 0; i < tinggi; i++) {
        mvwprintw(win, i, 0, "#");
        mvwprintw(win, i, lebar - 1, "#");
        }
    }
}

void batasSelesai(int lebar, int tinggi) {
    for(int i = 0; i < lebar; i++) {
        mvprintw(0, i, "#");
        mvprintw(tinggi, i, "#");

    for(int i = 0; i < tinggi; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, lebar - 1, "#");
         }
    }
}

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahOpsi);

void print_judul(WINDOW *win) {
    int lebar = 40;

    const char *judul[] = {
        "  ____   ___   ____ _  __",
        " |  _ \\ / _ \\ / ___| |/ /",
        " | |_) | | | | |   | ' / ",
        " |  _ <| |_| | |___| . \\ ",
        " |_| \\_\\\\___/ \\____|_|\\_\\",
        "",
        "  _____ _    _     _     ",
        " |  ___/ \\  | |   | |    ",
        " | |_ / _ \\ | |   | |    ",
        " |  _/ ___ \\| |___| |___ ",
        " |_|/_/   \\_\\_____|_____|"
    };

    int startY = 1;

    for (int i = 0; i < 11; i++) {
        int len = strlen(judul[i]);
        int posX = (lebar - len) / 2;
        mvwprintw(win, startY + i, posX, "%s", judul[i]);
    }
}

int main() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    srand(time(NULL));
    
    int lebar = 40;
    int tinggi = 20;
    int pemain = lebar / 2;
    int skor = 0;
    bool selesai = false;

    vector<batu> batuan;

    WINDOW *menu_win = newwin(tinggi, lebar, 0, 0);
    keypad(menu_win, TRUE);

    const char *opsi[] = {
        "Mulai",
        "Cara Bermain",
        "Credit",
        "Keluar"
    };

    int jumlahOpsi = sizeof(opsi) / sizeof(opsi[0]);
    int pilihanTerpilih = 0;
    int pilihan = -1;

    while (1) {
        werase(menu_win);
        batas(menu_win, lebar, tinggi);

        print_judul(menu_win);
        print_menu(menu_win, pilihanTerpilih, opsi, jumlahOpsi);

        wrefresh(menu_win);
        int tombol = wgetch(menu_win);
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih <= 0)
                    pilihanTerpilih = jumlahOpsi - 1;
                else
                    --pilihanTerpilih;
                break;
            case KEY_DOWN:
                if (pilihanTerpilih >= jumlahOpsi - 1)
                    pilihanTerpilih = 0;
                else
                    ++pilihanTerpilih;
                break;
            case 10:
                pilihan = pilihanTerpilih;
                break;
            default:
                break;
        }

    if (pilihan == 0) {
        selesai = false;
        skor = 0;
        pemain = lebar / 2;
        batuan.clear();

        WINDOW* gamewin = newwin(tinggi + 1, lebar, 0, 0);
        nodelay(gamewin, TRUE);
        keypad(gamewin, TRUE);

        while(!selesai) {
            werase(gamewin);
            batas(gamewin, lebar, tinggi);

            int gerak = wgetch(gamewin);
            switch(gerak) {
                case KEY_LEFT:
                case 'a':
                    if (pemain > 1) pemain--;
                    break;

                case KEY_RIGHT:
                case 'd':
                    if (pemain < lebar - 2) pemain++;
                    break;
                
                case 'q':
                    selesai = true;
                    break;
            }

            mvwprintw(gamewin, tinggi - 2, pemain, "A");

            // Menambahkan batu secara acak
            if(rand() % 5 == 0) {
                batu b;
                b.x = rand() % lebar;
                b.y = 0;
                batuan.push_back(b);
            }

            for (size_t i = 0; i < batuan.size(); i++) {
                batuan[i].y++;

                if(batuan[i].y >= tinggi) {
                    skor++;
                    batuan.erase(batuan.begin() + i);
                    i--;
                    continue;
                }
 
                if(batuan[i].y == tinggi - 1 && batuan[i].x == pemain) {
                    selesai = true;
                }

            }

            for(auto &b : batuan) {
                mvwprintw(gamewin, b.y, b.x, "*");
            }

            mvwprintw(gamewin, 2, 1, "Skor: %d", skor);
            mvwprintw(gamewin, 3, 1, "Tekan q untuk menyerah");
            wrefresh(gamewin);
            if(skor <= 30) {
                napms(45);
            } else if(skor > 30 && skor <= 70) {
                napms(40);
            } else if(skor > 70 && skor <= 120) {
                napms(35);
            } else if(skor > 120 && skor <= 300) {
                napms(30);
            } else {
                napms(25);
            }

        }

        clear();
        batasSelesai(lebar, tinggi);
        mvprintw(tinggi / 2, lebar / 2 - 5, "Game Over!");
        mvprintw(tinggi / 2 + 1, lebar / 2 - 7, "Total Skor: %d", skor);
        mvprintw(tinggi / 2 + 5, lebar / 2 - 17, "Tekan tombol apa saja untuk keluar! ");
        if(skor < 30) {
            mvprintw(tinggi / 2 + 2, lebar / 2 - 7, "'Masih Pemula'");
        } else if (skor >= 30 && skor < 120) {
            mvprintw(tinggi / 2 + 2, lebar / 2 - 5, "'Lumayan OK.'");
        } else if (skor >= 350 && skor < 500) {
            mvprintw(tinggi / 2 + 2, lebar / 2 - 5, "'Hampir Jadi Sepuh..'");
        } else if (skor >= 1000) {
            mvprintw(tinggi / 2 + 2, lebar / 2 - 5, "'Ampun Puh Sepuh...'");
        }
        refresh();
        nodelay(stdscr, FALSE);
        getch();
        pilihan = -1;
    }

    if (pilihan == 1) {
        clear();
        mvprintw(2, 2, "Cara Bermain:");
        mvprintw(4, 4, "1. Gunakan tombol panah kiri dan kanan atau 'a' dan 'd' untuk bergerak.");
        mvprintw(5, 4, "2. Hindari batu yang jatuh dari atas.");
        mvprintw(6, 4, "3. Setiap menghindar dari bati skor akan bertambah.");
        mvprintw(7, 4, "4. Tekan 'q' untuk menyerah dan keluar dari permainan.");
        mvprintw(9, 2, "Tekan tombol apa saja untuk kembali ke menu utama.");
        refresh();
        getch();
        clear();
        pilihan = -1;
}

    if(pilihan == 2) {
        clear();
        mvprintw(2, 2, "Credit:");
        mvprintw(4, 4, "Game ini dibuat oleh:");
        mvprintw(5, 6, "1. Juanda Virgo Matanari (2517051077)");
        mvprintw(6, 6, "2. Zahlian Akhiansyah (2557051006)");
        mvprintw(7, 6, "3. Febiola Hayu Suciani (2517051082)");
        mvprintw(9, 2, "Terima kasih telah memainkan game ini!");
        mvprintw(11, 2, "Tekan tombol apa saja untuk kembali ke menu utama.");
        refresh();
        getch();
        clear();
        pilihan = -1;
    }

    if(pilihan == 3) {
        break;
    }
}
    clrtoeol();
    refresh();
    endwin();
    
    return 0;
}


void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahOpsi) {
    int lebar = 40;
    int tinggi = 20;

    int offsetJudul = 8; 
    int opsiTengah = offsetJudul + (tinggi - offsetJudul - jumlahOpsi) / 2 + 1;

    for (int i = 0; i < jumlahOpsi; ++i) {
        int len = strlen(opsi[i]);
        int pos = (lebar - len) / 2;

        if (i == pilihanTerpilih) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, opsiTengah + i, pos, "%s", opsi[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, opsiTengah + i, pos, "%s", opsi[i]);
        }
    }

    wrefresh(menu_win);
}

