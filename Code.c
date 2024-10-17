// NAMA KELOMPOK :
//PUTRI FEBIYANI - 2602181875
//NAZHIRA DEWI AQMARINA - 2602155574
//STEPHEN WIJAYA UTAMA - 2602099812

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char kode[8];
char nama[50];

int nilai;
int sks;

typedef struct matkul{
    char nama[50];
    char kode[8];
    int sks;
    int nilai;
    struct matkul *lanjut, *kembali;
}matkul;

matkul *kepala, *ekor;

void init(){
    kepala = NULL;
    ekor = NULL;
}

int isEmpty(){
    if(ekor==NULL)
    return 1;
    else
    return 0;
}

void data_depan(char *kode, char *nama, int sks, int nilai){
    matkul *temp;
    temp = malloc(sizeof(struct matkul));
    strcpy(temp->kode, kode);
    strcpy(temp->nama, nama);
    temp->nilai = nilai;
    temp->sks = sks;

    if(isEmpty()==1){
        kepala = temp;
        ekor = kepala;
        kepala->lanjut = kepala;
        kepala->kembali = kepala;
        ekor->lanjut = ekor;
        ekor->kembali = ekor;
    } else {
        temp->lanjut = kepala;
        kepala->kembali = temp;
        kepala = temp;
        kepala->kembali = ekor;
        ekor->lanjut = kepala;
    }
    FILE* fp = fopen("matakuliah.txt", "a");
    if (fp == NULL) {
        printf("File tidak dapat dibuka atau dibuat\n");
        return;
    }

    fprintf(fp, "%s,%s,%d,%d\n", temp->kode, temp->nama, temp->sks, temp->nilai);

    fclose(fp);
    
    printf("=====================================\n");
    printf("===Data telah ditambahkan===\n");
    printf("Data dengan kode : %s\n",temp->kode);
    printf("Data dengan nama : %s\n",temp->nama);
    printf("Data berhasil ditambahkan di depan!\n");
}

void data_belakang(char *kode, char *nama, int sks, int nilai){
    matkul *temp;
    temp = malloc(sizeof(struct matkul));
    strcpy(temp->kode, kode);
    strcpy(temp->nama, nama);
    temp->nilai = nilai;
    temp->sks = sks;

    if(isEmpty()==1){
        kepala = temp;
        ekor = kepala;
        kepala->lanjut = kepala;
        kepala->kembali = kepala;
        ekor->lanjut = ekor;
        ekor->kembali = ekor;
    }else{
        ekor->lanjut = temp;
        temp->kembali = ekor;
        ekor = temp;
        ekor->lanjut = kepala;
        kepala->kembali = ekor;
    }
    
    FILE* fp = fopen("matakuliah.txt", "a");
    if (fp == NULL) {
        printf("File tidak dapat dibuka atau dibuat\n");
        return;
    }

    fprintf(fp, "%s,%s,%d,%d\n", temp->kode, temp->nama, temp->sks, temp->nilai);

    fclose(fp);
    
    printf("=====================================\n");
    printf("===Data telah ditambahkan===\n");
    printf("Data dengan kode : %s\n",temp->kode);
    printf("Data dengan nama : %s\n",temp->nama);
    printf("Data berhasil ditambahkan di belakang!\n");
}

void hapus_depan(){
    matkul *del;
    char d[8];

    if(kepala != ekor){
        del = kepala;
        strcpy(d, del->kode);
        kepala = kepala->lanjut;
        kepala->kembali = ekor;
        ekor->lanjut = kepala;
        free(del);
    }else{
        strcpy(d, del->kode);
        kepala = NULL;
        ekor = NULL;
    }
    printf("Data %s berhasil dihapus!\n", d);
}

void hapus_belakang(){
    matkul *del;
    char d[8];

    if(kepala!=ekor){
    del = ekor;
    strcpy(d, del->kode);
    ekor = ekor->kembali;
    ekor->lanjut = kepala;
    kepala->kembali = ekor;
    free(del);
    }else{
    strcpy(d, del->kode);
    kepala = NULL;
    ekor = NULL;
    }
    printf("Data %s berhasil dihapus!\n", d);
}

void cari_data(char *cari){
    matkul *help, *s_earch;
    int index;

    help = kepala;
    index = 1;
    do{
        if(strcmp(help->kode, cari)==0){
            s_earch = help;
            printf("Data kode %s dengan baris %d\n",cari,index);
            return;
        }
        index++;
        help = help->lanjut;
    }
    while(help!=ekor->lanjut);
    printf("Data kode %s tidak ditemukan",cari);
}

