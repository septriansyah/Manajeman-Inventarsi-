#include <stdio.h>
#include <string.h>
#include <stdlib.h>//library untuk menghapus screen yang sudah diguanakn
#include <unistd.h>//library untuk sleep() atau jeda
#include <time.h>//library untuk mempermudah mebrikan keterangan waktu
#include "Kelompok 15_Menjemen Inventaris Keamkom2.h"
#include "Kelompok 15_Menjemen Inventaris Keamkom.h"
// Struktur data aset
typedef struct {
    char Pemberi[50];
    char kode[10];
    char nama[50];
    char kategori[30];
    char lokasi[50];
    char kondisi[20];
    char tanggalmemberi[20];
    int jumlah;
} Aset;
// Struktur data penguna akses
typedef struct {
    char nim[15];
    char nama[50];
    char jabatan[50];
} Anggota;
typedef struct {
    char kode[10];
    char nama[50];
    char kategori[30];
    int jumlah;
}Peminjaman;
// Deklarasi global
Aset inventaris[100];
Peminjaman pinjam [50];
int totalpinjam = 0;
int totalAset = 0;
Anggota pengguna;
// Fungsi prototipe
void tampilkanData();
void tambahData();
void editData();
void hapusData();
void pencarianData();
void pencarianSekuen();
void pencarianBinary();
void bubbleSort(int n, Aset inventaris[]);
void quickSort(int low, int high);
int partition(int low, int high);
void transaksiPenambahanItem();
void transaksiPenguranganItem();
void cetakHasilAkhir();
void peminjaman2 ();
void transaksiPeminjamanItem();
void Tampilbarangpinjam();
int Menutama();
void peminjaman ();
void pengembalian();
int Validasi();
// Fungsi untuk "membersihkan layar"
void clearScreen() {
    printf("\033[H\033[J");
}
int isValidJabatan(char jabatan[]) {
    //array string yang berisi nama divis yang dianggap Valid
    const char *jabatanValid[] = {//kata kunci const mengunci bahwa isi dari string di bawah ini tidak dapat di ubah melalui pointer tersebut
        "Non-Divisi", "DPMB", "DPO", "DIVROH", "EKOBIS", 
        "DIVDIKLAT", "DIVKOMTEKINFO", "DIVADSOSPOL"
    };
//perulangan untuk mengecek apakah jabatan yang di input valid
    for (int i = 0; i < 8; i++) {
        //bandingkan dengan yang di input dengan yang ada di array
        if (strcmp(jabatan, jabatanValid[i]) == 0) {
            return 1; // jika di temukan kecocokan maka, Jabatan valid
        }
    }
    return 0; // jika tidak ditemukan kecocokan maka, Jabatan tidak valid
}
// Fungsi utama
int main() {
    int pilihan2; // Variabel untuk pilihan menu

    strcpy(inventaris[0].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[0].tanggalmemberi, "06/22/2024");
    strcpy(inventaris[0].kode, "A001");
    strcpy(inventaris[0].nama, "Epson L1400");
    strcpy(inventaris[0].kategori, "Elektronik");
    strcpy(inventaris[0].lokasi, "Sekretariat Kemakom");
    strcpy(inventaris[0].kondisi, "Perlu diperbaiki");
    inventaris[0].jumlah = 2;
    // Data ke-1
    strcpy(inventaris[1].Pemberi, "Kaprodi PILKOM");
    strcpy(inventaris[1].tanggalmemberi, "07/26/2024");
    strcpy(inventaris[1].kode, "B002");
    strcpy(inventaris[1].nama, "Proyektor Epson");
    strcpy(inventaris[1].kategori, "Elektronik");
    strcpy(inventaris[1].lokasi, "Ruang Auditorium");
    strcpy(inventaris[1].kondisi, "Cukup");
    inventaris[1].jumlah = 2;
    // Data ke-2
    strcpy(inventaris[2].Pemberi, "Divisi EKOBIS");
    strcpy(inventaris[2].tanggalmemberi, "07/26/2024");
    strcpy(inventaris[2].kode, "A019");
    strcpy(inventaris[2].nama, "Lemari");
    strcpy(inventaris[2].kategori, "Furniture");
    strcpy(inventaris[2].lokasi, "Sekretariat Kemakom");
    strcpy(inventaris[2].kondisi, "Baik");
    inventaris[2].jumlah = 10;
    // Data ke-3
    strcpy(inventaris[3].Pemberi, "Sekretaris UMUM");
    strcpy(inventaris[3].tanggalmemberi, "06/23/2024");
    strcpy(inventaris[3].kode, "C102");
    strcpy(inventaris[3].nama, "Kertas A4");
    strcpy(inventaris[3].kategori, "ATK");
    strcpy(inventaris[3].lokasi, "Lab Komputer");
    strcpy(inventaris[3].kondisi, "Baik");
    inventaris[3].jumlah = 500;
    // Data ke-4
    strcpy(inventaris[4].Pemberi, "Sekretaris UMUM");
    strcpy(inventaris[4].tanggalmemberi, "06/22/2024");
    strcpy(inventaris[4].kode, "A102");
    strcpy(inventaris[4].nama, "Kertas A4");
    strcpy(inventaris[4].kategori, "ATK");
    strcpy(inventaris[4].lokasi, "Sekretariat Kemakom");
    strcpy(inventaris[4].kondisi, "Baik");
    inventaris[4].jumlah = 234;
    // Data ke-5
    strcpy(inventaris[5].Pemberi, "Divisi EKOBIS");
    strcpy(inventaris[5].tanggalmemberi, "08/10/2024");
    strcpy(inventaris[5].kode, "A201");
    strcpy(inventaris[5].nama, "Meja Kerja");
    strcpy(inventaris[5].kategori, "Furniture");
    strcpy(inventaris[5].lokasi, "Sekretariat Kemakom");
    strcpy(inventaris[5].kondisi, "Baik");
    inventaris[5].jumlah = 5;
    // Data ke-6
    strcpy(inventaris[6].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[6].tanggalmemberi, "09/15/2024");
    strcpy(inventaris[6].kode, "C305");
    strcpy(inventaris[6].nama, "Laptop Dell");
    strcpy(inventaris[6].kategori, "Elektronik");
    strcpy(inventaris[6].lokasi, "Lab Komputer");
    strcpy(inventaris[6].kondisi, "Cukup");
    inventaris[6].jumlah = 3;
    // Data ke-7
    strcpy(inventaris[7].Pemberi, "Kaprodi PILKOM");
    strcpy(inventaris[7].tanggalmemberi, "11/12/2024");
    strcpy(inventaris[7].kode, "B402");
    strcpy(inventaris[7].nama, "Proyektor Epson");
    strcpy(inventaris[7].kategori, "Elektronik");
    strcpy(inventaris[7].lokasi, "Ruang Auditorium");
    strcpy(inventaris[7].kondisi, "Baik");
    inventaris[7].jumlah = 1;

    // Data ke-8
    strcpy(inventaris[8].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[8].tanggalmemberi, "12/12/2024");
    strcpy(inventaris[8].kode, "A100");
    strcpy(inventaris[8].nama, "Meja Panjang");
    strcpy(inventaris[8].kategori, "Furniture");
    strcpy(inventaris[8].lokasi, "Sekretariat BEM");
    strcpy(inventaris[8].kondisi, "Baik");
    inventaris[8].jumlah = 5;

    // Data ke-9
    strcpy(inventaris[9].Pemberi, "Dekan FPMIPA");
    strcpy(inventaris[9].tanggalmemberi, "11/30/2024");
    strcpy(inventaris[9].kode, "C786");
    strcpy(inventaris[9].nama, "Komputer Gaming");
    strcpy(inventaris[9].kategori, "Elektronik");
    strcpy(inventaris[9].lokasi, "Lab Komputer");
    strcpy(inventaris[9].kondisi, "Baru");
    inventaris[9].jumlah = 10;

    // Data ke-10
    strcpy(inventaris[10].Pemberi, "DPO KEMAKOM");
    strcpy(inventaris[10].tanggalmemberi, "11/25/2024");
    strcpy(inventaris[10].kode, "B403");
    strcpy(inventaris[10].nama, "Speaker Portabel");
    strcpy(inventaris[10].kategori, "Elektronik");
    strcpy(inventaris[10].lokasi, "Ruang Auditorium");
    strcpy(inventaris[10].kondisi, "Baik");
    inventaris[10].jumlah = 4;

    // Data ke-11
    strcpy(inventaris[11].Pemberi, "DPMB KEMAKOM");
    strcpy(inventaris[11].tanggalmemberi, "11/24/2024");
    strcpy(inventaris[11].kode, "A870");
    strcpy(inventaris[11].nama, "Benner Acara");
    strcpy(inventaris[11].kategori, "Barang Lain");
    strcpy(inventaris[11].lokasi, "Sekretariat KEMAKOM");
    strcpy(inventaris[11].kondisi, "Baik");
    inventaris[11].jumlah = 3;

    // Data ke-12
    strcpy(inventaris[12].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[12].tanggalmemberi, "06/12/2024");
    strcpy(inventaris[12].kode, "A126");
    strcpy(inventaris[12].nama, "Proyektor Epson");
    strcpy(inventaris[12].kategori, "Elektronik");
    strcpy(inventaris[12].lokasi, "Sekretariat KEMAKOM");
    strcpy(inventaris[12].kondisi, "Rusak");
    inventaris[12].jumlah = 2;

    // Data ke-13
    strcpy(inventaris[13].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[13].tanggalmemberi, "11/14/2024");
    strcpy(inventaris[13].kode, "B128");
    strcpy(inventaris[13].nama, "Stand MIC");
    strcpy(inventaris[13].kategori, "Barang Lain");
    strcpy(inventaris[13].lokasi, "Ruang Auditorium");
    strcpy(inventaris[13].kondisi, "Baik");
    inventaris[13].jumlah = 3;

    // Data ke-14
    strcpy(inventaris[14].Pemberi, "BEM KEMAKOM");
    strcpy(inventaris[14].tanggalmemberi, "09/03/2024");
    strcpy(inventaris[14].kode, "C402");
    strcpy(inventaris[14].nama, "Router");
    strcpy(inventaris[14].kategori, "Elektronik");
    strcpy(inventaris[14].lokasi, "Lab Komputer");
    strcpy(inventaris[14].kondisi, "Rusak");
    inventaris[14].jumlah = 3;

    // Data ke-15
    strcpy(inventaris[15].Pemberi, "DEKAN FPMIPA");
    strcpy(inventaris[15].tanggalmemberi, "05/12/2024");
    strcpy(inventaris[15].kode, "B402");
    strcpy(inventaris[15].nama, "Mimbar Acara");
    strcpy(inventaris[15].kategori, "Furniture");
    strcpy(inventaris[15].lokasi, "Ruang Auditorium");
    strcpy(inventaris[15].kondisi, "Perlu diperbaiki");
    inventaris[15].jumlah = 5;

    // Update totalAset
    totalAset = 16;

    // Inisialisasi data peminjaman pertama
    strcpy(pinjam[0].kode, "A102");
    strcpy(pinjam[0].nama, "Kertas A4");
    strcpy(pinjam[0].kategori, "ATK");
    pinjam[0].jumlah = 2;

    // Inisialisasi data peminjaman kedua
    strcpy(pinjam[1].kode, "B128");
    strcpy(pinjam[1].nama, "Stand MIC");
    strcpy(pinjam[1].kategori, "Barang Lain");
    pinjam[1].jumlah = 1;

    // Inisialisasi data peminjaman ketiga
    strcpy(pinjam[2].kode, "B402");
    strcpy(pinjam[2].nama, "Mimbar Acara");
    strcpy(pinjam[2].kategori, "Furniture");
    pinjam[2].jumlah = 2;

    // Inisialisasi data peminjaman keempat
    strcpy(pinjam[3].kode, "A870");
    strcpy(pinjam[3].nama, "Benner Acara");
    strcpy(pinjam[3].kategori, "Barang Lain");
    pinjam[3].jumlah = 1;

    // Inisialisasi data peminjaman kelima
    strcpy(pinjam[4].kode, "A201");
    strcpy(pinjam[4].nama, "Meja Panjang");
    strcpy(pinjam[4].kategori, "Furniture");
    pinjam[4].jumlah = 1;

    // Total peminjaman adalah 1
    totalpinjam = 5;

    // Tampilan menu awal untuk pengguna
    printf("\n=====================================================\n");
    printf("=== Selamat Datang di Sistem Manajemen Inventaris ===\n");
    printf("=====================================================\n");
    printf("Apakah Yang Ingin Anda Lakukan?\n");
    printf("[1] Pengelolaan Inventaris (Anggota BEM KEMAKON)\n");
    printf("[2] Peminjaman Inventaris\n");
    printf("====================================================\n");
    printf("Pilih: ");
    scanf("%d", &pilihan2); // Mengambil input pilihan menu utama

    // Menentukan menu berdasarkan pilihan pengguna
    switch (pilihan2)
    {
    case 1:
        Menutama(); // Fungsi untuk pengelolaan inventaris oleh BEM
        break;
    case 2:
        peminjaman2(); // Fungsi untuk peminjaman inventaris
        break;
    default:
        break; // Tidak ada aksi jika pilihan tidak valid
    }
}

