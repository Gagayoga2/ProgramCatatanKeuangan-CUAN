#include "../Headers/helpers.h"

/* =========================== LAPORAN HARIAN ========================== */
// Fungsi Ambil Data Laporan Harian
RingkasanHarian getRingkasanHarian(const char *tanggalHariIni, int IDUser, FILE *out, int toFile){
    RingkasanHarian ringkasan = {0, 0, "", 0};
    char tanggal[20], kategori[100], deskripsi[255], headerFile[255];
    int id, idUser, counter = 1;
    double jumlah;
    cekFile(FILEPENGELUARAN, "r");
    fgets(headerFile, sizeof(headerFile), fp);
    while(fscanf(fp, "%d|%19[^|]|%99[^|]|%254[^|]|%lf|%d\n", &id, tanggal, kategori, deskripsi, &jumlah, &idUser) == 6){
        if (strcmp(tanggal, tanggalHariIni) == 0 && idUser == IDUser){
            ringkasan.adaData = 1;
            ringkasan.total += jumlah;
            // Hitung Transaksi
            ringkasan.jumlahTransaksi++;
            if(jumlah > ringkasan.maxJumlah){
                ringkasan.maxJumlah = jumlah; 
                strcpy(ringkasan.kategoriMax, kategori); 
            }

            if(jumlah > ringkasan.maxJumlah){
                ringkasan.maxJumlah = jumlah;
                strcpy(ringkasan.kategoriMax, kategori);
            }
            if(toFile){
                fprintf(out, "%-3d | %-20s | %-30s | Rp.%8.2f\n", counter, kategori, deskripsi, jumlah);
            }else{
                printf("%-3d | %-20s | %-30s | Rp.%8.2f\n", counter, kategori, deskripsi, jumlah);
            }
            counter++;
        }
    }
    fclose(fp);
    if (ringkasan.total > 0){ 
        ringkasan.persenKategoriMax = (ringkasan.maxJumlah / ringkasan.total) * 100.0; 
    }
    return ringkasan;
}

// Fungsi Analisis Harian
AnalisisLaporan getAnalisisLaporan(int IDUser){
    AnalisisLaporan a;
    time_t t = time(NULL);
    tm_info = *localtime(&t);
    a.bulan = tm_info.tm_mon + 1;
    a.tahun = tm_info.tm_year + 1900;
    a.pemasukanBulanan = getPemasukanBulanan(FILEPEMASUKAN, a.bulan, a.tahun, IDUser);
    a.jumlahHariBulan = getJumlahHari(a.bulan, a.tahun);
    a.batasHarian = a.pemasukanBulanan / a.jumlahHariBulan;
    a.sisaSaldo = a.pemasukanBulanan - getTotalPengeluaran(a.bulan, a.tahun, IDUser);
    return a;
}

