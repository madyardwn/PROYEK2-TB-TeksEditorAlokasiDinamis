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
	char namaFile[25];
	char ch;
	
	gotoxy(28,2);
	printf("Nama file : ");
	bar();
	gotoxy(28,14);
	inputNamaFile(namaFile);
	strcat(namaFile,".txt");
	file = fopen(namaFile, "r");
	
	if(file == NULL)
	{
		fclose(file);
		gotoxy(28,14);
		printf("File tidak tersedia");
		bar();
		getch();
		return false;
	}
	
	gotoxy(0,0);
	system("cls");
	while(!feof(file))
	{
		ch = fgetc(file);
		if(ch == -1)
		{
			continue;
		}
		
		else{
			P = Alokasi(ch);
			normal_input(*(&L), P, &(*baris), &(*kolom));
		}
	}
	fclose(file);
	return true;
}

int ListFile(list *L)
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
    return 0;
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
        if(ch == 13 || ch == 10)
		{
            break;
        }

        /* Jika menekan backspace mengahapus karakter */
        else if(ch == 8 || ch == 127)
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
		}
		
		else if (	
					(ch == -32) ||
					!(ch >= 'a' && ch <= 'z') && 
					!(ch >= 'A' && ch <= 'Z')
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

void save(list L)
{
	char namaFile[25], ch;
	address P;
	FILE *file;
	
	P = Next(Head(L));

	gotoxy(28,2);
	printf("Nama file : ");
	bar();
	gotoxy(28,14);
	inputNamaFile(namaFile);
	strcat(namaFile,".txt");
	file = fopen(namaFile, "w");
	while(P != NULL)
	{
		fprintf(file, "%c", Info(P));
		P = Next(P);
	}
	fclose(file);
}

void modify(list *L)
{
	bool fileTersedia = false;
	int baris = 0;
	int kolom = 0;
	
	fileTersedia = fileToList(&(*L), &baris, &kolom, fileTersedia);
	if(fileTersedia == true){
		input_keyboard(&(*L), &baris, &kolom);
	}
}
