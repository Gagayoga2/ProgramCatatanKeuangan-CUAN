/* Fungsi Bagian Tampilan Program */
#include "../Headers/helpers.h"

// Tampilan Splash Screen Program
void splashScreen() {
    system(CLEAR_CMD);
    header(JUDULPROGRAM, TAGLINESPLASH);
    printf("%s%s", TAGLINEENTER, LINEEQ);
    getchar();  
    setHalamanUtama();
}

// Tampilan Halaman Utama
void halamanUtama(){
    system(CLEAR_CMD);
    header(JUDULPROGRAM, TAGLINEUTAMA);
    printf("# Menu Utama\n%s", LINEDASH);
    printf("[1] Login\n");
    printf("[2] Register\n");
    printf("[3] Tentang Program\n");
    printf("[4] Keluar\n%s", LINEEQ);
    printf("Masukkan pilihan Anda: ");
}

// Tampilan Halaman Beranda
void halamanBeranda(double uang, double saldo, char tanggal[20]){
    system(CLEAR_CMD);
    header(JUDULPROGRAM, TAGLINEBERANDA);
    printf("# Ringkasan Hari Ini  : %s\n", tanggal);
    printf(BOLD "Pengeluaran  : "BLUE"Rp.%0.2f"RESET"\n", uang);
    printf(BOLD "Sisa Saldo   : "BLUE"Rp.%0.2f"RESET"\n", saldo);
    printf(LINEDASH);
    printf("# MENU :\n");
    printf("[1] Catat Pemasukan\n");
    printf("[2] Catat Pengeluaran\n");
    printf("[3] Laporan Harian\n");
    printf("[4] Laporan Bulanan\n");
    printf("[5] Keluar\n%s", LINEEQ);
    printf("Masukkan pilihan Anda: ");
}

// Tampilan Halaman Login
void halamanLogin(){
    resetInputScreen();
    printf("======================= [LOGIN] =========================\n");
    inputString("Masukan Username : ", user.namaUser, sizeof(user.namaUser));
    inputString("Masukan Password : ", user.password, sizeof(user.password));
    loginUser();
}

// Tampilan Halaman Login
void halamanRegister(){
    resetInputScreen();
    char confirmPass[50];
    printf("===================== [REGISTER] ========================\n");
    inputString("Masukan Username : ", user.namaUser, sizeof(user.namaUser));

    do {
        inputString("Masukan Password : ", user.password, sizeof(user.password));
        inputString("Konfirmasi Password : ", confirmPass, sizeof(confirmPass));

        if (strcmp(user.password, confirmPass) != 0) {
            printf("\033[31m[x] Password tidak sama, silakan ulangi!\033[0m\n");
        }
    } while (strcmp(user.password, confirmPass) != 0);
    registerUser();
}

// Tampilan Halaman Pemasukan
void halamanPemasukan(){
    resetInputScreen();
    printf("===================== [PEMASUKAN] =======================\n");
    printf("# MENU PENCATATAN PEMASUKAN %d\n%s", user.IDUser, LINEDASH);
    inputInt("Masukan Tahun    : ", &pemasukan.tahun);
    inputInt("Masukan Bulan    : ", &pemasukan.bulan);
    inputDouble("Jumlah Pemasukan : ", &pemasukan.jumlah);
    pemasukan.IDUser = user.IDUser;
    setMenuPemasukan();
}

// Tampilan Halaman Pengeluaran
void halamanPengeluaran(){
    resetInputScreen();
    pengeluaran = (pengeluaranHarian*) malloc(sizeof(pengeluaranHarian));

    // Alokasi string dinamis
    pengeluaran->tanggal   = (char*) malloc(20);
    pengeluaran->kategori  = (char*) malloc(50);
    pengeluaran->deskripsi = (char*) malloc(100);
    strcpy(pengeluaran->tanggal, getTanggal());

    printf("===================== [PENGELUARAN] =======================\n\n");
    printf("Tanggal    : %s\n", pengeluaran->tanggal);
    inputString("Kategori   : ", pengeluaran->kategori, 50);
    inputString("Deskripsi  : ", pengeluaran->deskripsi, 100);
    inputDouble("Jumlah Rp. : ", &pengeluaran->jumlah);
}