void peminjaman2() {
    int pilih3; // variabel untuk menyimpan pilihan menu

    do {
    printf("\n══════════════════════════════════════════════════════════════════════\n");
    printf("🌟 ===== Sistem Peminjaman Inventaris KEMAKOM ===== 🌟\n");
    printf("══════════════════════════════════════════════════════════════════════\n");
    printf("📋 Pilihan Menu:\n");
    printf("──────────────────────────────────────────────────────────────────────\n");
    printf("[1] 📖 Tampil Data Inventaris\n");
    printf("[2] 📖 Tampil Data yang Dipinjam\n");
    printf("[3] 📦 Peminjaman Barang\n");
    printf("[4] 🔄 Pengembalian Barang\n");
    printf("[5] 🔙 Ke Menu Utama (Sebagai Anggota BEM)\n");
    printf("[0] ❌ Keluar Dari Sistem Ini\n");
    printf("──────────────────────────────────────────────────────────────────────\n");
    printf("🔍 Pilih Menu: ");
        scanf("%d", &pilih3); // mengambil input pilihan menu dari pengguna

        switch (pilih3) {
            case 1:
                tampilkanData(); // menampilkan data inventaris
                continue; // melanjutkan ke awal loop untuk pilihan lainnya
            case 2:
                Tampilbarangpinjam(); // menampilkan data barang yang dipinjam
                continue; // melanjutkan ke awal loop untuk pilihan lainnya
            case 3:
                tampilkanData(); // menampilkan data inventaris yang tersedia
                transaksiPeminjamanItem(); // memproses transaksi peminjaman barang
                continue; // melanjutkan ke awal loop untuk pilihan lainnya
            case 4:
                pengembalian(); // proses pengembalian barang yang dipinjam
                continue; // melanjutkan ke awal loop untuk pilihan lainnya
            case 5:
                sleep(1);
                Menutama(); // kembali ke menu utama sebagai anggota BEM
                continue; // melanjutkan ke awal loop untuk pilihan lainnya
            case 0:
                anggotaKelompok();
                break; // keluar dari loop dan menghentikan program
            default:
                break; // jika pilihan tidak valid, keluar dari switch-case
        }
        
    } while (pilih3 != 0); // loop berlanjut sampai pengguna memilih untuk keluar dari sistem
}

