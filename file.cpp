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
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

bool fileToList(list *L, int *baris, int *kolom, bool fileTersedia)
{
	FILE *file;
	address P;
	char namaFile[25];
	char ch;
	bool cek;
	
	gotoxy(28,2);
	printf("Nama file : ");
	bar();
	gotoxy(28,14);
	inputNamaFile(namaFile);
	strcat(namaFile,".txt");
	file = fopen(namaFile, "r");
	
	if(file == NULL)
	{
		gotoxy(28,14);
		printf("File tidak tersedia");
		bar();
		getch();
		cek = false;
	}
	
	else 
	{
		gotoxy(0,0);
		system("cls");
		while(!feof(file))
		{
			ch = fgetc(file);
			if (ch == -1)
			{
				continue;
			}
			
			if(ch == '\n')
			{
				enter(*(&L), NULL, *(&baris), *(&kolom));
			}
			
			else
			{
				P = Alokasi(ch);
				normal_input(*(&L), P, &(*baris), &(*kolom));
			}
		}
		cek = true;
		fclose(file);
	}
	
	return cek;
}

void ListFile(list *L)
{
	system("cls");
	int jumlah = 1;
	char cwd[PATH_MAX];
	char pilihFile[25];
    struct dirent *d;
    DIR *dr;
    
    getcwd(cwd, sizeof(cwd));
    dr = opendir(cwd);
    if(dr!=NULL)
    {
    	printf("Daftar File : \n");
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
        	if(txt_extension(d->d_name))
			{
        		printf("%d. %s \n", jumlah, d->d_name);
        		jumlah++;
			}
        }
        closedir(dr);
    }
    else
	{
		printf("\nERROR: Folder tidak ditemukan!");
	}
}

void inputNamaFile(char karakter[25])
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
        	if(strlen(karakter)>=24)
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

bool cekNama(char namaFile[25])
{
	char cwd[PATH_MAX];
    struct dirent *d;
    DIR *dr;
    
    getcwd(cwd, sizeof(cwd));
    dr = opendir(cwd);
    if(dr!=NULL)
    {
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
        	if(txt_extension(d->d_name))
			{
				if(!strcmp(namaFile,d->d_name))
				{
					
					return false;
				}
			}
        }
        closedir(dr);
    }
    else
    {
    	printf("Directory tidak ada");
	}
	return true;
}

void save(list *L)
{
	char namaFile[25], ch;
	address P;
	FILE *file;
	bool available = true;
	
	while(1)
	{		
		system("cls");
		tampil_list(&(*L));
		gotoxy(28,2);
		printf("Nama file : ");
		bar();
		gotoxy(28,14);
		inputNamaFile(namaFile);
		strcat(namaFile,".txt");
		available = cekNama(namaFile);
		
		if(available)
		{
			file = fopen(namaFile, "w");
			
			P = Next(Head(*L));
			while(P != NULL)
			{	
				if(Info(P) == NULL)
				{
					fprintf(file, "%c", '\n');
				}
				
				else
				{
					fprintf(file, "%c", Info(P));
				}
				P = Next(P);
			}
			fclose(file);
			break;
		}
		
		else
		{
			system("cls");
			tampil_list(&(*L));
			gotoxy(28,2);
			printf("Nama file : ");
			gotoxy(28,14);
			printf("Nama File tidak tersedia");
			bar();
			getch();
		}
	}
}

void modify(list *L)
{
	bool fileTersedia = false;
	int baris = 0;
	int kolom = 0;
	
	fileTersedia = fileToList(&(*L), &baris, &kolom, fileTersedia);
	if(fileTersedia){
		input_keyboard(&(*L), &baris, &kolom);
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
	printf("                                            ");
	gotoxy(28,2);
	printf("nama file baru :");
	box(1,27,118,29);
	gotoxy(28,18);
	
	inputNamaFile(copy);
	strcat(copy,".txt"); //fflush(stdin);
	availableAfter = cekNama(copy);
	
	//cek file ada atau ngga//
	if(baca == NULL || availableAfter == false){
		//remove(copy, ".txt");
		gotoxy(28,2);
		printf("File tidak tersedia!");
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
	system("pause");
}

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
