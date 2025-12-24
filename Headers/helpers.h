#ifndef HELPERS_H
#define HELPERS_H

// Header File Constanta
#include "constanta.h"

// Header File Models
#include "models.h"

// Variabel Struct dan Pointer 
PemasukanBulanan pemasukan;
PengeluaranHarian *pengeluaran;
FILE *fp;
int pilihan;
struct tm tm_info;

// Fungsi Bantu
void  header(char judul[255], char tagline[255]);
void  inputString(const char *label, char *buffer, int size);
void  inputInt(const char *label, int *value);
void  inputDouble(const char *label, double *value);
void  alert(AlertType type, const char *message);
int   getJumlahHari(int bulan, int tahun);
FILE* cekFile(const char *namaFile, const char *mode);
void  resetInputScreen();
char* getTanggal();
void  kembaliBeranda();
void  kembaliUtama();
void  logoutUser();
int   getIDUser();
void  keluarProgram();

// Fungsi Untuk Ambil Data Pemasukan Dan Pengeluaran
int    getLastID(const char *filename, const char *format, int fieldCount);
double getPemasukanBulanan(const char *filename, int bulan, int tahun, int IDUser);
double getPengeluaranHariIni(const char *filename, const char *tanggalHariIni, int idUserTarget);
double getTotalPengeluaran(int bulan, int tahun, int IDUser);

// Fungsi Laporan Harian dan Bulanan
DataRingkasan    getDataRingkasan(int IDUser);
AnalisisLaporan  getAnalisisLaporan(int IDUser);
RingkasanHarian  getRingkasanHarian(const char *tanggalHariIni, int IDUser, FILE *out, int toFile);
RingkasanBulanan getRingkasanBulanan(int bulan, int tahun, double batasHarian, int jumlahHariBulan, int IDUser, FILE *out, int toFile);

// Fungsi Tampilan
void splashScreen();
void halamanUtama();
void halamanBeranda(double uang, double saldo, char tanggal[20]);
void setHalamanUtama();
void setHalamanBeranda();

// Menu Login
void halamanLogin();
void loginUser();

// Menu Register
void halamanRegister();
void registerUser();

// Menu Pemasukan
void halamanPemasukan();
void setMenuPemasukan(int IDUser);

// Menu Pengeluaran
void halamanPengeluaran();
void setMenuPengeluaran(int IDUser);

// Menu Laporan Harian
void laporanHarian(const char *tanggalHariIni, int IDUser);

// Menu Laporan Bulananan
void laporanBulanan(const char *tanggalHariIni, int IDUser);

#endif