/* =========================== LAPORAN BULANAN ========================== */
// Fungsi Analisis Bulanan
RingkasanBulanan getRingkasanBulanan(int bulan, int tahun, double batasHarian, int jumlahHariBulan, int IDUser, FILE *out, int toFile) {
    RingkasanBulanan r = {0};
    char headerFile[255];
    fp = cekFile(FILEPENGELUARAN, "r");
    fgets(headerFile, sizeof(headerFile), fp);

    int id, idUser, counter = 1, kategoriCount = 0, transaksiHari = 0;
    double jumlah, totalHari = 0, totalKategori[50] = {0}, totalMinggu[5] = {0};
    char tanggal[20], kategori[100], deskripsi[255];
    char hariSebelumnya[20] = "", namaKategori[50][100];

    while(fscanf(fp, "%d|%19[^|]|%99[^|]|%254[^|]|%lf|%d\n", &id, tanggal, kategori, deskripsi, &jumlah, &idUser) == 6) {
        int d, m, y;
        sscanf(tanggal, "%d-%d-%d", &d, &m, &y);
        if(m == bulan && y == tahun && idUser == IDUser){
            r.adaData = 1;
            r.totalBulanan += jumlah;
            int found = 0;
            // kategori terbesar
            for(int i = 0; i < kategoriCount; i++){
                if(strcmp(namaKategori[i], kategori) == 0) {
                    totalKategori[i] += jumlah;
                    found = 1;
                    break;
                }
            }
            if(!found){
                strcpy(namaKategori[kategoriCount], kategori);
                totalKategori[kategoriCount] = jumlah;
                kategoriCount++;
            }

            // per hari
            if(strcmp(hariSebelumnya, tanggal) != 0){
                // evaluasi hari sebelumnya
                if(hariSebelumnya[0] != '\0'){
                    if(totalHari > batasHarian) r.hariBoros++;
                    else r.hariHemat++;
                    if(transaksiHari > r.transaksiTerbanyak) {
                        r.transaksiTerbanyak = transaksiHari;
                        strcpy(r.tanggalTransaksiMax, hariSebelumnya);
                    }
                    if(toFile){
                        fprintf(out, "--------------------------------%s", LINEDASH);
                    }else{ 
                        printf(BOLD BLUE "--------------------------------%s" RESET, LINEDASH);
                    }
                }
                // reset
                totalHari = jumlah;
                transaksiHari = 1;
                strcpy(hariSebelumnya, tanggal);
            }else{
                totalHari += jumlah;
                transaksiHari++;
            }

            if(totalHari > r.maxHariJumlah){
                r.maxHariJumlah = totalHari;
                strcpy(r.tanggalMax, tanggal);
            }

            // minggu (anggap minggu ke-1 = tanggal 1-7, dst)
            int minggu = (d - 1) / 7;
            totalMinggu[minggu] += jumlah;

            if(toFile){
                fprintf(out, "%-3d | %-11s | %-20s | %-30s | Rp.%9.2f\n", counter, tanggal, kategori, deskripsi, jumlah);
            }else{
                printf("%-3d | %-11s | %-20s | %-30s | Rp.%9.2f\n", counter, tanggal, kategori, deskripsi, jumlah);
            }
            counter++;

            // distribusi kategori
            if(!found){
                strcpy(r.namaKategori[r.jumlahKategori], kategori);
                r.totalKategori[r.jumlahKategori] = jumlah;
                r.jumlahKategori++;
            }else{
                for (int i = 0; i < r.jumlahKategori; i++) {
                    if (strcmp(r.namaKategori[i], kategori) == 0) {
                        r.totalKategori[i] += jumlah; break;
                    }
                }
            }
        }
    }fclose(fp);

    // evaluasi hari terakhir
    if(hariSebelumnya[0] != '\0'){
        if(totalHari > batasHarian) r.hariBoros++;
        else r.hariHemat++;
        if(transaksiHari > r.transaksiTerbanyak){
            r.transaksiTerbanyak = transaksiHari;
            strcpy(r.tanggalTransaksiMax, hariSebelumnya);
        }
    }

    // kategori terbesar
    for(int i = 0; i < kategoriCount; i++){
        if (totalKategori[i] > r.maxKategoriJumlah){
            r.maxKategoriJumlah = totalKategori[i];
            strcpy(r.kategoriMax, namaKategori[i]);
        }
    }

    // minggu terboros
    for(int i = 0; i < 5; i++){
        if (totalMinggu[i] > r.maxMingguJumlah){
            r.maxMingguJumlah = totalMinggu[i];
            sprintf(r.mingguMax, "Minggu ke-%d", i+1);
        }
    }

    // rata-rata mingguan
    r.rataRataMingguan = r.totalBulanan / 4.0; // asumsi 4 minggu

    // rata-rata harian
    r.rataRataHarian = r.totalBulanan / jumlahHariBulan;

    // hari tanpa pengeluaran
    r.hariTanpaPengeluaran = jumlahHariBulan - (r.hariBoros + r.hariHemat);

    return r;
}