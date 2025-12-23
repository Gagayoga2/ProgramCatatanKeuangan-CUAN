#ifndef MODELS_H
#define MODELS_H

// Struct User
struct{
    int IDUser;
    char namaUser[255];
    char password[50];
}user;

/* ================================= STRUCT PEMASUKAN DAN PENGELUARAN =================================*/
// Struct Pemasukan dan Pengeluaran
typedef struct {
    int bulan;
    int tahun;
    double jumlah;
    int IDUser;
} pemasukanBulanan;

typedef struct {
    char *tanggal;
    char *kategori;
    char *deskripsi;
    double jumlah;
} pengeluaranHarian;

/* =========================================== STRUCT LAPORAN ================================================*/
// Struct Data Ringkasan
typedef struct{ 
    double pengeluaranHariIni; 
    double pemasukanBulanan; 
    double saldoHariIni; 
} DataRingkasan;

// Struct Ringkasan & Analisis Harian Untuk Laporan Harian
typedef struct{
    double total;
    double maxJumlah;
    char kategoriMax[100];
    int adaData;
} RingkasanHarian;
typedef struct {
    int bulan;
    int tahun;
    int jumlahHariBulan;
    double pemasukanBulanan;
    double batasHarian;
    double sisaSaldo;
} AnalisisLaporan;

// Struct Ringkasana Bulanana Untuk Laporan Bulanan
typedef struct {
    double totalBulanan;
    double maxKategoriJumlah;
    char kategoriMax[100];
    double maxHariJumlah;
    char tanggalMax[20];
    int adaData;

    // Data Tambahan
    double rataRataHarian;
    int hariBoros;
    int hariHemat;
    int hariTanpaPengeluaran;
    char mingguMax[20];
    double maxMingguJumlah;
    int transaksiTerbanyak;
    char tanggalTransaksiMax[20];
    double marginBulanan;
} RingkasanBulanan;

/* ===================================================== STRUCT ENUM ALERT & MENU =================================================*/
// ENUM Alert
typedef enum {
    ALERT_SUCCESS,
    ALERT_ERROR,
    ALERT_WARNING,
    ALERT_INFO,
    ALERT_DEFAULT
} AlertType;

// Enum Menu Beranda
typedef enum {
    MENU_PEMASUKAN = 1,
    MENU_PENGELUARAN,
    MENU_LAPORAN_HARIAN,
    MENU_LAPORAN_BULANAN,
    MENU_LOGOUT
} MenuBeranda;

// Definisi enum
typedef enum {
    MENU_LOGIN = 1,
    MENU_REGISTER,
    MENU_TENTANG,
    MENU_LEFT
} MenuUtama;

#endif