void menampilkan_jumlah(){
    matkul *help;
    help = kepala;

    int n = 0;
    if(isEmpty()==1){
        printf("Data masih kosong");
        return;
    }else{
        do{
            n++;
            help = help->lanjut;
        }while(help!=ekor->lanjut);
        printf("Jumlah data = %d\n", n);
        printf("-----------------\n");
    }
}

void menampilkan_semua(){
    matkul *help;
    help = kepala;
    FILE *fp;

    int n = 1;
    if(isEmpty() == 1){
        printf("Data masih kosong, silahkan menambahkan data terlebih dahulu\n");
        return;
    }else{
        if ((fp = fopen("matakuliah.txt","r")) == NULL){
            printf("Error! opening file");
            exit(1);
        }
        printf("===========D A T A  M A T A  K U L I A H===========\n");
        do{
            fscanf(fp,"%[^\','],%[^\','],%[^\','],%[^\',']\n", help->kode, help->nama, &help->sks, &help->nilai);
            printf("Mata kuliah ke : %d\n", n);
            printf("Kode mata kuliah : %s\n", help->kode);
            printf("Nama mata kuliah : %s\n", help->nama);
            printf("Nilai mata kuliah : %d\n", help->nilai);
            printf("Jumlah SKS : %d\n", help->sks);
            printf("-------------------------------------\n");
            help = help->lanjut;
            n++;
        } while(help != ekor->lanjut);
        printf("\n");
        fclose(fp);
    }
}


void nilaiMinMax(){
    matkul *help, *terbesar, *terkecil;

    help = kepala;
    terbesar = help;
    terkecil = help;

    if(isEmpty()==1){
        printf("Belum terdapat data\n");
        return;
    }else{
        do{
            if(help->nilai < terbesar->nilai){
                terbesar = help;
            }
            if(help->nilai > terkecil->nilai){
                terkecil = help;
            }
            help = help->lanjut;
        }while(help!=ekor->lanjut);
        printf("===========Data Matkul Terbesar===========\n");
        printf("Kode mata kuliah : %s\n", terbesar->kode);
        printf("Nama mata kuliah : %s\n", terbesar->nama);
        printf("Jumlah SKS : %d\n", terbesar->sks);
        printf("Nilai : %d\n", terbesar->nilai);
        printf("===========================================\n");
        printf("-----------Data Matkul Terkecil-----------\n");
        printf("Kode mata kuliah : %s\n", terkecil->kode);
        printf("Nama mata kuliah : %s\n", terkecil->nama);
        printf("Jumlah SKS : %d\n", terkecil->sks);
        printf("Nilai : %d\n", terkecil->nilai);
        printf("------------------------------------------\n");
    }
}

void lulus(int nilai){
    matkul *help;
    int jumlah = 0;

    help = kepala;
    printf("Nilai Minimal : %d\n",nilai);
    printf("==========Data Matkul Yang Tidak Lulus==========\n");
    do{
        if(help->nilai < nilai){
            printf("-------------------------------------\n");
            printf("Kode mata kuliah : %s\n", help->kode);
            printf("Nama mata kuliah : %s\n", help->nama);
            printf("Jumlah SKS : %d\n", help->sks);
            printf("Nilai mata kuliah : %d\n", help->nilai);
            printf("Mata kuliah tidak lulus!\n");
            printf("-------------------------------------\n");
            jumlah++;
        }
        help = help->lanjut;
    }while(help!=ekor->lanjut);
    if(jumlah==0){
        printf("+------------------------------------+\n");
        printf("Semua mata kuliah lulus!!\n");
    }
}

void average(){
    matkul *help;
    int jumlah;
    int n;
    float rata;
    help = kepala;
    jumlah = 0;
    n = 0;
    do{
        jumlah = jumlah+help->nilai;
        n++;
        help = help->lanjut;
    }while(help!=ekor->lanjut);
    rata = jumlah/n;
    printf("=========Rata-rata=========\n");
    printf("Jumlah nilai : %d\n", jumlah);
    printf("Jumlah data : %d\n", n);
    printf("Rata-rata : %.2f\n", rata);
    printf("===========================\n");
}

void reset(){
    matkul *help, *hapus;
    help = kepala;
    do{
        hapus = help;
        help = kepala->lanjut;
        free(hapus);
    }while(help->lanjut!=kepala);
    kepala = NULL;
    ekor = NULL;
    printf("Data telah terhapus\n");
}

void cek_sks(int newSks){
    if(newSks > 3){
        do{
            printf("Maaf rentang jumlah SKS salah..\n");
            printf("Masukkan jumlah SKS (max 3) : ");
            scanf("%d",&newSks);
            fflush(stdin);
        }while(newSks>3);
    }
    sks = newSks;
}

