#include <stdio.h>
#include <windows.h>
#include <dirent.h>
#include "conio.h"
#include "input.h"
#include "file.h"
#include "design.h"

#define MAX 256

bool txt_extension(char const *name)
{
	/* --- Modul untuk mengambil ekstensi file  --- */
    
	size_t len = strlen(name); // panjang array
    
    /* Cek apakah ekstensinya .txt */
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

bool fileToList(list *L, int *baris, int *kolom, bool fileTersedia, char namaFile[30])
{
	/* Kamus Data */
	FILE *file; // variable file  
	address P; // variable untuk menampung address
	char ch; // variable untuk menampung karakter input
	bool cek; // validasi
	int max_height = 30;
	int max_width = 120;
	
	/* --- Algortima --- */
	
	file = fopen(namaFile, "r"); // membuka file dengan mode read	
	
	/* Jika File kosong */
	if(file == NULL)
	{
		gotoxy(28,14);
		printf("File tidak tersedia");
		barMenu();
		getch();
		cek = false;
	}
	
	/* Jika File ada */
	else 
	{
		system("cls"); // clear screen 
		gotoxy(8,0); // Kembali ke 8,0
		
		while(!feof(file)) // baca file sampai end of file
		{
			ch = fgetc(file); // ambil karakter dalam file masukkan dalam variable ch
			
			/* Error handling karena node awal berisi NULL*/
			if (ch == -1) 
			{
				continue;
			}
			
			/* Print Enter ketika membaca '\n' dalam file */
			if(ch == '\n')
			{
				enter(*(&L), NULL, *(&baris), *(&kolom));
			}
			
			/* Alokasikan apa yang dibaca kedalam memori heap */
			else
			{
				P = Alokasi(ch); // alokasi pembacaan ch
				normal_input(*(&L), P, &(*baris), &(*kolom)); // representasi console
			}
			SetWindow(&max_height+2, &max_width+2, *baris, *kolom, *L);
		}
		cek = true; 
		fclose(file); // menuntup file
	}
	
	return cek; // mereturn nilai yang disimpan dalam cek
}

void ListFile(list *L)
{
	/* --- Kamus Data --- */
	int jumlah = 1; // variable untuk menghitung jumlah file .txt
	char cwd[PATH_MAX]; // variable untuk menampung nama file
    struct dirent *d; // variable record untuk menampung data directory
    DIR *dr; // variable record yang merepresentasikan directory stream, stream : penghubung 
    
    system("cls"); // clear screen
    getcwd(cwd, sizeof(cwd)); // prosedur untuk mengambil data direcoty saat ini
    dr = opendir(cwd); // membuka directory 
    if(dr!=NULL)
    {
    	printf("Daftar File : \n");
    	/* Membaca isi directory satu persatu dengan fungsi readdir */
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
        	/* Jika Ekstensi nya .txt */
        	if(txt_extension(d->d_name))
			{
        		printf("%d. %s \n", jumlah, d->d_name);
        		jumlah++;
			}
        }
        closedir(dr); // Menutup direcotory
    }
    else
	{
		printf("\nERROR: Folder tidak ditemukan!");
	}
}

void inputNamaFile(char karakter[30])
{
    /* Kamus Data Lokal*/
    char ch;                        // variable penampung input karakter
    int array = 0;                  // variable menampung data input
    
    /* Algoritma agar insert tidak melebihi batas (25 karakter )*/
    memset(karakter, 0, 1);
    while(1)
	{
        /* Pengaturan agar karakter seragam (huruf kecil) */
        ch = getch();

        /* Jika menekan enter selesai */
       	if(ch == 13 && strlen(karakter)>0)
		{
            break;
        }else
        
		if(ch == 0)
        {
        	ch = getch();
		}else

        /* Jika menekan backspace mengahapus karakter */
        if(ch == 8 || ch == 127)
		{
            /* Jika line berada di line awal pengahpusan tidak bekerja */
            if(array <= 0)
			{
                continue;
            }
			
            else
			{
                printf("\b \b");
                karakter[array-1] = '\0';
                array--;
            }
        }else
		
		// disable arrow 
		if(ch == 72 || ch == 80 || ch == 75 || ch == 77){
			continue;
		}else 
		
		if(	
				(ch == -32) || (ch == 10) ||
				!(ch >= 'a' && ch <= 'z') && 
				!(ch >= 'A' && ch <= 'Z') &&
				!(ch >= '0' && ch <= '9') &&
				!(ch == 10)
			)
		{
        	continue;
		}
		
		else
		{
            /* Jika batas karakter yang dinput sama dengan 25 tidak dapat menginput lagi */
        	if(strlen(karakter)>=25)
			{
            	continue;
			}

            /* Mengimput */
            karakter[array] = ch;
            karakter[array+1] = '\0';
            printf("%c", karakter[array]);
            array = array + 1;
        }
    }
    
    /* return NULL di ujung array */
    karakter[array] = '\0';
}

