#include <stdio.h>
#include <windows.h>
#include <dirent.h>
#include "conio.h"
#include "input.h"
#include "file.h"
#include "design.h"

bool txt_extension(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

bool fileToList(list *L, int *baris, int *kolom, bool fileTersedia)
{
	FILE *file;
	address P;
	char namaFile[30];
	char ch;
	bool cek;
	
	gotoxy(28,2);
	printf("Nama file : ");
	barMenu();
	gotoxy(28,14);
	inputNamaFile(namaFile);
	strcat(namaFile,".txt");
	file = fopen(namaFile, "r");
	
	if(file == NULL)
	{
		gotoxy(28,14);
		printf("File tidak tersedia");
		barMenu();
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
	char pilihFile[30];
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
	char namaFile[30], ch;
	address P;
	FILE *file;
	bool available = true;
	
	while(1)
	{		
		system("cls");
		tampil_list(&(*L));
		gotoxy(28,2);
		printf("Nama file : ");
		barMenu();
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
			barMenu();
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
