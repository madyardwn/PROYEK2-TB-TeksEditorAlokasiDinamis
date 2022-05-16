#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "design.h"
#include "input.h"
#include "file.h"

void warna(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void box(int y1,int x1,int y2,int x2) 	// x baris, y kolom
{										
   int i;
   for(i=y1;i<=y2;i++)
    {
		gotoxy(x1,i);
		printf("%c",196);
		gotoxy(x2,i);
		printf("%c",196);
    }
   	for(i=x1;i<=x2;i++)
    {
		gotoxy(i,y1);
		printf("%c",179);
		gotoxy(i,y2);
		printf("%c",179);
    }
	gotoxy(x1,y1);
	printf("%c",218);
	gotoxy(x2,y1);
	printf("%c",192);
	gotoxy(x1,y2);
	printf("%c",191);
	gotoxy(x2,y2);
	printf("%c",217);
}

void creadit()
{
	gotoxy(2,93);
	printf(" Created by : \n");
	gotoxy(3,93);
	printf(" - Achmadya    \n");
	gotoxy(4,93);
	printf(" - Aurell      \n");
	gotoxy(5,93);
	printf(" - Evic        \n");
	gotoxy(6,93);
	printf(" - Fahmi       \n");
	gotoxy(7,93);
	printf(" - Ibrahim     \n");
	box(92,1,118,26);
}

void displayLogo()
{
	warna(9);
	printf("                                                                                           \n");
	printf("                                                                                           \n");
	printf("   ||||       |||   |||      |||  |||     |||  |||||||||                |||   ||||||||||   \n"); 
	printf("   ||||||     |||   |||      |||   |||   |||      |||                   |||   |||          \n");
	printf("   ||| |||    |||   |||      |||    ||| |||       |||                   |||   |||          \n");
	printf("   |||  |||   |||   |||      |||     |||||        |||                   |||   |||          \n");
	printf("   |||   |||  |||   |||      |||      |||         |||                   |||   ||||||||||   \n");
	printf("   |||    ||| |||   |||      |||     |||||        |||           |||     |||          |||   \n");
	printf("   |||     ||||||   |||      |||    ||| |||       |||           |||     |||          |||   \n");
	printf("   |||      |||||   |||      |||   |||   |||      |||           |||     |||          |||   \n");
	printf("   |||       ||||   ||||||||||||  |||     |||     |||     |||   |||||||||||   ||||||||||   \n");
	printf(" 																						   \n");
	warna(7);
	printf("                                       TEXT EDITOR                                     	   \n");
	printf("                                                                                           \n");
	gotoxy(16,3);
	printf("                            -- Shortcut or Arrow Key --                                    \n");
	gotoxy(28,2);
	printf("Welcome to our text editor");
	box(2,12,89,14);
	box(2,15,89,25);
	box(1,1,90,26);
}

void bar()
{
	box(1,27,118,29);
}

bool selectionMenu(list *L)
{
	int opsiWarna[3] = {7,7,7};
	int pilihan = 1;
	char ch;
	
	while(1)
	{
		/* Selection */
		gotoxy(18,5);
		warna(opsiWarna[0]);
		printf("	[I] Insert Text\n");
		
		gotoxy(19,5);
		warna(opsiWarna[1]);
		printf("	[O] Open Recent File\n");
		
		gotoxy(20,5);
		warna(opsiWarna[2]);
		printf("	[Q] Quit Text Editor");
		
		ch = getch();
		if(ch == 72)
		{
			if(pilihan == 1)
			{
				continue;
			}
			
			else
			{
				pilihan--;
			}
		}
		
		if(ch == 80)
		{
			if(pilihan == 3)
			{
				continue;
			}
			else
			{
				pilihan++;
			}
		}
		
		if(ch == 13)
		{
			if(pilihan == 1)
			{
				int baris = 0, kolom = 0;
				
				system("cls");
				
				warna(7);
				input_keyboard(&(*L), &baris, &kolom);
				return true;
			}
			if(pilihan == 2)
			{
				system("cls");
				
				warna(7);
				ListFile(&(*L));
				modify(&(*L));
				return true;
			}
			if(pilihan == 3)
			{
				system("cls");
				
				warna(7);
				return false;
			}
		}else 
		
		/* Shortcut */
		if(ch == 'i')
		{
			int baris = 0, kolom = 0;
			
			system("cls");
			
			warna(7);
			input_keyboard(&(*L), &baris, &kolom);
			return true;
		}else 
		
		if(ch == 'o')
		{
			system("cls");
			
			warna(7);
			ListFile(&(*L));
			modify(&(*L));
			return true;
		}else 
		
		if(ch == 'q')
		{
			system("cls");
			
			warna(7);
			return false;
		}
		opsiWarna[0] = 7;
		opsiWarna[1] = 7;
		opsiWarna[2] = 7;
		if(pilihan == 1)
		{
			opsiWarna[0] = 13;
		}
		
		if(pilihan == 2)
		{
			opsiWarna[1] = 13;
		}
		
		if(pilihan == 3)
		{
			opsiWarna[2] = 13;
		}
	}
}

void menu()
{
	system("cls");
	displayLogo();
	creadit();
	bar();
}

void loading()
{
	int i,j;
	
	system("cls");
	printf("\n");
	printf("\t=========================================================================================  \n\n");
	printf("\t  ||||       |||   |||      |||  |||     |||  |||||||||                |||   ||||||||||    \n"); 
	printf("\t  ||||||     |||   |||      |||   |||   |||      |||                   |||   |||           \n");
	printf("\t  ||| |||    |||   |||      |||    ||| |||       |||                   |||   |||           \n");
	printf("\t  |||  |||   |||   |||      |||     |||||        |||                   |||   |||           \n");
	printf("\t  |||   |||  |||   |||      |||      |||         |||                   |||   ||||||||||    \n");
	printf("\t  |||    ||| |||   |||      |||     |||||        |||           |||     |||          |||    \n");
	printf("\t  |||     ||||||   |||      |||    ||| |||       |||           |||     |||          |||    \n");
	printf("\t  |||      |||||   |||      |||   |||   |||      |||           |||     |||          |||    \n");
	printf("\t  |||       ||||   ||||||||||||  |||     |||     |||     |||   |||||||||||   ||||||||||    \n\n");
	printf("\t========================================================================================== \n");
	printf("\t=====                                   TEXT EDITOR                                    === \n");
	printf("\t========================================================================================== \n\n");
	printf("\t                                       PLEASE WAIT . . .                                   \n\n");
	Sleep(800);
	printf("\t                                         >>> 3 <<<                                         \n\n");
	Sleep(1000);
	printf("\t                                         >>> 2 <<<                                         \n\n");
	Sleep(1000);
	printf("\t                                         >>> 1 <<<                                         \n\n");
	Sleep(1000);
	system("cls");
}

void border()
{
	int brs = MAX_ROWS;
	int klm = MAX_COLUMNS;
	
	// Margin Kanan
	for(brs = 0; brs < MAX_ROWS; brs++)
	{	
		gotoxy(brs,klm);
		printf(" |");	
	}
	
	// Margin Bawah
	for(klm = 0; klm <= MAX_COLUMNS; klm++)
	{	
		gotoxy(brs,klm);
		printf("-");	
	}
	printf("-");
	gotoxy(0,0);	
}

void gotoxy(int baris,int kolom)
{
	COORD coord;
	
    coord.X = kolom;
    coord.Y = baris;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void tampil_list(list L)
{	
	system("cls");
	address P;
	P = Next(Head(L));
	
	while(P != NULL)
	{
		printf("%c", Info(P));
		if (Info(P) == NULL)
		{
			printf("\n");
		}
		P = Next(P);
	}
}