// Fungsi untuk menampilkan data peminjaman barang
void Tampilbarangpinjam() {
    if (totalpinjam == 0) { // jika tidak ada barang yang dipinjam
        printf("\n** Tidak ada data inventaris yang dipinjam. **\n");
    } else { // jika ada barang yang dipinjam
        printf("\n=====================================================================\n");
        printf("| No |    Kode    |        Nama        |   Kategori   |   Jumlah   |\n");
        printf("=====================================================================\n");

        // Menampilkan data barang yang dipinjam
        for (int i = 0; i < totalpinjam; i++) {
            printf("| %-2d | %-10s | %-17s  | %-12s | %-9d  |\n",
                   i + 1,
                   pinjam[i].kode,
                   pinjam[i].nama,
                   pinjam[i].kategori,
                   pinjam[i].jumlah);
        }
        printf("=====================================================================\n");
    }
}

// Fungsi untuk menampilkan data inventaris yang tersedia
void tampilkanData() {
    // Cek apakah jumlah inventaris itu 0
    if (totalAset == 0) { // jika tidak ada inventaris
        // Menampilkan pesan bahwa tidak ada inventaris yang tersedia
        printf("\n** Tidak ada data inventaris yang tersedia. **\n");
    } else { // jika ada inventaris
        // Menampilkan header tabel data inventaris
        printf("\n==============================================================================================================================================================\n");
        printf("| No |         Nama Pemberi        | Tanggal Memberi    | Kode  |        Nama        |    Kategori    |         Lokasi         |       Kondisi      | Jumlah |\n");
        printf("==============================================================================================================================================================\n");

        // Menampilkan data inventaris dari setiap item yang ada
        for (int i = 0; i < totalAset; i++) {
            // Menampilkan data aset dengan format tabel yang rapi
            printf("| %-2d | %-27s | %-18s | %-5s | %-18s | %-14s | %-22s | %-18s | %-6d |\n",//
                   i + 1, // nomor urut
                   inventaris[i].Pemberi, // nama pemberi
                   inventaris[i].tanggalmemberi, // tanggal pemberian
                   inventaris[i].kode, // kode aset
                   inventaris[i].nama, // nama aset
                   inventaris[i].kategori, // kategori aset
                   inventaris[i].lokasi, // lokasi aset
                   inventaris[i].kondisi, // kondisi aset
                   inventaris[i].jumlah); // jumlah aset
        }
        // Menutup tabel
        printf("==============================================================================================================================================================\n");
    }
}
// Fungsi Menambah Inventaris
void tambahData() {
    int pilihanLokasi; // Variabel untuk menyimpan pilihan lokasi penyimpanan aset
    char kodeawal;    // Variabel untuk menyimpan awalan kode aset berdasarkan lokasi

    printf("\n==================================================\n");
    printf("=============== Tambah Data Aset ================\n");
    printf("=================================================\n");

    // Memasukkan informasi pemberi inventaris
    printf("Masukkan Nama Pemberi Inventaris: ");
    scanf(" %[^\n]s", inventaris[totalAset].Pemberi); // Mengambil nama pemberi

    // Mengisi tanggal pemberian inventaris secara otomatis
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(inventaris[totalAset].tanggalmemberi, sizeof(inventaris[totalAset].tanggalmemberi), "%m/%d/%Y", local);

    // Menampilkan tanggal otomatis
    printf("Tanggal Pemberian Inventaris: %s\n", inventaris[totalAset].tanggalmemberi);

    // Validasi lokasi penyimpanan
    do {
        // Menampilkan pilihan lokasi penyimpanan
        printf("\nPilih Lokasi Penyimpanan:\n");
        printf("[1] Sekretariat Kemakom\n");
        printf("[2] Ruang Auditorium\n");
        printf("[3] Lab Komputer\n");
        printf("Pilih: ");
        scanf("%d", &pilihanLokasi); // Mengambil input lokasi

        // Menentukan lokasi dan prefix kode berdasarkan pilihan
        switch (pilihanLokasi) {
            case 1:
                strcpy(inventaris[totalAset].lokasi, "Sekretariat Kemakom"); // Set lokasi
                kodeawal = 'A'; // Set prefix kode untuk lokasi 1
                break;
            case 2:
                strcpy(inventaris[totalAset].lokasi, "Ruang Auditorium"); // Set lokasi
                kodeawal = 'B'; // Set prefix kode untuk lokasi 2
                break;
            case 3:
                strcpy(inventaris[totalAset].lokasi, "Lab Komputer"); // Set lokasi
                kodeawal = 'C'; // Set prefix kode untuk lokasi 3
                break;
            default:
                printf("** Pilihan tidak valid. Harap pilih lokasi yang tersedia. **\n"); // Jika input tidak valid
        }
    } while (pilihanLokasi < 1 || pilihanLokasi > 3); // Looping jika input lokasi tidak valid

    // Memasukkan kode aset tanpa huruf di depan
    printf("Masukkan Kode Aset (tanpa prefix): ");
    scanf("%s", inventaris[totalAset].kode); // Mengambil kode aset

    // Menambahkan kode awal pada kode aset berdasarkan lokasi yang dipilih
    char finalKode[50];
    snprintf(finalKode, sizeof(finalKode), "%c%s", kodeawal, inventaris[totalAset].kode); // Membuat kode akhir
    strcpy(inventaris[totalAset].kode, finalKode); // Menyimpan kode lengkap dengan prefix

    // Memasukkan informasi tentang aset
    printf("Masukkan Nama Aset: ");
    scanf(" %[^\n]s", inventaris[totalAset].nama); // Mengambil nama aset
    printf("Masukkan Kategori Aset: ");
    scanf(" %[^\n]s", inventaris[totalAset].kategori); // Mengambil kategori aset
    printf("Masukkan Kondisi Aset: ");
    scanf(" %[^\n]s", inventaris[totalAset].kondisi); // Mengambil kondisi aset
    printf("Masukkan Jumlah Aset: ");
    scanf("%d", &inventaris[totalAset].jumlah); // Mengambil jumlah aset

    // Menambah total aset dan memberikan konfirmasi
    totalAset++; // Menambah jumlah total aset
    printf("\n** Data berhasil ditambahkan! **\n"); // Konfirmasi bahwa data berhasil ditambahkan
}