bool cekNama(char namaFile[30])
{
	/*  --- Kamus Data --- */
	char cwd[PATH_MAX]; // Current Work Directory, PATH_MAX : 260
    struct dirent *d; // variable record untuk operasi directory
    DIR *dr; // variable record yang merepresentasikan directory stream, stream : penghubung 
    
    /* ---  Algoritma --- */
    getcwd(cwd, sizeof(cwd));  // prosedur untuk mengambil current work directory 
    dr = opendir(cwd); // opendir : fungsi untuk membuka direcory, dr menampung addresnya
    
	/* Jika Directory Tidak ada */
	if(dr!=NULL) 
    {
    	/* Membaca isi directory  satu persatu dengan readdir */
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
        	/* Mengambil file yang hanya berekstensi .txt */
        	if(txt_extension(d->d_name))
			{
				
				/* Membandinkan dengan nama yang diketik, jika sama return false */
				if(!strcmp(namaFile,d->d_name))
				{
					return false;
				}
			}
        }
        closedir(dr); // tutup directory
    }
    else
    {
    	printf("Directory tidak ada");
	}
	return true;
}

void save(list *L)
{
	/* --- Kamus Data --- */
	char namaFile[30], ch; // variable untuk menampung nama file
	address P; // variable untuk menampung address
	FILE *file; // variable file
	bool available = true; // validator
	
	/* --- Algoritma ---*/
	while(1)
	{		
		system("cls"); // clear screen 
		
		tampil_list(&(*L)); // Memanggil modul tampilkan list
		
		gotoxy(28,2);
		printf("Nama file : ");
		barMenu();
		
		gotoxy(28,14);
		inputNamaFile(namaFile); // prosedur untuk input nama
		strcat(namaFile,".txt"); // menyambungkan string
		
		available = cekNama(namaFile); // modul untuk melakukan pengecekan terhadap nama file
		
		/* Jika nama file boleh dipakai */
		if(available)
		{
			file = fopen(namaFile, "w"); // open file mode overwrite
			
			P = Next(Head(*L));
			while(P != NULL)
			{	
				if(Info(P) == NULL)
				{
					fprintf(file, "%c", '\n'); // tulis list ke file
				}
				
				else
				{
					fprintf(file, "%c", Info(P)); // tulis list ke file
				}
				P = Next(P);
			}
			fclose(file); // tutup file
			break;
		}
		
		/* Jika Nama File tidak boleh Dipakai */
		else
		{
			system("cls");
			
			tampil_list(&(*L));
			
			gotoxy(28,2);
			printf("Nama file : ");
			
			gotoxy(28,14);
			printf("Nama File tidak tersedia");
			barMenu();
			getch();
		}
	}
}

void saveModify(list *L, char namaFile[30])
{
	/* --- Kamus Data --- */
	address P; // variable untuk menampung address
	FILE *file; // variable file
	
	/* --- Algoritma -- */
	while(1)
	{		
		tampil_list(&(*L)); // menampilkan list
		
		file = fopen(namaFile, "w"); // membuka file dengan mode overwrite
		
		P = Next(Head(*L));
		while(P != NULL)
		{	
			if(Info(P) == NULL)
			{
				fprintf(file, "%c", '\n'); // menulis ke file 
			}
			
			else
			{
				fprintf(file, "%c", Info(P)); // menulis ke file
			}
			P = Next(P);
		}
		fclose(file);
		
		barMenu(); // menampilkan bar menu kembali
		gotoxy(28,2);
		printf("File berhasil disimpan");
		getch();
		
		break;
	}
}

