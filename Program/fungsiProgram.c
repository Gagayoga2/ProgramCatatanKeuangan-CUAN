#include "../Headers/helpers.h"

// Fungsi Halaman Utama
void setHalamanUtama(){
    halamanUtama();
    scanf("%d", &pilihan);

    switch((MenuUtama)pilihan){
    case MENU_LOGIN: halamanLogin(); break;
    case MENU_REGISTER: halamanRegister(); break;
    case MENU_TENTANG: halamanLogin(); break;
    case MENU_LEFT: keluarProgram(); break;
    default: alert(ALERT_ERROR, "Pilihan tidak valid!"); break;
    }
}

// Fungsi login
void loginUser(){
    char line[512], nama[255], pass[50];
    int id, data = 0;

    fp = cekFile(FILEUSER, "r");
    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp)) {
        if(sscanf(line, "%d|%254[^|]|%49[^\n]", &id, nama, pass) == 3){
            if(strcmp(User.namaUser, nama) == 0 && strcmp(User.password, pass) == 0){
                User.IDUser = id;
                data = 1;
                break;
            }
        }
    }fclose(fp);

    if (data){
        alert(ALERT_SUCCESS, "Login Berhasil. Selamat Datang di CUAN!");
        kembaliBeranda();
    }else{
        alert(ALERT_WARNING, "Login gagal! Periksa username dan password Anda!");
        kembaliUtama();
    }
    
}

// Fungsi Register
void registerUser(){
    int lastID = 0;
    fp = fopen(FILEUSER, "r");
    if(fp != NULL){
        char line[512];
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp)){
            lastID++;
        }fclose(fp);
    }User.IDUser = lastID + 1;

    fp = cekFile(FILEUSER, "a");
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0){
        fprintf(fp, "ID|Nama User|Password\n");
    }

    fprintf(fp, "%d|%s|%s\n", User.IDUser, User.namaUser, User.password);
    fclose(fp);

    alert(ALERT_SUCCESS, "Registrasi berhasil!, Silakan Login Dahulu");
    kembaliUtama();
}

// Fungsi Halaman Beranda
void setHalamanBeranda(){
    DataRingkasan saldo = getDataRingkasan(getIDUser());
    halamanBeranda(saldo.pengeluaranHariIni, saldo.saldoHariIni, getTanggal());
    scanf("%d", &pilihan);

    switch((MenuBeranda)pilihan){
    case MENU_PEMASUKAN: halamanPemasukan(getIDUser()); break;
    case MENU_PENGELUARAN: setMenuPengeluaran(getIDUser()); break;
    case MENU_LAPORAN_HARIAN: laporanHarian(getTanggal(), getIDUser()); break;
    case MENU_LAPORAN_BULANAN: laporanBulanan(getTanggal(), getIDUser()); break;
    case MENU_LOGOUT: logoutUser(); break;
    default: alert(ALERT_ERROR, "Pilihan tidak valid!"); break;
    }
}

// Fungsi Menu Pencatatan Pemasukan
void setMenuPemasukan(int IDUser){
    int newID = getLastID(FILEPEMASUKAN, "%d|%d|%d|%lf|%d\n", 5) + 1;
    int bulan, tahun, idUser; double jumlah; char header[255];
    fp = fopen(FILEPEMASUKAN, "r"); 
    if(fp != NULL){
        fgets(header, sizeof(header), fp); 
        while(fscanf(fp, "%d|%d|%d|%lf|%d\n", &newID, &bulan, &tahun, &jumlah, &idUser) == 5){ 
            if(bulan == pemasukan.bulan && tahun == pemasukan.tahun && idUser == IDUser){ 
                fclose(fp);
                alert(ALERT_WARNING, "Pemasukan bulan ini sudah dicatat, tidak bisa menambahkan lagi!"); 
                printf("Tekan ENTER untuk kembali ke menu utama...\n"); 
                kembaliBeranda(); 
                return;
            }
        } fclose(fp); 
    }
    
    fp = cekFile(FILEPEMASUKAN, "a");
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0){
        fprintf(fp, "ID|Bulan|Tahun|Jumlah|IDUser\n");
    }

    fprintf(fp, "%d|%d|%d|%.2lf|%d\n", newID, pemasukan.bulan, pemasukan.tahun, pemasukan.jumlah, IDUser);
    fclose(fp);
    alert(ALERT_SUCCESS, "Pemasukan Berhasil di Catat!");
    printf("Tekan ENTER untuk kembali ke menu utama...\n");
    kembaliBeranda();
}

void setMenuPengeluaran(int IDUser){
    char lagi;
    do{
        halamanPengeluaran();
        int newID = getLastID(FILEPENGELUARAN, "%d|%31[^|]|%99[^|]|%255[^|]|%lf|%d", 6) + 1;

        fp = cekFile(FILEPENGELUARAN, "a");
        fseek(fp, 0, SEEK_END);
        if(ftell(fp) == 0) {
            fprintf(fp, "ID|Tanggal|Kategori|Deskripsi|Jumlah|IDUser\n");
        }
        fprintf(fp, "%d|%s|%s|%s|%.2f|%d\n", newID,pengeluaran->tanggal, pengeluaran->kategori, pengeluaran->deskripsi, pengeluaran->jumlah, IDUser);
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