#include "../Headers/helpers.h"

// Fungsi Untuk Cetak Laporan Bulanan
void headerTabelBulanan(FILE *out, const char *tanggalHariIni, const char *namaUser){ 
    fprintf(out, "================================== [LAPORAN BULANAN] ====================================\n"); 
    fprintf(out, "Pengguna : %s | Tanggal : %s\n", namaUser, tanggalHariIni); 
    fprintf(out, "=========================================================================================\n\n"); 
    fprintf(out, "-----------------------------------------------------------------------------------------\n"); 
    fprintf(out, "%-3s | %-11s | %-20s | %-30s | %-12s\n", "NO", "Tanggal", "Kategori", "Deskripsi", "Jumlah");
    fprintf(out, "-----------------------------------------------------------------------------------------\n"); 
}
void cetakLaporanBulanan(const char *tanggalHariIni, int IDUser){
    AnalisisLaporan analisis = getAnalisisLaporan();
    fflush(stdin);
    char namaFile[255];
    sprintf(namaFile, "Laporan/LaporanBulanan/laporanBulanan_%d-%d_%s.txt", analisis.bulan, analisis.tahun, user.namaUser);

    FILE *out = fopen(namaFile, "w");
    if (out == NULL){
        alert(ALERT_ERROR, "Tidak bisa membuat file laporan!");
        return;
    }

    headerTabelBulanan(out, getTanggal(), user.namaUser);
    RingkasanBulanan r = getRingkasanBulanan(analisis.bulan, analisis.tahun, analisis.batasHarian, analisis.jumlahHariBulan, IDUser, out, 1);
    unsigned int statusFlag = (r.totalBulanan > analisis.batasHarian * analisis.jumlahHariBulan) << 1 | (r.totalBulanan <= analisis.batasHarian * analisis.jumlahHariBulan);

    fprintf(out, "--------------------------------%s", LINEDASH);
    fprintf(out, "Total Pengeluaran Bulan Ini       : "  "Rp.%.2f\n", r.totalBulanan);
    fprintf(out, "Kategori Terbesar                 : %s (Rp.%.2f)\n", r.kategoriMax, r.maxKategoriJumlah);
    fprintf(out, "Hari Terboros                     : %s (Rp.%.2f)\n", r.tanggalMax, r.maxHariJumlah);
    fprintf(out, "Minggu Terboros                   : %s (Rp.%.2f)\n\n", r.mingguMax, r.maxMingguJumlah);
    
    fprintf(out, "Analisis Bulanan:\n");
    fprintf(out, "- Pemasukan Bulan %d-%d         : Rp.%.2f\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
    fprintf(out, "- Jumlah Hari Bulan               : %d Hari\n", analisis.jumlahHariBulan);
    fprintf(out, "- Rata-rata Pengeluaran Harian    : Rp.%.2f\n", r.rataRataHarian);
    fprintf(out, "- Hari Boros vs Hemat             : %d boros %d hemat\n", r.hariBoros, r.hariHemat);
    fprintf(out, "- Hari Tanpa Pengeluaran          : %d Hari\n", r.hariTanpaPengeluaran);
    fprintf(out, "- Hari Dengan Transaksi Terbanyak : %s (%d transaksi)\n", r.tanggalTransaksiMax, r.transaksiTerbanyak);

    double batasBulanan = analisis.batasHarian * analisis.jumlahHariBulan;
    fprintf(out, "- Batas Bulanan                   : Rp.%.2f\n", batasBulanan);
    fprintf(out ,"- Sisa Saldo Bulain %d-%d       : Rp.%.2f\n", analisis.bulan, analisis.tahun, analisis.sisaSaldo);
    fprintf(out, "================================%s", LINEEQ);
    fprintf(out, "%s\n", (statusFlag & (1 << 1)) ? "PENGELUARAN BULAN INI ANDA BOROS!!" : "BAGUS, PENGELUARAN BULAN INI ANDA HEMAT");
    fprintf(out, "================================%s\n", LINEEQ);

    fclose(out);
    system(CLEAR_CMD);
    
    alert(ALERT_SUCCESS, "Laporan berhasil disimpan di folder Laporan!");
    kembaliBeranda();
}

void laporanBulanan(const char *tanggalHariIni, int IDUser){
    resetInputScreen();
    AnalisisLaporan analisis = getAnalisisLaporan();
    printf("================================== [LAPORAN BULANAN] ====================================\n"); 
    printf(BOLD BLUE "Pengguna : %s | Tanggal : %s"RESET"\n", user.namaUser, tanggalHariIni); 
    printf("=========================================================================================\n\n"); 
    printf(BOLD BLUE "-----------------------------------------------------------------------------------------\n" RESET); 
    printf(BOLD "%-3s | %-11s | %-20s | %-30s | %-12s\n", "NO", "Tanggal", "Kategori", "Deskripsi", "Jumlah");
    printf(BOLD BLUE"-----------------------------------------------------------------------------------------\n" RESET);
    RingkasanBulanan r = getRingkasanBulanan(analisis.bulan, analisis.tahun, analisis.batasHarian, analisis.jumlahHariBulan, IDUser ,NULL, 0);
    printf(BOLD BLUE"-----------------------------------------------------------------------------------------\n" RESET);

    if (r.adaData){
        unsigned int statusFlag = (r.totalBulanan > analisis.batasHarian * analisis.jumlahHariBulan) << 1 | (r.totalBulanan <= analisis.batasHarian * analisis.jumlahHariBulan);
        printf("Total Pengeluaran Bulan Ini       : " BOLD BLUE "Rp.%.2f" RESET "\n", r.totalBulanan);
        printf("Kategori Terbesar                 : " BOLD RED "%s (%.2f)" RESET "\n", r.kategoriMax, r.maxKategoriJumlah);
        printf("Hari Terboros                     : " BOLD RED "%s (%.2f)" RESET "\n", r.tanggalMax, r.maxHariJumlah);
        printf("Minggu Terboros                   : " BOLD RED "%s (%.2f)" RESET "\n\n", r.mingguMax, r.maxMingguJumlah);
        
        printf("Analisis Bulanan:\n");
        printf("- Pemasukan Bulan %d-%d         : "BOLD"Rp.%.2f"RESET"\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
        printf("- Jumlah Hari Bulan               : "BOLD"%d Hari"RESET"\n", analisis.jumlahHariBulan);
        printf("- Rata-rata Pengeluaran Harian    : "BOLD"Rp.%.2f"RESET"\n", r.rataRataHarian);
        printf("- Hari Boros vs Hemat             : " BOLD RED "%d boros, " BOLD GREEN "%d hemat" RESET "\n", r.hariBoros, r.hariHemat);
        printf("- Hari Tanpa Pengeluaran          : "BOLD"%d Hari"RESET"\n", r.hariTanpaPengeluaran);
        printf("- Hari Dengan Transaksi Terbanyak : "BOLD"%s (%d transaksi)"RESET"\n", r.tanggalTransaksiMax, r.transaksiTerbanyak);

        double batasBulanan = analisis.batasHarian * analisis.jumlahHariBulan;
        printf("- Batas Bulanan                   : "BOLD"Rp.%.2f"RESET"\n", batasBulanan);
        printf("- Sisa Saldo Bulain %d-%d       : "BOLD GREEN"Rp.%.2f"RESET"\n", analisis.bulan, analisis.tahun, analisis.sisaSaldo);
        printf("================================%s", LINEEQ);
        printf("%s\n", (statusFlag & (1 << 1)) ? BOLD RED "PENGELUARAN BULAN INI ANDA BOROS!!" : BOLD GREEN "BAGUS, PENGELUARAN BULAN INI ANDA HEMAT" RESET "");
        printf("================================%s\n", LINEEQ);

        char simpan;
        alert(ALERT_WARNING, "Apakah ingin menyimpan laporan harian ke file? (y/n): ");
        scanf("%c", &simpan);
        if (simpan == 'y' || simpan == 'Y'){
            cetakLaporanBulanan(getTanggal(), IDUser);
        }else{
            kembaliBeranda();
        }
    }else{
        alert(ALERT_SUCCESS, "Hari ini tidak ada pengeluaran. Keuangan Anda terjaga dengan baik.");
        printf("\nTekan Enter untuk kembali...");
        kembaliBeranda();
    }
}