// Fungsi Menghapus Inventaris
void hapusData() {
    char kode[10]; // variabel untuk menyimpan kode inventaris yang ingin dihapus
    int ketemu = 0; // variabel untuk menandakan apakah data ditemukan

    printf("\n=================================================\n");
    printf("=== Hapus Data Aset ===\n");
    printf("=================================================\n");
    printf("Masukkan Kode inventaris yang ingin dihapus: ");
    scanf("%s", kode); // meminta input kode inventaris yang ingin dihapus

    // Mencari inventaris berdasarkan kode yang dimasukkan
    for (int i = 0; i < totalAset; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) { // jika kode ditemukan
            ketemu = 1; // set ketemu menjadi 1
            // Proses penghapusan, menggeser semua data setelahnya ke kiri
            for (int j = i; j < totalAset - 1; j++) {
                inventaris[j] = inventaris[j + 1]; // memindahkan data berikutnya ke posisi sebelumnya
            }
            totalAset--; // mengurangi jumlah total aset setelah penghapusan
            printf("\n** Data berhasil dihapus! **\n"); // konfirmasi penghapusan berhasil
            break; // keluar dari loop karena data sudah dihapus
        }
    }

    // Jika kode tidak ditemukan
    if (!ketemu) {
        printf("\n** Data dengan kode %s tidak ditemukan. **\n", kode); // pesan jika data tidak ada
    }
}

// Fungsi Subpilihan untuk Mencari data yang telah ada
void pencarianData() {
    int subPilihan; // variabel untuk menyimpan pilihan dari pengguna

    printf("\n==================================================================\n");
    printf("===================== Pencarian Data Aset ========================\n");
    printf("==================================================================\n");
    printf("[1] Menggunakan Metode Sekuensial Berdasarkan Nama \n"); // opsi pencarian menggunakan metode sekuensial
    printf("[2] Menggunakan Metode Binary dan Histroy Pertanggal Barang Masuk\n"); // opsi pencarian menggunakan metode binary dan berdasarkan tanggal barang masuk
    printf("[0] Kembali ke Menu Utama\n"); // opsi untuk kembali ke menu utama
    printf("==================================================================\n");
    printf("Pilih metode pencarian: ");
    scanf("%d", &subPilihan); // mengambil input dari pengguna

    // Menggunakan switch-case untuk memproses pilihan
    switch (subPilihan) {
        case 1:
            tampilkanData();
            pencarianSekuen(); // memanggil fungsi pencarian sekuensial
            break;
        case 2:
            tampilkanData();
            pencarianBinary(); // memanggil fungsi pencarian binary
            break;
        case 0:
            printf("\nKembali ke menu utama.\n"); // menampilkan pesan jika memilih kembali ke menu utama
            break;
        default:
            printf("\nPilihan tidak valid, coba lagi.\n"); // menampilkan pesan jika pilihan tidak valid
    }
}

