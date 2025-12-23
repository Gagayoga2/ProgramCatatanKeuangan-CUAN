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
void cetakLaporanHarian(const char *tanggalHariIni, int IDUser){
    AnalisisLaporan analisis = getAnalisisLaporan();
    fflush(stdin);
    char namaFile[255];
    sprintf(namaFile, "Laporan/LaporanHarian/laporanHari_%s_%s.txt", tanggalHariIni, user.namaUser);


    FILE *report = fopen(namaFile, "w");
    if (report == NULL){
        alert(ALERT_ERROR, "Tidak bisa membuat file laporan!");
        return;
    }

    cetakHeader(report, tanggalHariIni, user.namaUser);
    RingkasanHarian ringkasan = getRingkasanHarian(tanggalHariIni, IDUser, report, 1);
    // TStatus Pengeluaran Dengan Bit Manipulation
    unsigned int statusFlag = (ringkasan.total > analisis.batasHarian) << 1 | (ringkasan.total <= analisis.batasHarian);

    fprintf(report, "-----------------%s", LINEDASH);
    fprintf(report, "Total Pengeluaran Hari Ini : Rp.%.2f\n", ringkasan.total);
    fprintf(report, "Kategori Terbesar          : %s (Rp.%.2f)\n\n", ringkasan.kategoriMax, ringkasan.maxJumlah);
    fprintf(report, "Analisis:\n");
    fprintf(report, "- Pemasukan Bulan %d-%d  : Rp.%.2f\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
    fprintf(report, "- Jumlah Hari Bulan        : %d Hari\n", analisis.jumlahHariBulan);
    fprintf(report, "- Batas Harian             : Rp.%.2f\n", analisis.batasHarian);
    fprintf(report, "- Status                   : %s\n",(statusFlag & (1 << 1)) ? "PENGELUARAN HARI INI ANDA BOROS!!" : "BAGUS, PENGELUARAN HARI INI ANDA HEMAT");
    fprintf(report, "=================%s\n", LINEEQ);
    fclose(report);

    system(CLEAR_CMD);
    alert(ALERT_SUCCESS, "Laporan berhasil disimpan di folder Laporan!");
    kembaliBeranda();
}

void laporanHarian(const char *tanggalHariIni, int IDUser){
    AnalisisLaporan analisis = getAnalisisLaporan();
    resetInputScreen();

    printf(BOLD BLUE "========================== [LAPORAN HARIAN] ==============================\n");
    printf("Pengguna : %s | Tanggal : %s\n=================%s" RESET "\n", user.namaUser, tanggalHariIni, LINEEQ);
    printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);
    printf(BOLD "%-3s | %-20s | %-30s | %-12s\n", "NO", "Kategori", "Deskripsi", "Jumlah");
    printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);
    RingkasanHarian ringkasan = getRingkasanHarian(tanggalHariIni, IDUser, NULL, 0);
    printf(BOLD BLUE "-----------------%s" RESET "", LINEDASH);

    if (ringkasan.adaData){
        // TStatus Pengeluaran Dengan Bit Manipulation
        unsigned int statusFlag = (ringkasan.total > analisis.batasHarian) << 1 | (ringkasan.total <= analisis.batasHarian);
        printf("Total Pengeluaran Hari Ini : " BOLD BLUE "Rp.%.2f" RESET "\n", ringkasan.total);
        printf("Kategori Terbesar          : " BOLD BLUE "%s (Rp.%.2f)" RESET "\n\n", ringkasan.kategoriMax, ringkasan.maxJumlah);
        printf("Analisis:\n");
        printf("- Pemasukan Bulan %d-%d  : " BOLD BLUE "Rp.%.2f" RESET "\n", analisis.bulan, analisis.tahun, analisis.pemasukanBulanan);
        printf("- Sisa Saldo %d-%d       : " BOLD BLUE "Rp.%.2f" RESET "\n", analisis.bulan, analisis.tahun, analisis.sisaSaldo);
        printf("- Jumlah Hari Bulan        : " BOLD "%d Hari" RESET "\n", analisis.jumlahHariBulan);
        printf("- Batas Harian             : " BOLD RED "Rp.%.2f" RESET "\n", analisis.batasHarian);
        printf("- Status                   : %s\n",(statusFlag & (1 << 1)) ? BOLD RED "BOROS" : BOLD GREEN "HEMAT" RESET);
        printf("=================%s\n", LINEEQ);
        char simpan;
        alert(ALERT_WARNING, "Apakah ingin menyimpan laporan harian ke file? (y/n): ");
        scanf(" %c", &simpan);
        if (simpan == 'y' || simpan == 'Y'){
            cetakLaporanHarian(tanggalHariIni, IDUser);
        }else{
            kembaliBeranda();
        }
    }else{
        alert(ALERT_SUCCESS, "Hari ini tidak ada pengeluaran. Keuangan Anda terjaga dengan baik.");
        printf("\nTekan Enter untuk kembali...");
        kembaliBeranda();
    }
}