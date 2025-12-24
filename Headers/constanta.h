#ifndef CONSTANTA_H
#define CONSTANTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Konstanta Untuk Bersihkan Layar
#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

// Konstanta Teks
#define LINEEQ         "=========================================================\n"
#define LINEDASH       "---------------------------------------------------------\n"
#define JUDULPROGRAM   "           $$ CUAN | CATATAN KEUANGAN HARIAN $$          \n"
#define TAGLINESPLASH  "     Setiap catatan adalah langkah menuju masa depan     \n"
#define TAGLINEENTER   "               Tekan ENTER untuk melanjutkan             \n"
#define TAGLINEUTAMA   "           \"Keuangan rapi, hidup lebih pasti\"          \n"
#define TAGLINEBERANDA "     \"Catat setiap rupiah, wujudkan setiap impian\"     \n"
#define HEMAT          "Pengeluaran bulan ini terkendali sesuai rencana. Ini menunjukkan disiplin finansial yang konsisten."
#define BOROS          "Perhatian: pengeluaran bulan ini melebihi batas yang ditetapkan. Perlu evaluasi dan penyesuaian."

// Konstanta Nama FILE
#define FILEUSER        "DataProgram/fileDataUser.txt"
#define FILEPEMASUKAN   "DataProgram/fileDataPemasukan.txt"
#define FILEPENGELUARAN "DataProgram/fileDataPengeluaran.txt"

// Konstanta Warna
#define BOLD "\x1B[1m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[38;2;8;11;161m"
#define YELLOW "\x1B[33m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

#endif