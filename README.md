Project ini merupakan sebuah **game terminal sederhana** yang dibuat menggunakan **bahasa pemrograman C++** dan **library ncurses**.
Game ini mengusung konsep **survival**, di mana pemain harus menghindari batu yang jatuh dari atas layar selama mungkin untuk mendapatkan skor tertinggi.

Project ini dibuat sebagai **tugas pembelajaran** untuk memahami penggunaan ncurses, pengolahan input keyboard secara real-time, serta logika dasar pembuatan game berbasis terminal.

## Gambaran Umum Game
Pemain direpresentasikan dengan karakter **A** dan berada di bagian bawah layar.
Batu akan jatuh dari atas layar secara acak dan semakin lama kecepatan jatuh batu akan meningkat.
Setiap batu yang berhasil dihindari akan menambah skor pemain.

Permainan akan berakhir apabila pemain terkena batu atau memilih menyerah.

## Fitur Utama
* Menu utama interaktif
* Pergerakan pemain secara real-time
* Batu jatuh secara acak
* Sistem skor
* Tingkat kesulitan meningkat seiring skor
* Batas layar atau border permainan
* Layar Game Over dengan total skor

## Cara Bermain
1. Jalankan program melalui terminal
2. Gunakan tombol panah kiri dan kanan atau tombol a dan d untuk menggerakkan pemain
3. Hindari batu yang jatuh dari atas layar
4. Setiap batu yang berhasil dihindari akan menambah skor
5. Tekan tombol q untuk menyerah dan mengakhiri permainan


## Cara Menjalankan Program
Pastikan sistem sudah terinstall compiler C++ dan library ncurses.

### Compile
```bash
g++ main.cpp -o game -lncurses
```

### Jalankan
```bash
./game
```

## Pembagian Tugas Pengerjaan Project
Juanda Virgo Matanari
* Pembuatan menu utama
* Implementasi layar Game Over
* Pengaturan alur permainan
* Penggabungan dan perapihan kode

Febiola Hayu Suciani
* Pembuatan batas layar atau border
* Implementasi pergerakan pemain
* Pengaturan kontrol keyboard

Zahlian Akhiansyah
* Implementasi batu jatuh secara acak
* Sistem penambahan skor
* Logika tabrakan dan kondisi Game Over
  

## Kelebihan dan Kekurangan

### Kelebihan
* Ringan dan dapat dijalankan langsung di terminal
* Menggunakan ncurses sehingga tampilan lebih rapi
* Cocok untuk pembelajaran logika dasar game

### Kekurangan
* Tampilan masih berbasis teks
* Gameplay masih sederhana
* Belum memiliki sistem level atau penyimpanan skor


## Pengembangan Selanjutnya
Beberapa ide pengembangan yang dapat dilakukan ke depannya:
* Menambahkan level permainan
* Menyimpan skor tertinggi
* Menambahkan variasi rintangan
* Menambahkan efek visual atau suara