void cek_kodeKuliah(char *kode){
    matkul *s_earch;
    s_earch = kepala;
    if(isEmpty()==0){
        do{
            if(strcmp(s_earch->kode, kode)==0){
                do{
                    printf("Kode kuliah sudah ada\n");
                    printf("Masukkan kode mata kuliah : ");
                    gets(kode);
                }while(strcmp(s_earch->kode, kode)==0);
            }
            s_earch = s_earch->lanjut;
        }while(s_earch!=ekor);
    }
}

void cekMinMax(int score){
    if(score > 100){
        do{
            printf("Input nilai salah, rentang nilai (1-100)\n");
            printf("Masukkan nilai matkul : ");
            scanf("%d",&score);
            fflush(stdin);
        }while(score > 100);
        nilai = score;
    }
}

void delete(char *poin){
    matkul *del, *help;
    help = kepala;
    do{
        if(strcmp(help->kode, poin)==0){
            del = help;
            if(help == kepala && kepala == ekor){
                kepala = NULL;
                ekor = NULL;
            }else if(help == kepala){
                kepala = kepala->lanjut;
                kepala->kembali = ekor;
                ekor->lanjut = kepala;
                free(del);
            }else if(help == ekor){
                ekor = ekor->kembali;
                ekor->lanjut = kepala;
                kepala->kembali = ekor;
                free(del);
            }else{
                help->kembali->lanjut = help->lanjut;
                help->lanjut->kembali = help->kembali;
                free(del);
            }
            printf("Data dengan kode mata kuliah %s telah dihapus\n", poin);
            return;
        }
        help = help->lanjut;
    }while(help!=ekor->lanjut);
    printf("Data tidak ditemukan %s\n", poin);
}

void jam(){
    struct tm *waktu;
    time_t Timeval;
    Timeval = time(0);
    waktu = localtime(&Timeval);
    printf("\t\t\t  %s", asctime(waktu));
}

void loading(){
	int i;
	printf("\n\n\n\n\n\n\n");
    printf("\n\n\n\t\t\t\t\t Loading......");
    printf("\n\n");
    printf( "\t\t\t\t\t");
    for (i=0; i<= 35; i++)
    {
        printf("%c", 178);
        Sleep(10);
    }
    printf ("\n\n\t\t\t\t\t 'PRESS ENTER TO START'");
    system ("pause>0");
    system ("cls");
}

// REVISI
void baca_data() {
    FILE* fp = fopen("matakuliah.txt", "r");
    if (fp == NULL) {
        printf("File tidak dapat dibuka\n");
        return;
    }

    while (1) {
        matkul* temp = malloc(sizeof(struct matkul));
        int result = fscanf(fp, "%[^,],%[^,],%d,%d\n", temp->kode, temp->nama, &(temp->sks), &(temp->nilai));
        if (result != 4) {
            free(temp);
            break;
        }

        temp->lanjut = NULL;
        temp->kembali = NULL;

        if (isEmpty() == 1) {
            kepala = temp;
            ekor = kepala;
            kepala->lanjut = kepala;
            kepala->kembali = kepala;
            ekor->lanjut = ekor;
            ekor->kembali = ekor;
        } else {
            ekor->lanjut = temp;
            temp->kembali = ekor;
            ekor = temp;
            ekor->lanjut = kepala;
            kepala->kembali = ekor;
        }
    }

    fclose(fp);
}