// fungsi pencarian secara sekuensial
void pencarianSekuen() {
    char nama[50]; // variabel untuk menyimpan input nama inventaris
    int i = 0; // indeks untuk iterasi dalam array inventaris
    int usaha = 0; // variabel untuk menghitung jumlah usaha pencarian

    printf("\n=================================================\n");
    printf("========= Pencarian Data (Sekuensial) ===========\n");
    printf("=================================================\n");
    printf("Masukkan Nama Inventaris yang dicari: ");
    scanf(" %49[^\n]", nama); // Menggunakan format ini untuk menangani spasi dalam input

    // Pencarian sekuensial
    while (i < totalAset) { // looping untuk mencari nama yang sesuai dalam array inventaris
        usaha++; // meningkatkan jumlah usaha setiap iterasi
        if (strcmp(inventaris[i].nama, nama) == 0) { // mengecek apakah nama yang dicari cocok
            // Jika ditemukan
            printf("\n** Data ditemukan. **\n");
            printf("Nama Pemberi    : %s\n", inventaris[i].Pemberi); // menampilkan data pemberi
            printf("Tanggal Memberi : %s\n", inventaris[i].tanggalmemberi); // menampilkan tanggal memberi
            printf("Kode            : %s\n", inventaris[i].kode); // menampilkan kode aset
            printf("Nama            : %s\n", inventaris[i].nama); // menampilkan nama inventaris
            printf("Kategori        : %s\n", inventaris[i].kategori); // menampilkan kategori inventaris
            printf("Lokasi          : %s\n", inventaris[i].lokasi); // menampilkan lokasi aset
            printf("Kondisi         : %s\n", inventaris[i].kondisi); // menampilkan kondisi aset
            printf("Jumlah          : %d\n", inventaris[i].jumlah); // menampilkan jumlah aset
            printf("Usaha pencarian: %d kali\n", usaha); // menampilkan jumlah usaha pencarian
            return; // keluar dari fungsi setelah data ditemukan
        }
        i++; // melanjutkan ke indeks berikutnya
    }

    // Jika data tidak ditemukan, tambahkan penanganan
    printf("\n** Data tidak ditemukan. **\n");
}
// fungsi pencarian data dengan metode binary search
void pencarianBinary() {
    char tanggal[50]; // variabel untuk menyimpan input tanggal
    int kiri = 0, kanan = totalAset - 1, tengah; // inisialisasi batas pencarian
    int usaha = 0; // variabel untuk menghitung jumlah usaha pencarian
    int ditemukan = 0; // flag untuk mengecek apakah data ditemukan
    int jumlahData = 0; // variabel untuk menghitung jumlah data yang ditemukan

    // menampilkan menu pencarian
    printf("\n=================================================\n");
    printf("============ Pencarian Data (Binary) ============\n");
    printf("=================================================\n");
    printf("Masukkan Tanggal Pemberian Inventaris yang ingin dicari: ");
    scanf(" %49[^\n]", tanggal); // menerima input tanggal

    // proses binary search
    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2; // menentukan indeks tengah
        usaha++; // mencatat usaha pencarian

        int cmp = strcmp(inventaris[tengah].tanggalmemberi, tanggal); // membandingkan tanggal

        if (cmp == 0) { // jika tanggal ditemukan
            ditemukan = 1; // set flag ditemukan

            // mencari elemen dengan tanggal yang sama ke kiri dan kanan
            int i = tengah;

            // mencari elemen ke kiri
            while (i >= 0 && strcmp(inventaris[i].tanggalmemberi, tanggal) == 0) {
                jumlahData++; // menghitung data yang ditemukan
                i--;
            }

            // mencari elemen ke kanan
            i = tengah + 1;
            while (i < totalAset && strcmp(inventaris[i].tanggalmemberi, tanggal) == 0) {
                jumlahData++; // menghitung data yang ditemukan
                i++;
            }

            // menampilkan hasil pencarian
            printf("===========================================================");
            printf("\n History Pencarian Pada Tanggal %s Adalah \n", tanggal);
            printf(" Jumlah data ditemukan: %d \n", jumlahData);
            printf("===========================================================");

            // menampilkan semua data dengan tanggal yang sama (kembali ke kiri)
            i = tengah;
            while (i >= 0 && strcmp(inventaris[i].tanggalmemberi, tanggal) == 0) {
                printf("\nData ke-%d:\n", i + 1);
                printf("Nama Pemberi    : %s\n", inventaris[i].Pemberi);
                printf("Tanggal Memberi : %s\n", inventaris[i].tanggalmemberi);
                printf("Kode            : %s\n", inventaris[i].kode);
                printf("Nama            : %s\n", inventaris[i].nama);
                printf("Kategori        : %s\n", inventaris[i].kategori);
                printf("Lokasi          : %s\n", inventaris[i].lokasi);
                printf("Kondisi         : %s\n", inventaris[i].kondisi);
                printf("Jumlah          : %d\n", inventaris[i].jumlah);
                i--;
            }

            // mencari elemen ke kanan dan menampilkannya
            i = tengah + 1;
            while (i < totalAset && strcmp(inventaris[i].tanggalmemberi, tanggal) == 0) {
                printf("\nData ke-%d:\n", i + 1);
                printf("Nama Pemberi    : %s\n", inventaris[i].Pemberi);
                printf("Tanggal Memberi : %s\n", inventaris[i].tanggalmemberi);
                printf("Kode            : %s\n", inventaris[i].kode);
                printf("Nama            : %s\n", inventaris[i].nama);
                printf("Kategori        : %s\n", inventaris[i].kategori);
                printf("Lokasi          : %s\n", inventaris[i].lokasi);
                printf("Kondisi         : %s\n", inventaris[i].kondisi);
                printf("Jumlah          : %d\n", inventaris[i].jumlah);
                i++;
            }

            // menampilkan jumlah usaha pencarian
            printf("\nUsaha pencarian: %d kali\n", usaha);
            return;
        } else if (cmp < 0) { // jika tanggal di sebelah kanan
            kiri = tengah + 1;
        } else { // jika tanggal di sebelah kiri
            kanan = tengah - 1;
        }
    }

    // jika data tidak ditemukan
    if (!ditemukan) {
        printf("\n** Data dengan tanggal %s tidak ditemukan. **\n", tanggal);
        printf("Usaha pencarian: %d kali\n", usaha);
    }
}

