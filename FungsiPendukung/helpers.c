#include "../Headers/helpers.h"

// Fungsi Untuk Header
void header(char judul[255], char tagline[255]){
    printf(LINEEQ);
    printf(BOLD BLUE "%s" RESET, judul);
    printf("%s%s%s", LINEEQ, tagline, LINEDASH);
}

// Fungsi Reset Input & Screen
void resetInputScreen(){
    fflush(stdin);
    system(CLEAR_CMD);
}

// Fungsi Untuk Inputan String
void inputString(const char *label, char *buffer, int size){
    printf("%s", label);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Fungsi Untuk Inputan integer
void inputInt(const char *label, int *value){
    char buffer[50];
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    *value = atoi(buffer); 
}

// Fungsi Untuk Inputan Double
void inputDouble(const char *label, double *value){
    char buffer[50];
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    *value = atof(buffer);
}

// Fungsi Untuk Alert
void alert(AlertType type, const char *message){
    printf(LINEDASH);
    switch(type){
    case ALERT_SUCCESS: printf("%s%s[$] %s%s\n", BOLD, GREEN, message, RESET); break;
    case ALERT_ERROR: printf("%s%s[x] %s%s\n", BOLD, RED, message, RESET); break;
    case ALERT_WARNING: printf("%s%s[!] %s%s\n", BOLD, YELLOW, message, RESET);; break;
    case ALERT_INFO: printf("%s%s[i] %s%s\n", BOLD, CYAN, message, RESET); break;
    case ALERT_DEFAULT: printf("%s%s[-] %s%s\n", BOLD, RESET, message, RESET); break;
    default: printf("%s%s[-] %s%s\n", BOLD, RESET, message, RESET);break;
    }
    printf(LINEEQ);
}

// Fungsi Untuk Get ID Terakhir
int getLastID(const char *filename, const char *format, int fieldCount){
    fp = fopen(filename, "r");
    if(fp == NULL) return 0;

    int lastID = 0;
    char line[512];
    fgets(line, sizeof(line), fp);

    while(fgets(line, sizeof(line), fp)){
        int id;
        char buf1[128], buf2[128], buf3[256];
        int i1, i2;
        double d1;

        // parsing sesuai format yang dikirim
        int matched = sscanf(line, format, &id, buf1, buf2, buf3, &d1, &i1, &i2);
        if(matched == fieldCount){
            lastID = id;
        }
    }

    fclose(fp);
    return lastID;
}

// Fungsi Untuk get Tanggal Hari Ini
char* getTanggal() {
    static char buffer[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return buffer;
}

// Fungsi Untuk Jumlah Hari Bulan
bool cekTahunKabisat(int tahun){
    return (tahun % 400 == 0) || (tahun % 4 == 0 && tahun % 100 != 0);
}

int getJumlahHari(int bulan, int tahun){
    int hariPerBulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(bulan == 2 && cekTahunKabisat(tahun)){
        return 29;
    } return hariPerBulan[bulan - 1];
}

// Fungsi Untuk Get Data Ringkasan
DataRingkasan getDataRingkasan(int IDUser){
    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);
    int bulan = tm.tm_mon + 1;
    int tahun = tm.tm_year + 1900; 

    DataRingkasan hasil; 
    double totalPengeluaran = getTotalPengeluaran(bulan, tahun, IDUser);
    hasil.pengeluaranHariIni = getPengeluaranHariIni(FILEPENGELUARAN, getTanggal(), IDUser); 
    hasil.pemasukanBulanan = getPemasukanBulanan(FILEPEMASUKAN, bulan, tahun, IDUser); 
    hasil.saldoHariIni = hasil.pemasukanBulanan - totalPengeluaran; 
    return hasil;
}

// Fungsi Untuk Mengambik Pemasukan Bulanan
double getPemasukanBulanan(const char *filename, int bulan, int tahun, int IDUser){
    fp = fopen(filename, "r");
    if(fp == NULL) return 0;

    int id, b, t, idUser;
    double jumlah, total = 0;

    char header[256];
    fgets(header, sizeof(header), fp);
    while(fscanf(fp, "%d|%d|%d|%lf|%d\n", &id, &b, &t, &jumlah, &idUser) == 5){
        if(b == bulan && t == tahun && idUser == IDUser){
            total += jumlah;
        }
    }fclose(fp);
    return total;
}

// Fungsi Untuk Mengambil Data Pengeluaran Hari Ini
double getPengeluaranHariIni(const char *filename, const char *tanggalHariIni, int IDUser){
    fp = fopen(filename, "r");
    if(fp == NULL) return 0;

    int id, userID;
    double jumlah, total = 0;
    char tanggal[20], kategori[100], deskripsi[255], headerFile[255];
    fgets(headerFile, sizeof(headerFile), fp);
    while(fscanf(fp, "%d|%19[^|]|%99[^|]|%254[^|]|%lf|%d\n",&id, tanggal, kategori, deskripsi, &jumlah, &userID) == 6){
        if(strcmp(tanggal, tanggalHariIni) == 0 && userID == IDUser){
            total += jumlah;
        }
    }fclose(fp);
    return total;
}

// Fungsi Untuk Mengambil Datat Total Pengeluaran
double getTotalPengeluaran(int bulan, int tahun, int IDUser){
    double jumlah, totalPengeluaran = 0;
    char tanggal[20], kategori[100], deskripsi[255], headerFile[255];
    int id, idUser;

    // Ambil tanggal hari ini dari tm_info
    time_t t = time(NULL);
    tm_info = *localtime(&t);

    fp = cekFile(FILEPENGELUARAN, "r");
    fgets(headerFile, sizeof(headerFile), fp);
    while(fscanf(fp, "%d|%19[^|]|%99[^|]|%254[^|]|%lf|%d\n", &id, tanggal, kategori, deskripsi, &jumlah, &idUser) == 6){
        int d, m, y;
        sscanf(tanggal, "%d-%d-%d", &d, &m, &y);

        if(m == bulan && y == tahun && idUser == IDUser){
            // hanya pengeluaran sampai hari ini
            if (d <= tm_info.tm_mday) {
                totalPengeluaran += jumlah;
            }
        }
    }fclose(fp);
    return totalPengeluaran;
}

// Fungsi Buka File
FILE* cekFile(const char *namaFile, const char *mode){
    fp = fopen(namaFile, mode);
    if(fp == NULL){
        alert(ALERT_ERROR, "Tidak bisa membuka file!");
        return NULL;
    }
    return fp;
}

// Fungsi Ambil ID User
int getIDUser(){
    int ID = User.IDUser;
    return ID;
}

// Fungsi Kembali Halaman Beranda
void kembaliBeranda(){
    getchar();
    setHalamanBeranda();
}

// Fungsi Kembali Halaman Utama
void kembaliUtama(){
    getchar();
    setHalamanUtama();
}

// Fungsi Untuk Logput
void logoutUser(){
    User.IDUser = -1;
    strcpy(User.namaUser, "");
    strcpy(User.password, "");
    system(CLEAR_CMD);
    alert(ALERT_INFO, "Anda telah logout. Silakan login kembali untuk mengakses program!");
    getchar();
    kembaliUtama();
}

// Fungsi Keluar Program
void keluarProgram(){
    system(CLEAR_CMD);
    alert(ALERT_INFO, "TERIMA KASIH TELAH MENGGUNAKAN PROGRAM CUAN");
    return;
}