int main(){
    init();
    Sleep(1000);
    system ("color B");
    loading();
    jam();
    // REVISI
    baca_data();
    int tidak_lulus;
    int menu;
    char kirim[5];
    char del[10];
    char cari[15];
    char poin[20];

    do{
        printf("\n=====================MENU DATA MATA KULIAH=====================\n");
        printf("Menu\n");
        printf("1. Menambahkan mata kuliah di belakang\n");
        printf("2. Menambahkan mata kuliah di depan\n");
        printf("3. Menghapus mata kuliah di depan\n");
        printf("4. Menghapus mata kuliah di belakang\n");
        printf("5. Menghapus mata kuliah dengan kode\n");
        printf("6. Mencari dan menampilkan data mata kuliah\n");
        printf("7. Menampilkan jumlah data mata kuliah\n");
        printf("8. Menampilkan semua data\n");
        printf("9. Mencari nilai terbesar dan nilai terkecil\n");
        printf("10. Menampilkan daftar mata kuliah yang tidak lulus\n");
        printf("11. Menampilkan rata-rata\n");
        printf("12. Reset data\n");
        printf("13. Keluar\n");
        printf("===============================================================\n");
        printf("Masukkan pilihan : ");
        scanf("%d",&menu);
        fflush(stdin);

        switch (menu)
        {
        case 1: {
            fflush(stdin);
            printf("=====================TAMBAH DATA BELAKANG=====================\n");
            printf("Masukkan data");
            printf("\nKode mata kuliah : ");
            gets(kode);
            fflush(stdin);
            cek_kodeKuliah(kode);

            printf("Nama mata kuliah : ");
            gets(nama);
            fflush(stdin);

            printf("Jumlah SKS mata kuliah (max 3) : ");
            scanf("%d",&sks);
            fflush(stdin);
            cek_sks(sks);

            printf("Masukkan nilai mata kuliah (max 100) : ");
            scanf("%d",&nilai);
            fflush(stdin);
            cekMinMax(nilai);
            system("cls");
            data_belakang(kode,nama,sks,nilai);
            break;
        }

        case 2: {
            fflush(stdin);
            printf("=====================TAMBAH DATA DEPAN=====================\n");
            printf("Masukkan data");
            printf("\nKode mata kuliah : ");
            gets(kode);
            fflush(stdin);
            cek_kodeKuliah(kode);

            printf("Nama mata kuliah : ");
            gets(nama);
            fflush(stdin);

            printf("Jumlah SKS mata kuliah (max 3) : ");
            scanf("%d",&sks);
            fflush(stdin);
            cek_sks(sks);

            printf("Masukkan nilai mata kuliah (max 100) : ");
            scanf("%d",&nilai);
            fflush(stdin);
            cekMinMax(nilai);
            system("cls");
            data_depan(kode,nama,sks,nilai);
            break;
        }

        case 3: {
            fflush(stdin);
            if(isEmpty()==1){
                printf("Maaf tidak terdapat data\n");
            }else{
                system("cls");
                printf("Apakah anda yakin akan menghapus data di depan? (y or t) : ");
                gets(kirim);
                fflush(stdin);
                if(strcmp(kirim, "y")==0){
                    hapus_depan();
                }else{
                    printf("Data gagal dihapus!\n");
                    system("cls");
                }
            }
            break;
        }

        case 4: {
            fflush(stdin);
            if(isEmpty()==1){
                printf("Maaf tidak terdapat data\n");
            }else{
                system("cls");
                printf("Apakah anda yakin akan menghapus data di belakang? (y or t) : ");
                gets(kirim);
                fflush(stdin);
                if(strcmp(kirim, "y")==0){
                    hapus_belakang();
                }else{
                    printf("Data gagal dihapus!\n");
                }
            }
            break;
        }

        case 5: {
            fflush(stdin);
            if(isEmpty()==1){
                printf("Maaf tidak terdapat data\n");
            }else{
                system("cls");
                printf("Masukkan kode mata kuliah : ");
                gets(del);
                printf("Apakah anda yakin akan menghapus data? (y or t) : ");
                gets(kirim);
                fflush(stdin);
                if(strcmp(kirim, "y")==0){
                    delete(del);
                }else{
                    printf("Data gagal dihapus!\n");
                }
            }
            break;
        }

        case 6: {
            system("cls");
            printf("Masukkan kode mata kuliah : ");
            gets(cari);
            fflush(stdin);
            cari_data(cari);
            break;
        }

        case 7: {
            fflush(stdin);
            system("cls");
            menampilkan_jumlah();
            break;
        }

        case 8:{
            fflush(stdin);
            system("cls");
            menampilkan_semua();
            break;
        }

        case 9: {
            fflush(stdin);
            system("cls");
            nilaiMinMax();
            break;
        }

        case 10: {
            fflush(stdin);
            if(isEmpty()==1){
                printf("Data mata kuliah kosong\n");
            }else{
                system("cls");
                printf("Data mata kuliah tidak lulus\n");
                printf("Masukkan batas nilai : ");
                scanf("%d", &nilai);
                fflush(stdin);
                lulus(nilai);
            }
            break;
        }

        case 11: {
            fflush(stdin);
            system("cls");
            average();
            break;
        }

        case 12: {
            fflush(stdin);
            if(isEmpty()==1){
                printf("Maaf tidak terdapat data\n");
            }else{
                system("cls");
                printf("Apakah anda yakin akan mereset data? (y or t) : ");
                gets(kirim);
                fflush(stdin);
                if(strcmp(kirim, "y")==0){
                    reset();
                }else{
                    printf("Data gagal dihapus!\n");
                }
            }
            break;
        }

        case 13: {
            printf(">>Terima kasih telah menggunakan program ini!<<\n");
            exit;
            break;
        }
        default:{
            printf("Maaf input anda tidak sesuai\n");
            system("cls");
            break;
        }
        }
    }while(menu!=13);

}
