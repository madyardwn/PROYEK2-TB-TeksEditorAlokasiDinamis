#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "design.h"
#include "input.h"
#include "file.h"
#include "themes.h"

#define WHITE 7
#define LIGHTM 13
#define FIRST_MENU 1
#define LAST_MENU 5
#define UP 72
#define DOWN 80
#define ENTER 13

void warna(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void box(int x1,int y1,int x2,int y2) 	// x kolom, y baris
{										
   int i;
   for(i=x1;i<=x2;i++)
    {
		gotoxy(y1,i);
		printf("%c",196);
		gotoxy(y2,i);
		printf("%c",196);
    }
   	for(i=y1;i<=y2;i++)
    {
		gotoxy(i,x1);
		printf("%c",179);
		gotoxy(i,x2);
		printf("%c",179);
    }
	gotoxy(y1,x1);
	printf("%c",218);
	gotoxy(y2,x1);
	printf("%c",192);
	gotoxy(y1,x2);
	printf("%c",191);
	gotoxy(y2,x2);
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
	warna(WHITE);
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

void barInput(int *baris, int *kolom, int reset)
{
	if(reset)
	{
		box(1,27,118,29);
	}
	gotoxy(28,2);
	printf("SAVE (Ctrl + S) | QUIT/CANCLE (Ctrl + Q)							Baris: %d | Kolom: %d", (*baris)+1, (*kolom)+1); 
}

void barMenu()
{
	box(1,27,118,29);
}
bool selectionMenu(list *L)
{
	/* --- Kamus Data --- */
	int opsiWarna[5] = {WHITE, WHITE, WHITE, WHITE, WHITE}; // Array warna mula-mula
	int pilihan = 1; // penanda posisi
	char ch; // penampung input
	
	/* --- Algoritma --- */
	
	/* Menampilkan Menu */
	menu();
	
	/* Loop untuk menentukan posisi dengan tanda berupa warna */
	while(1)
	{
		/* -- Selection -- */
		gotoxy(18,5);
		warna(opsiWarna[0]);
		printf("	[I] Insert Text\n");
		
		gotoxy(19,5);
		warna(opsiWarna[1]);
		printf("	[O] Open Recent File\n");
		
		gotoxy(20,5);
		warna(opsiWarna[2]);
		printf("	[D] Duplicate File");
		
		gotoxy(21,5);
		warna(opsiWarna[3]);
		printf("	[T] Theme Text Editor");
		
		gotoxy(22,5);
		warna(opsiWarna[4]);
		printf("	[Q] Quit Text Editor");
		
		
		/* - Proses Insert Arrow - */
		ch = getch();
		
		/* Tombol UP */
		if(ch == UP)
		{
			/* Move ke menu terakhir jika sudah mentok di paling atas */
			if(pilihan == FIRST_MENU)
			{
				pilihan = LAST_MENU;
			}
			
			/* Move ke atas satu baris */
			else
			{
				pilihan--;
			}
		}
		
		/* Tombol Bawah */
		if(ch == DOWN)
		{
			/* Move ke menu awal jika sudah mentok di paling bawah */
			if(pilihan == LAST_MENU)
			{
				pilihan = FIRST_MENU;
			}
			
			/* Move satu baris ke bawah */
			else
			{
				pilihan++;
			}
		}
		
		/* Tombol Enter : untuk accept pilihan*/
		if(ch == ENTER)
		{
			/* Menulis Tulisan */
			if(pilihan == 1)
			{
				/*Variable Local*/
				int baris = 0, kolom = 0;
				
				system("cls"); // Clear Screen
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				input_keyboard(&(*L), &baris, &kolom); // Modul Insert --> Save File or Exit
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Modifikasi tulisan yang sudah tersimpan */
			if(pilihan == 2)
			{
				system("cls"); // Clear Screen
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				ListFile(&(*L)); // Menampilkan daftar file
				modify(&(*L)); // Melakukan modifikasi terhadap file yang dibuka
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Menduplikasi file yang sudah tersimpan */
			if(pilihan == 3)
			{
				system("cls"); // Clear Screen 
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				ListFile(&(*L)); // Menampilkan daftar file 
				duplicate(); // Memilih kemudian menduplikasi file
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Mengganti Menu */
			if(pilihan == 4)
			{
				system("cls"); // Clear Screen 

				warna(WHITE); // Mengembalikan warna menjadi normal 
				menu_themes(); // Masuk ke menu theme
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Exit */
			if(pilihan == 5)
			{
				system("cls"); // Clear Screen
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				
				return false; // Return False : untuk berhenti menampilkan Menu kemudia Exit
			}
			
		}else 
		
		/*  -- Shortcut -- */
		
		/* Tombol I : Insert */
		if(ch == 'i' || ch == 'I')
		{
			/* Variable Local */
			int baris = 0, kolom = 0;
			
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			input_keyboard(&(*L), &baris, &kolom); // Modul Insert --> Save File or Exit
			
			return true; // Return True untuk menampilkan menu kembali
		}else 
		
		/* Tombol O : Open */
		if(ch == 'o' || ch == 'O')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			ListFile(&(*L)); // Menampilkan daftar file
			modify(&(*L)); // Melakukan modifikasi terhadap file yang dibuka
			
			return true; // Return True untuk menampilkan menu kembali
		}else
		
		/* Tombol D : Duplikasi */
		if(ch == 'd' || ch == 'D')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			ListFile(&(*L)); // Menampilkan daftar file
			duplicate(); // Memilih kemudian menduplikasi file
			
			return true; // Return True untuk menampilkan menu kembali
		}else 
		
		/* Tombol T : Theme */
		if(ch == 't' || ch == 'T')
		{
			system("cls"); // Clear Screen
			warna(WHITE); // Mengembalikan warna menjadi normal 
			menu_themes(); // Masuk ke menu theme
			
			return true; // Return True untuk menampilkan menu kembali
		}else
		
		/* Tombol Q : Quit */
		if(ch == 'q' || ch == 'Q')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			
			return false; // Return True untuk menampilkan menu kembali
		}
		
		/* Restart Warna */
		else
		{
			opsiWarna[0] = WHITE; // Mengembalikan warna menjadi normal 
			opsiWarna[1] = WHITE; // Mengembalikan warna menjadi normal 
			opsiWarna[2] = WHITE; // Mengembalikan warna menjadi normal 
			opsiWarna[3] = WHITE; // Mengembalikan warna menjadi normal 
			opsiWarna[4] = WHITE; // Mengembalikan warna menjadi normal 
			
			/* -- Merubah Warna Sesuai Pilihan --*/
			if(pilihan == 1)
			{
				opsiWarna[0] = LIGHTM;
			}
			
			if(pilihan == 2)
			{
				opsiWarna[1] = LIGHTM;
			}
			
			if(pilihan == 3)
			{
				opsiWarna[2] = LIGHTM;
			}
			
			if(pilihan == 4)
			{
				opsiWarna[3] = LIGHTM;
			}
			
			if(pilihan == 5)
			{
				opsiWarna[4] = LIGHTM;
			}
		}
	}
}

void menu()
{
	system("cls");
	displayLogo();
	creadit();
	barMenu();
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

void tampil_list(list *L)
{	
	system("cls");
	address P;
	P = Next(Head(*L));
	
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

void clear()
{
    /* Origin : https://docs.microsoft.com/en-us/windows/console/clearing-the-screen */
    /* Dengan penyesuaian */
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 1;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hStdout, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}
