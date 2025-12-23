# 📄 Dokumentasi Program CUAN

CUAN adalah program pencatatan keuangan pribadi yang membantu pengguna mencatat pemasukan bulanan dan pengeluaran harian, serta menghasilkan laporan harian dan bulanan lengkap dengan analisis sederhana.

---

## 📁 Struktur Folder Program

```text
/SRC
│
├── Build
│   └── CUAN.exe                     (File executable utama)
│
├── DataProgram
│   ├── fileDataUser.txt             (Data user, dibuat saat registrasi)
│   ├── fileDataPemasukan.txt        (Data pemasukan bulanan)
│   └── fileDataPengeluaran.txt      (Data pengeluaran harian)
│
├── Dokumentasi
│   ├── dokumentasi.md               (Dokumentasi teknis program)
│   └── readme.md                    (Deskripsi umum program CUAN)
│
├── FungsiPendukung
│   ├── helpers.c                    (Fungsi bantu umum)
│   └── helperLaporan.c              (Fungsi bantu untuk laporan)
│
├── Headers
│   ├── constanta.h                 (Konstanta global)
│   ├── helpers.h                   (Header fungsi bantu)
│   └── models.h                    (Struktur data dan model)
│
├── Laporan
│   ├── LaporanHarian
│   │   └── laporanHari_<tanggal>_<user>.txt           (File laporan harian yang di simpan)
│   └── LaporanBulanan
│       └── laporanBulanan_<bulan>-<tahun>_<user>.txt  (File laporan Bulanan yang di simpan)
│
├── Program
│   ├── fungsiProgram.c             (Logika utama login, register, input data)
│   ├── laporanHarian.c             (Fungsi laporan harian)
│   └── laporanBulanan.c            (Fungsi laporan bulanan)
│
├── Tampilan
│   ├── display.c                   (Tampilan menu dan UI)
│   └── main.c                      (Entry point program)
│
└── .vscode
    └── tasks.json                  (Konfigurasi build otomatis)
```
---

## 🚀 Cara Instalasi & Menjalankan Program

Anda memiliki dua opsi untuk menjalankan program CUAN:

### ✅ Opsi 1: Menjalankan Langsung (Executable)
- Pastikan file `CUAN.exe` berada di dalam folder `Build`.
- Pastikan folder `DataProgram` tersedia dan berada dalam satu struktur proyek.
- Klik dua kali file `CUAN.exe` untuk menjalankan program.

### 🛠️ Opsi 2: Build & Run Manual (Via Terminal)
Jika Anda ingin melakukan build ulang dari source code:

1. Pastikan file `tasks.json` berada di dalam folder `.vscode`.
2. Buka terminal (CMD/PowerShell) di dalam folder proyek utama (sejajar dengan `main.c`).
3. Jalankan perintah berikut:

```bash
cls && gcc main.c FungsiPendukung/helpers.c FungsiPendukung/helperLaporan.c Program/fungsiProgram.c Program/laporanHarian.c Program/laporanBulanan.c Tampilan/display.c -o Build\\CUAN.exe && Build\\CUAN.exe
```

### 🛠️ Opsi 3: Build & Run Pakai Shortcut CTRL+SHIFT+B
Jika Anda ingin melakukan build ulang dari source code:

1. Pastikan folder `.vscode` terdapat di proyek Anda.
2. Cari file `tasks.json`, lalu pindahkan ke folder `.vscode`.
3. Buka file `main.c`, lalu tekan tombol `CTRL+SHIFT+B` lalu tinggal enter.
4. Program siap di jalankan.

---