void modify(list *L)
{
	/* --- Kamus Data --- */
	bool fileTersedia = false; // variable untuk memvalidasi keberadaan fille
	int baris = 0; // baris mula-mula
	int kolom = 0; // kolom mula-mula
	char namaFile[30]; // variable untuk menampung nama file 
	bool validasi_file = true;
	
	gotoxy(28,2);
	printf("Nama file : ");
	barMenu(); // menampulkan bar khusus untuk proses input namaFile
	
	gotoxy(28,14);
	inputNamaFile(namaFile); // modul untuk memasukkan nama file
	strcat(namaFile,".txt"); // fungsi untuk menyambungkan nama yang sudah di input dengan .txt
	
	fileTersedia = fileToList(&(*L), &baris, &kolom, fileTersedia, namaFile); // return value bool/false
	
	/* Jika File tersedia */
	if(fileTersedia)
	{
		/* Modul Input keyboard khsus modify */
		input_keyboard(&(*L), &baris, &kolom, namaFile, validasi_file);
	}
}

void duplicate()  /* -- referensi : https://www.youtube.com/watch?v=ceODxfZWZIo -- */
{	
	char kar, read[25], copy[25];
	bool availableAfter = true;
	bool availableBefore = true;
	FILE *baca, *salin;
	gotoxy(28,2);
	printf("nama file :"); 
	box(1,27,118,29);
	gotoxy(28,14);
	inputNamaFile(read);
	strcat(read,".txt");
	
	availableBefore = cekNama(read);
	if(availableBefore == true){
		//remove(copy, ".txt");
		gotoxy(28,2);
		printf("File tidak tersedia!");
		box(1,27,118,29);
		getch();
		return;
	}
	baca = fopen(read, "r");
	
	gotoxy(28,2);
	printf("                                            "); //fflush(stdin);
	gotoxy(28,2);
	printf("nama file baru :"); //fflush(stdin);
	box(1,27,118,29);
	gotoxy(28,18);
	
	inputNamaFile(copy);
	strcat(copy,".txt"); //fflush(stdin);
	availableAfter = cekNama(copy);
	
	//cek file ada atau ngga//
	if(baca == NULL || availableAfter == false){
		//remove(copy, ".txt");
		gotoxy(28,2);
		printf("Nama file tidak tersedia!");
		box(1,27,118,29);
		getch();
		return;
	}
	
	salin = fopen(copy, "w");
	while((kar=fgetc(baca))!=EOF)
	fputc(kar,salin);
	
	fclose(baca);
	fclose(salin);
	
	if(fputc(kar,salin)){
		gotoxy(28,2);
		printf("berhasil di duplicate");
		box(1,27,118,29);
	}else{
		gotoxy(28,2);
		printf("gagal duplicate");
		box(1,27,118,29);
	}
	getch();
}

/*modul delete file*/
int removeFile(char nama_file_temp[30]) {
    system("cls");
    if (remove(nama_file_temp) == 0) {
        return true;
    } else {
        return false;
    }
}

void deleteFile(){
	char namaFile[30];
    bool statusFile;
    /* Input nama file lama yang akan dihapus */
    printf("Masukkan nama file yang akan dihapus: ");
    scanf("%s", namaFile);
    strcat(namaFile,".txt");
    
    /* Proses menghapus file*/
    statusFile = removeFile(namaFile);
    if (statusFile == true){
        printf("SUCCESS : %s berhasil dihapus\n", namaFile);
    } else  {
        printf("ERROR : %s gagal dihapus\n", namaFile);
    }
    
}

/*modul rename file*/
void renameFile(){
    char oldName[25], newName[25];

    /* Input nama file lama dan nama file baru */
    printf("Masukan nama file yang akan diubah : ");
    scanf("%s", oldName);
    strcat(oldName,".txt");
    
    printf("masukan nama file baru : ");
    scanf("%s", newName);
    strcat(newName,".txt");


    /* mengganti nama file lama menjadi nama file baru */
    if (rename(oldName, newName) == 0)
    {
        printf("File berhasil diganti namanya.\n");
    }
    else
    {
        printf("Nama file tidak dapat dirunah. Silakan periksa file yang anda miliki.\n");
    }

}