// fungsi untuk memilih metode pengurutan data
void pengurutanData() {
    int subpilih; // variabel untuk menyimpan pilihan metode pengurutan

    // menampilkan menu metode pengurutan
    printf("\n===================================================\n");
    printf("[1] Pengurutan Bubble Sort Berdasarkan Tanggal Pemberian \n");
    printf("[2] Pengurutan Quick Sort Berdasarkan Nama Pemberi\n");
    printf("[0] Keluar Dari Menu ini\n");
    printf("===================================================\n");
    printf("Masukkan Metode Pengurutan: ");
    scanf("%d", &subpilih); // menerima input pilihan metode

    switch (subpilih) {
        case 1:
            bubbleSort(totalAset, inventaris); 
            tampilkanData(); // menampilkan data setelah diurutkan
            break;
        case 2:
            quickSort(0, totalAset - 1); // melakukan pengurutan dengan Quick Sort
            tampilkanData(); // menampilkan data setelah diurutkan
            break;
        case 0:
            printf("\nKembali ke menu utama.\n");
            break;
        default:
            printf("\nPilihan tidak valid, coba lagi.\n");
            break;
    }
}
// Fungsi untuk mengonversi nama bulan menjadi nilai numerik
void bubbleSort(int n, Aset inventaris[]) {
    int usaha = 0; // Variabel untuk menghitung jumlah iterasi yang dilakukan

    // Loop untuk menjalankan pengurutan
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Bandingkan bulan dari tanggal masing-masing aset
            if (strcmp(inventaris[j].tanggalmemberi, inventaris[j + 1].tanggalmemberi) > 0) {
                Aset temp = inventaris[j]; // Simpan elemen sementara
                inventaris[j] = inventaris[j + 1]; // Tukar elemen
                inventaris[j + 1] = temp; // Masukkan elemen sementara ke posisi baru
            }
        }
        usaha++; // Tambah hitungan iterasi
    }
    // Tampilkan jumlah usaha dan pemberitahuan selesai
    printf("Jumlah iterasi yang dilakukan: %d\n", usaha);
    printf("Pengurutan menggunakan Bubble Sort selesai.\n");
}

void quickSort(int low, int high) {
    // Jika ada lebih dari satu elemen, lakukan pengurutan
    if (low < high) {
        int pi = partition(low, high); // Bagi array berdasarkan pivot

        // Urutkan bagian kiri dari pivot
        quickSort(low, pi - 1);

        // Urutkan bagian kanan dari pivot
        quickSort(pi + 1, high);
    }
}

int partition(int low, int high) {
    char pivot[50]; // Elemen pivot yang menjadi acuan
    strcpy(pivot, inventaris[high].Pemberi); // Ambil pivot dari elemen terakhir
    int i = low - 1; // Indeks elemen lebih kecil

    // Bandingkan elemen-elemen dengan pivot
    for (int j = low; j < high; j++) {
        // Jika elemen lebih kecil atau sama dengan pivot, tukar
        if (strcmp(inventaris[j].Pemberi, pivot) <= 0) {
            i++; // Geser indeks elemen lebih kecil

            // Tukar posisi elemen
            Aset temp = inventaris[i];
            inventaris[i] = inventaris[j];
            inventaris[j] = temp;
        }
    }
    // Tukar elemen pivot ke posisi yang benar
    Aset temp = inventaris[i + 1];
    inventaris[i + 1] = inventaris[high];
    inventaris[high] = temp;

    return i + 1; // Kembalikan posisi pivot
}


void transaksiPenambahanItem() {
    char kode[10]; // menyimpan kode aset yang akan ditambahkan
    int jumlah; // menyimpan jumlah yang akan ditambahkan

    // menampilkan header menu transaksi penambahan item
    printf("\n=================================================\n");
    printf("=== Transaksi Penambahan Item ===\n");
    printf("=================================================\n");

    // meminta input kode aset dan jumlah yang akan ditambahkan
    printf("Masukkan Kode Aset: ");
    scanf("%s", kode); // input kode aset
    printf("Masukkan Jumlah yang ingin ditambahkan: ");
    scanf("%d", &jumlah); // input jumlah yang ingin ditambahkan

    // mencari kode aset di dalam inventaris
    for (int i = 0; i < totalAset; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) { // cek apakah kode aset cocok
            inventaris[i].jumlah += jumlah; // tambahkan jumlah ke inventaris
            printf("\n** Jumlah berhasil ditambahkan! **\n");
            return; // keluar dari fungsi karena transaksi selesai
        }
    }

    // jika kode aset tidak ditemukan
    printf("\n** Data dengan kode %s tidak ditemukan. **\n", kode);
}

