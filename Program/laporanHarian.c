#include "../Headers/helpers.h"

// Fungsi Untuk Cetak Laporan Harian
void cetakHeader(FILE *out, const char *tanggalHariIni, const char *namaUser){
    fprintf(out, "========================== [LAPORAN HARIAN] ==============================\n");
    fprintf(out, "Pengguna : %s | Tanggal : %s\n", namaUser, tanggalHariIni);
    fprintf(out, "==========================================================================\n\n");
    fprintf(out, "--------------------------------------------------------------------------\n");
    fprintf(out, "%-3s | %-20s | %-30s | %-12s\n", "NO", "Kategori", "Deskripsi", "Jumlah");
    fprintf(out, "--------------------------------------------------------------------------\n");
}
void cetakLaporanHarian(const char *tanggalHariIni, int IDUser, char namaUser[50]){
    AnalisisLaporan analisis = getAnalisisLaporan(IDUser);
    fflush(stdin);
    char namaFile[255];
    sprintf(namaFile, "Laporan/LaporanHarian/laporanHari_%s_%s.txt", tanggalHariIni, namaUser);

    FILE *report = cekFile(namaFile, "w");
    cetakHeader(report, tanggalHariIni, namaUser);
    RingkasanHarian ringkasan = getRingkasanHarian(tanggalHariIni, IDUser, report, 1);
    // TStatus Pengeluaran Dengan Bit Manipulation
    unsigned int statusFlag = (ringkasan.total > analisis.batasHarian) << 1 | (ringkasan.total <= analisis.batasHarian);

    fprintf(report, "-----------------%s", LINEDASH);
    fprintf(report, "Total Pengeluaran Hari Ini : Rp.%.2f\n", ringkasan.total);
    fprintf(report, "Jumlah Transaksi Hari Ini  : %d Transaksi\n", ringkasan.jumlahTransaksi);
    fprintf(report, "Kategori Terbesar          : %s (Rp.%.2f, %.2f%%)\n\n", ringkasan.kategoriMax, ringkasan.maxJumlah, ringkasan.persenKategoriMax);
    fprintf(report, "Analisis:\n");
    fprintf(report, "- Pemasukan Bulan %d-%d  : Rp.%.2f\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
    fprintf(report, "- Jumlah Hari Bulan        : %d Hari\n", analisis.jumlahHariBulan);
    fprintf(report, "- Batas Harian             : Rp.%.2f\n", analisis.batasHarian);
    fprintf(report, "- Status                   : %s\n", (statusFlag & (1 << 1)) ? "PENGELUARAN HARI INI ANDA BOROS!!" : "BAGUS, PENGELUARAN HARI INI ANDA DIBAWAH BATAS HARIAN");
    fprintf(report, "=================%s\n", LINEEQ);
    fclose(report);

    system(CLEAR_CMD);
    alert(ALERT_SUCCESS, "Laporan berhasil disimpan di folder Laporan!");
    kembaliBeranda();
}

void laporanHarian(const char *tanggalHariIni, int IDUser){
    AnalisisLaporan analisis = getAnalisisLaporan(IDUser);
    resetInputScreen();

    printf(BOLD BLUE "========================== [LAPORAN HARIAN] ==============================\n");
    printf("Pengguna : %s | Tanggal : %s\n=================%s" RESET "\n", User.namaUser, tanggalHariIni, LINEEQ);
    printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);
    printf(BOLD "%-3s | %-20s | %-30s | %-12s\n", "NO", "Kategori", "Deskripsi", "Jumlah");
    printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);
    RingkasanHarian ringkasan = getRingkasanHarian(tanggalHariIni, IDUser, NULL, 0);

    if(ringkasan.adaData){
        // TStatus Pengeluaran Dengan Bit Manipulation
        unsigned int statusFlag = (ringkasan.total > analisis.batasHarian) << 1 | (ringkasan.total <= analisis.batasHarian);
        printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);
        printf("Total Pengeluaran Hari Ini : " BOLD BLUE "Rp.%.2f" RESET "\n", ringkasan.total);
        printf("Jumlah Transaksi Hari Ini  : " BOLD BLUE "%d Transaksi" RESET "\n", ringkasan.jumlahTransaksi);
        printf("Kategori Terbesar          : " BOLD BLUE "%s (Rp.%.2f, %.2f%%)" RESET "\n", ringkasan.kategoriMax, ringkasan.maxJumlah, ringkasan.persenKategoriMax);
        printf("\nAnalisis:\n");
        printf("- Pemasukan Bulan %d-%d  : " BOLD BLUE "Rp.%.2f" RESET "\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
        printf("- Sisa Saldo %d-%d       : " BOLD BLUE "Rp.%.2f" RESET "\n", analisis.bulan, analisis.tahun, analisis.sisaSaldo);
        printf("- Jumlah Hari Bulan        : " BOLD "%d Hari" RESET "\n", analisis.jumlahHariBulan);
        printf("- Batas Harian             : " BOLD RED "Rp.%.2f" RESET "\n", analisis.batasHarian);
        printf("- Status                   : %s\n", (statusFlag & (1 << 1)) ? BOLD RED "PENGELUARAN HARI INI ANDA BOROS!!" : BOLD GREEN "BAGUS, PENGELUARAN HARI INI DIBAWAH BATAS HARIAN" RESET);
        printf("=================%s\n", LINEEQ);
        char simpan;
        alert(ALERT_WARNING, "Apakah ingin menyimpan laporan harian ke file? (y/n): ");
        scanf(" %c", &simpan);
        if(simpan == 'y' || simpan == 'Y'){
            cetakLaporanHarian(tanggalHariIni, IDUser, User.namaUser);
        }else{
            kembaliBeranda();
        }
    }else{
        alert(ALERT_SUCCESS, "Hari ini tidak ada pengeluaran. Keuangan Anda terjaga dengan baik.");
        printf("\nTekan Enter untuk kembali...");
        kembaliBeranda();
    }
}