//modul untuk hitung kata
int hitungKata()
{
	FILE *fp;
    int count = 1;
    char filename[100];
    char c, ch;

    printf("Masukkan nama file: ");
    scanf("%s", filename);
    strcat(filename,".txt");

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File %s tidak tersedia", filename);
        printf("\n\n");
		system("pause");
		return 1;
    }
    
    //tampilkan isi file
    puts("\nISI FILE ASLI :\n");
    while (fp) {
        	ch = fgetc(fp);
       		if (ch == EOF) {
            	break;
        	}
        	printf("%c", ch);
    	}	
			printf("\n\n");
			fclose(fp);
			
	fp = fopen(filename, "r");
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == ' ' || c == '\n')
            count = count + 1;

    fclose(fp);
    printf("------------------------------------------\n");
    printf("Jumlah kata pada file %s adalah %d  ", filename, count);
	printf("\n\n");
    //return 0;
    system("pause");
}

//modul find and replace
int finrep() 	/* -- referensi : http://see-programming.blogspot.com/2013/07/c-program-to-replace-word-in-file.html */
{
        FILE *fp1, *fp2;
        char word[MAX], fname[MAX], ch;
        char string[MAX], replace[MAX];
        char temp[] = "temp.txt", *ptr1, *ptr2;

        /* get the input file from the user */
        printf("Masukkan nama file:");
        fgets(fname, MAX, stdin);
        fname[strlen(fname) - 1] = '\0';
        strcat(fname,".txt");
        
        /* open input file in read mode */
        fp1 = fopen(fname, "r");

        /* error handling */
        
        if (!fp1) {
                printf("File tidak tersedia!!\n");
                system("pause");
                return 0;
        }

        /* open temporary file in write mode */
        fp2 = fopen(temp, "w");

        /* error handling */
        if (!fp2) {
                printf("Tidak bisa membuka temporary file!!\n");
                return 0;
        }
        
        
 		// displaying file contents
        puts("ISI FILE ASLI :\n");
    	while (1) {
        	ch = fgetc(fp1);
       		if (ch == EOF) {
            	break;
        	}
        	printf("%c", ch);
    	}	
			printf("\n\n");
			fclose(fp1);
        
        
		fp1 = fopen(fname, "r");
        /* get the word to delete from the user */
        printf("Masukkan kata yang ingin dicari:");
        scanf("%s", word);

        /* get the word to replace */
        printf("Masukkan kata untuk mereplace:");
        scanf("%s", replace);

        

        /* delete the given word from the file */
        while (!feof(fp1)) {
                strcpy(string, "\0");
                /* read line by line from the input file */
                fgets(string, MAX, fp1);

                /*
                 * check whether the word to delete is
                 * present in the current scanned line
                 */
                if (strstr(string, word)) {
                        ptr2 = string;
                        while (ptr1 = strstr(ptr2, word)) {
                                /*
                                 * letters present before
                                 * before the word to be replaced
                                 */
                                while (ptr2 != ptr1) {
                                        fputc(*ptr2, fp2);
                                        ptr2++;
                                }
                                /* skip the word to be replaced */
                                ptr1 = ptr1 + strlen(word);
                                fprintf(fp2, "%s", replace);
                                ptr2 = ptr1;
                        }

                        /* characters present after the word to be replaced */
                        while (*ptr2 != '\0') {
                                fputc(*ptr2, fp2);
                                ptr2++;
                        }
                } else {
                        /*
                         * current scanned line doesn't 
                         * have the word that need to be replaced
                         */
                        fputs(string, fp2);
                }
        }

        /* close the opened files */
        fclose(fp1);
        fclose(fp2);

        /* remove the input file */
        remove(fname);
        /* rename temporary file name to input file name */
        rename(temp, fname);
        
        //buka hasil file yg udah di replace
        puts("\n\nISI FILE YANG SUDAH DIUBAH :\n\n");
        fp1 = fopen(fname, "r");
        while (1) {
        	ch = fgetc(fp1);
       		if (ch == EOF) {
            	break;
        	}
        	printf("%c", ch);
    	}	
			printf("\n\n");
			fclose(fp1);
        system("pause");
  }