void transaksiPeminjamanItem() {
    char kode[10]; // menyimpan kode aset yang akan dipinjam
    int jumlah; // menyimpan jumlah yang akan dipinjam

    // menampilkan header menu transaksi peminjaman barang
    printf("\n=================================================\n");
    printf("=== Transaksi Peminjaman Barang ===\n");
    printf("=================================================\n");

    // meminta input kode aset dan jumlah yang ingin dipinjam
    printf("Masukkan Kode Aset: ");
    scanf("%s", kode); // input kode aset
    printf("Masukkan Jumlah yang ingin dipinjam: ");
    scanf("%d", &jumlah); // input jumlah yang ingin dipinjam

    // mencari kode aset di dalam inventaris
    for (int i = 0; i < totalAset; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) { // cek apakah kode aset cocok
            if (inventaris[i].jumlah >= jumlah) { // cek apakah stok mencukupi
                // kurangi jumlah barang di inventaris
                inventaris[i].jumlah -= jumlah;

                // simpan data peminjaman
                strcpy(pinjam[totalpinjam].kode, inventaris[i].kode); // salin kode aset
                strcpy(pinjam[totalpinjam].nama, inventaris[i].nama); // salin nama aset
                strcpy(pinjam[totalpinjam].kategori, inventaris[i].kategori); // salin kategori aset
                pinjam[totalpinjam].jumlah = jumlah; // set jumlah yang dipinjam

                // tambahkan jumlah total peminjaman
                totalpinjam++;

                // tampilkan pesan berhasil
                printf("\n** Barang berhasil dipinjam! **\n");
                printf("===============================================\n");
                printf("Nama           : %s\n", inventaris[i].nama); // tampilkan nama barang
                printf("Kategori       : %s\n", inventaris[i].kategori); // tampilkan kategori barang
                printf("Lokasi         : %s\n", inventaris[i].lokasi); // tampilkan lokasi barang
                printf("Kondisi        : %s\n", inventaris[i].kondisi); // tampilkan kondisi barang
                printf("===============================================\n");
                printf("Sisa jumlah: %d\n", inventaris[i].jumlah); // tampilkan jumlah sisa
            } else {
                // jika stok tidak mencukupi
                printf("\n** Stok tidak mencukupi! **\n");
                printf("Jumlah tersedia: %d\n", inventaris[i].jumlah); // tampilkan jumlah yang tersedia
            }
            return; // keluar dari fungsi karena transaksi selesai
        }
    }

    // jika kode aset tidak ditemukan
    printf("\n** Data dengan kode %s tidak ditemukan. **\n", kode);
}
void cetakHasilAkhir() {
    FILE *file; // pointer untuk akses file
    file = fopen("Hasil_Akhir_Inventaris.txt", "w"); // membuka file untuk menulis hasil akhir

    if (file == NULL) { // cek jika file gagal dibuka
        printf("\n** Gagal membuat file. **\n");
        return;
    }

    // menulis header ke file
    fprintf(file, "=================================================\n");
    fprintf(file, "=== Hasil Akhir Data Inventaris ===\n");
    fprintf(file, "=================================================\n");

    if (totalAset == 0) { // cek jika tidak ada data
        fprintf(file, "** Tidak ada data inventaris yang tersedia. **\n");
    } else {
        for (int i = 0; i < totalAset; i++) { // loop untuk menulis setiap aset ke file
            fprintf(file, "\nInventaris #%d\n", i + 1);
            fprintf(file, "Pemberi        : %s\n", inventaris[i].Pemberi);
            fprintf(file, "Tanggal Memberi: %s\n", inventaris[i].tanggalmemberi);
            fprintf(file, "Kode           : %s\n", inventaris[i].kode);
            fprintf(file, "Nama           : %s\n", inventaris[i].nama);
            fprintf(file, "Kategori       : %s\n", inventaris[i].kategori);
            fprintf(file, "Lokasi         : %s\n", inventaris[i].lokasi);
            fprintf(file, "Kondisi        : %s\n", inventaris[i].kondisi);
            fprintf(file, "Jumlah         : %d\n", inventaris[i].jumlah);
            fprintf(file, "=============================================\n");
        }
    }

    fclose(file); // menutup file setelah selesai menulis
    printf("\n** Hasil akhir berhasil disimpan ke file 'Hasil_Akhir_Inventaris.txt'. **\n");
}
void editData() {
    char kode[10]; //  Menyimpan kode aset yang mau diedit
    int ditemukan = 0; // flag untuk menandakan kode aset ketemu atau tidak

    // Menampilkan header buat menu edit data aset
    printf("\n=================================================\n");
    printf("=== Edit Data Aset ===\n");
    printf("=================================================\n");
    printf("Masukkan Kode inventaris yang ingin diubah: ");
    scanf("%s", kode); // Input kode inventaris yang mau diubah

    // loop buat nyari kode inventaris yang cocok
    for (int i = 0; i < totalAset; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) { // Cek kode cocok atau tidak
            ditemukan = 1; // tandain kode aset ketemu
            printf("\n** Data ditemukan. **\n");
            printf("Pemberi        : %s\n", inventaris[i].Pemberi); // Menampilkan data lama
            printf("Tanggal Memberi: %s\n", inventaris[i].tanggalmemberi);
            printf("Kode           : %s\n", inventaris[i].kode);
            printf("Nama           : %s\n", inventaris[i].nama);
            printf("Kategori       : %s\n", inventaris[i].kategori);
            printf("Lokasi         : %s\n", inventaris[i].lokasi);
            printf("Kondisi        : %s\n", inventaris[i].kondisi);
            printf("Jumlah         : %d\n", inventaris[i].jumlah);

            // Masukkan data baru
            printf("\nMasukkan data baru:\n");
            printf("Nama          : ");
            scanf(" %[^\n]s", inventaris[i].nama);
            printf("Kategori      : ");
            scanf(" %[^\n]s", inventaris[i].kategori);
            printf("Lokasi        : ");
            scanf(" %[^\n]s", inventaris[i].lokasi);
            printf("Kondisi       : ");
            scanf(" %[^\n]s", inventaris[i].kondisi);
            printf("Jumlah        : ");
            scanf("%d", &inventaris[i].jumlah);


            // Memberi pesan kalau data sudah berhasil diubah
            printf("\n** Data berhasil diubah! **\n");
            break; // Keluar dari loop karena data sudah diedit
        }
    }

    // Jika kode inventaris tidak ketemu, beri pesan ini
    if (!ditemukan) {
        printf("\n** Data dengan kode %s tidak ditemukan. **\n", kode);
    }
}
void transaksiPenguranganItem() {

    char kode[10]; // Variabel untuk menyimpan kode aset yang akan dikurangi
    int jumlah; // Variabel untuk menyimpan jumlah yang ingin dikurangi
    int found = 0; // Flag untuk menandai apakah kode aset ditemukan
    
    // Menampilkan header menu transaksi pengurangan item
    printf("\n=================================================\n");
    printf("=== Transaksi Pengurangan Item ===\n");
    printf("=================================================\n");
    // Meminta input kode aset dan jumlah yang ingin dikurangi
    printf("Masukkan Kode Aset: ");
    scanf("%s", kode);
    printf("Masukkan Jumlah yang ingin dikurangi: ");
    scanf("%d", &jumlah);

    // Loop untuk mencari aset berdasarkan kode
    for (int i = 0; i < totalAset; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) { // Mengecek apakah kode cocok
            found = 1; // Menandai bahwa kode aset ditemukan
            if (inventaris[i].jumlah >= jumlah) { // Mengecek apakah jumlah mencukupi
                inventaris[i].jumlah -= jumlah; // Mengurangi jumlah aset
                printf("\n** Jumlah berhasil dikurangi! **\n");
            } else {
                // Pesan jika jumlah tidak mencukupi
                printf("\n** Jumlah aset tidak mencukupi untuk dikurangi. **\n");
            }
            return; // Keluar dari fungsi setelah transaksi selesai
        }
    }
    // Jika kode aset tidak ditemukan
    if (!found) {
        printf("\n** Data dengan kode %s tidak ditemukan. **\n", kode);
    }
}
int Menutama() {
    int pilihan;
    int anggotaBEM;

    // Menampilkan pesan pembuka
    printf("\n=====================================================\n");
    printf("=== Selamat Datang di Sistem Manajemen Inventaris ===\n");
    printf("=====================================================\n");
    printf("Apakah Anda merupakan anggota BEM Kemakom?\n");
    printf("[1] Ya\n");
    printf("[2] Tidak\n");
    printf("=====================================================\n");
    printf("Pilih: ");
    scanf("%d", &anggotaBEM);

    // Mengecek status anggota BEM
    if (anggotaBEM == 2) {
        printf("\nAkses hanya diperuntukkan bagi anggota BEM Kemakom.\n");
        printf("Terima kasih, program akan keluar.\n");
        return 0;
    } else if (anggotaBEM != 1) {
        printf("\nPilihan tidak valid, program akan keluar.\n");
        return 0;
    }

    // Jika iya, masukkan data pengguna
    printf("\n=================================================\n");
    printf("=== Masukkan Data Anda ===\n");
    printf("=================================================\n");
    printf("Masukkan NIM      : ");
    scanf("%s", pengguna.nim);
    printf("Masukkan Nama     : ");
    scanf(" %[^\n]s", pengguna.nama);

    while (1) {
        printf("Masukkan Divisi   : ");
        scanf(" %[^\n]s", pengguna.jabatan);
        if (isValidJabatan(pengguna.jabatan)) {
            break;
        } else {
            printf("\nJabatan tidak valid. Harap masukkan Divisi yang sesuai.\n");
        }
    }

    printf("\nSelamat datang, %s (%s), dari Divisi: %s.\n", pengguna.nama, pengguna.nim, pengguna.jabatan);
    sleep(2);
    do {
    clearScreen();
    printf("\n══════════════════════════════════════════════════════════════════════\n");
    printf("🌟 WELCOME TO 🌟\n");
    printf("████████╗██╗   ██╗██████╗ ███████╗███████╗\n");
    printf("╚══██╔══╝██║   ██║██╔══██╗██╔════╝██╔════╝\n");
    printf("╚══██╔══╝██║   ██║██╔══██╗██╔════╝██╔════╝\n");
    printf("   ██║   ██║   ██║██████╔╝█████╗  ███████╗  \n");
    printf("   ██║   ██║   ██║██   ██ ██╔══╝  ╚════██║ \n");
    printf("   ██║   ██║   ██║██   ██ ██╔══╝  ╚════██║\n");
    printf("   ██║   ╚██████╔╝██████╗ ███████╗███████╗\n");
    printf("   ╚═╝    ╚═════╝ ╚═════╝╚══════╝╚══════╝\n");
    printf("✨ Sistem Manajemen Inventaris KEMAKOM ✨\n");
    printf("══════════════════════════════════════════════════════════════════════\n");
    printf("📂 [1] Tampil Inventaris Yang Ada\n");
    printf("📜 [2] SOP Penambahan Inventaris\n");
    printf("➕ [3] Penambahan Inventaris\n");
    printf("🔢 [4] Pengurutan Inventaris\n");
    printf("📅 [5] Histori Tanggal Pemberian & Pencarian Inventaris\n");
    printf("✏️  [6] Edit/Update Inventaris\n");
    printf("💰 [7] Transaksi Penambahan Inventaris\n");
    printf("📉 [8] Transaksi Pengurangan Inventaris\n");
    printf("❌ [9] Hapus Inventaris\n");
    printf("📄 [10] Menu Peminjaman Barang\n");
    printf("📦 [11] Cetak ke File .txt\n");
    printf("👥 [0] Anggota Kelompok & Keluar\n");
    printf("══════════════════════════════════════════════════════════════════════\n");
    printf("🔍 Pilih menu: ");
    scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanData();
                break;
            case 2:
                SOPPenambahanBarang();
                break;
            case 3:
                tambahData();
                tampilkanData();
                break;
            case 4:
                pengurutanData();
                break;
            case 5:
                pencarianData();
                break;
            case 6:
                tampilkanData();
                editData();
                tampilkanData();
                break;
            case 7:
                tampilkanData();
                transaksiPenambahanItem();
                tampilkanData();
                break;
            case 8:
                tampilkanData();
                transaksiPenguranganItem();
                tampilkanData();
                break;
            case 9:
                tampilkanData();
                hapusData();
                tampilkanData();
                break;
            case 10:
                sleep(1);
                peminjaman2();
                break;
            case 11: 
                cetakHasilAkhir();

                break;
            case 0:
                anggotaKelompok();
                printf("\nTerima kasih telah menggunakan sistem ini, %s.\n", pengguna.nama);
                break;
            default:
                printf("\nPilihan tidak valid, coba lagi.\n");
        }

        if (pilihan != 0) {
            printf("\nTekan ENTER untuk melanjutkan...");
            getchar(); // Menunggu input
            getchar();
        }
    } while (pilihan != 0);

    return 0;
}
void pengembalian() {
    char kode[10]; // Mendeklarasikan array karakter untuk menyimpan kode barang yang akan dikembalikan
    int jumlah; // Mendeklarasikan variabel untuk menyimpan jumlah barang yang ingin dikembalikan
    Tampilbarangpinjam();
    printf("\n=================================================\n");
    printf("=== Pengembalian Barang Peminjaman ===\n");
    printf("=================================================\n");
    printf("Masukkan Kode Barang: ");
    scanf("%s", kode);
    printf("Masukkan Jumlah yang ingin dikembalikan: ");
    scanf("%d", &jumlah);

    // Melakukan iterasi untuk mencari barang yang dipinjam berdasarkan kode yang dimasukkan
    for (int i = 0; i < totalpinjam; i++) {
        // Membandingkan kode barang yang dipinjam dengan kode yang diberikan oleh pengguna
        if (strcmp(pinjam[i].kode, kode) == 0) {
            // Memastikan bahwa jumlah yang ingin dikembalikan tidak lebih dari jumlah yang dipinjam
            if (pinjam[i].jumlah >= jumlah) {
                // Mengurangi jumlah barang yang dipinjam
                pinjam[i].jumlah -= jumlah;

                // Tambahkan jumlah barang ke inventaris
                for (int j = 0; j < totalAset; j++) {
                    // Mencari barang di inventaris berdasarkan kode yang dimasukkan
                    if (strcmp(inventaris[j].kode, kode) == 0) {
                        inventaris[j].jumlah += jumlah; // Menambah jumlah barang di inventaris
                        break; // Keluar dari loop setelah menemukan barang
                    }
                }

                printf("\n** Barang berhasil dikembalikan! **\n");// Menampilkan pesan bahwa pengembalian berhasil


                // Jika semua barang sudah dikembalikan, hapus data peminjaman
                if (pinjam[i].jumlah == 0) {
                    // Menggeser data peminjaman untuk menghapus entri yang sudah dikembalikan
                    for (int k = i; k < totalpinjam - 1; k++) {
                        pinjam[k] = pinjam[k + 1]; //Menggeser elemen ke kiri
                    }
                    totalpinjam--; // Mengurangi total peminjaman
                }

                return;
            } else {
                // Jika jumlah yang dikembalikan melebihi jumlah yang dipinjam
                printf("\n** Jumlah yang dikembalikan melebihi jumlah yang dipinjam! **\n");
                return;
            }
        }
    }
    // Jika kode barang tidak ditemukan dalam daftar peminjaman
    printf("\n** Data peminjaman dengan kode %s tidak ditemukan. **\n", kode);
}
