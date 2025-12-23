#include "../Headers/helpers.h"

// Fungsi Halaman Utama
void setHalamanUtama(){
    halamanUtama();
    scanf("%d", &pilihan);

    switch ((MenuUtama)pilihan){
    case MENU_LOGIN: halamanLogin(); break;
    case MENU_REGISTER: halamanRegister(); break;
    case MENU_TENTANG: halamanLogin(); break;
    case MENU_LEFT: system(CLEAR_CMD); break;
    default: alert(ALERT_ERROR, "Pilihan tidak valid!"); break;
    }
}

// Fungsi login
void loginUser(){
    char line[512], nama[255], pass[50];
    int id;

    fp = fopen(FILEUSER, "r");
    if (fp == NULL) {
        alert(ALERT_ERROR, "Error: file data user tidak ditemukan!");
    }

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%254[^|]|%49[^\n]", &id, nama, pass) == 3) {
            if (strcmp(user.namaUser, nama) == 0 && strcmp(user.password, pass) == 0) {
                user.IDUser = id;
                fclose(fp);
                alert(ALERT_SUCCESS, "Login Berhasil. Selamat Datang di CUAN!");
                kembaliBeranda();
            }else{
                fclose(fp);
                alert(ALERT_WARNING, "Login gagal! Periksa username dan password Anda!");
                kembaliUtama();
            }
        }
    }
}

// Fungsi Register
void registerUser(){
    int count = 0;

    fp = fopen(FILEUSER, "r");
    if (fp != NULL) {
        char line[512];
        while (fgets(line, sizeof(line), fp)) {
            count++;
        }
        fclose(fp);
    } user.IDUser = count;

    fp = fopen(FILEUSER, "a");
    if (fp == NULL) {
        alert(ALERT_ERROR, "Error: tidak bisa membuka file!");
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "ID|Nama User|Password\n");
    }

    fprintf(fp, "%d|%s|%s\n", user.IDUser, user.namaUser, user.password);
    fclose(fp);

    alert(ALERT_SUCCESS, "Registrasi berhasil!, Silakan Login Dahulu");
    kembaliUtama();
}

// Fungsi Halaman Beranda
void setHalamanBeranda(){
    DataRingkasan saldo = getDataRingkasan(user.IDUser);
    halamanBeranda(saldo.pengeluaranHariIni, saldo.saldoHariIni, getTanggal());
    scanf("%d", &pilihan);

    switch ((MenuBeranda)pilihan){
    case MENU_PEMASUKAN: halamanPemasukan(); break;
    case MENU_PENGELUARAN: setMenuPengeluaran(); break;
    case MENU_LAPORAN_HARIAN: laporanHarian(getTanggal(), user.IDUser); break;
    case MENU_LAPORAN_BULANAN: laporanBulanan(getTanggal(), user.IDUser); break;
    case MENU_LOGOUT: logoutUser(); break;
    default: alert(ALERT_ERROR, "Pilihan tidak valid!"); break;
    }
}

// Fungsi Menu Pencatatan Pemasukan
void setMenuPemasukan(){
    int newID = getLastID(FILEPEMASUKAN, "%d|%d|%d|%lf|%d\n", 5) + 1;
    fp = fopen(FILEPEMASUKAN, "a");
    if (fp == NULL) {
        alert(ALERT_ERROR, "Error : Error membuka file pemasukan!");
        return;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "ID|Bulan|Tahun|Jumlah|IDUser\n");
    }

    fprintf(fp, "%d|%d|%d|%.2lf|%d\n", newID, pemasukan.bulan, pemasukan.tahun, pemasukan.jumlah, user.IDUser);
    fclose(fp);
    alert(ALERT_SUCCESS, "Pemasukan Berhasil di Catat!");
    printf("Tekan ENTER untuk kembali ke menu utama...\n");
    kembaliBeranda();
}

void setMenuPengeluaran(){
    char lagi;
    do{
        halamanPengeluaran();
        int newID = getLastID(FILEPENGELUARAN, "%d|%31[^|]|%99[^|]|%255[^|]|%lf|%d", 6) + 1;

        fp = fopen(FILEPENGELUARAN, "a");
        if (fp == NULL) {
            alert(ALERT_ERROR, "Error : Tidak bisa membuka file pengeluaran!");
            return;
        }
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0) {
            fprintf(fp, "ID|Tanggal|Kategori|Deskripsi|Jumlah|IDUser\n");
        }
        fprintf(fp, "%d|%s|%s|%s|%.2f|%d\n", newID,pengeluaran->tanggal, pengeluaran->kategori, pengeluaran->deskripsi, pengeluaran->jumlah, user.IDUser);
        fclose(fp);

        alert(ALERT_SUCCESS, "Pengeluaran berhasil dicatat!");

        // Bebaskan memori
        free(pengeluaran->tanggal);
        free(pengeluaran->kategori);
        free(pengeluaran->deskripsi);
        free(pengeluaran);

        // Tanya apakah mau isi lagi
        alert(ALERT_INFO, "Apakah ingin menambah pengeluaran lagi? (y/n): ");
        scanf("%c", &lagi);
        getchar();
    }while (lagi == 'y' || lagi == 'Y');
    setHalamanBeranda();
}