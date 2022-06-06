#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "design.h"
#include "input.h"
#include "file.h"

#define WHITE 7
#define LIGHTM 13
#define FIRST_MENU 1
#define LAST_MENU 6
#define UP 72
#define DOWN 80
#define ENTER 13

void warna(int color)
{
	// http://proprogrammershub.blogspot.com/2016/06/how-to-change-color-of-text-in-c.html
	/* Prosedur WINAPI untuk mengganti warna console */
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // meerubah backgound dan foreground
	/*
		- GetStdHandle 				: fungsi untuk membaca STD_OUTPUT_HANDLE
		- STD_OUTPUT_HANDLE 		: standard ouput device, menginisialiasasi buffer konsole yang aktif 
	*/
}

void box(int x1,int y1,int x2,int y2) 	// x kolom, y baris
{						
	/* --- Kamus Data --- */
	int i;
	
	/* --- Algoritma --- */				
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
	warna(9); // modul mengubah warna
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

void barInput(int baris, int kolom, list L, bool pull_mode, bool *status_bar)
{
	// Deklarasi
	int karakter,kata;
	
	// Jumlah Karakter
	karakter = jumlah_karakter(L);
	
	// Jumlah Kata
	kata = jumlah_kata(L);
    
    if (*status_bar == true)
	{
		if (pull_mode == true)
		{
			for(int i=4;i<=7; i++)
			{
				gotoxy(i,0);
				printf("                                                                                                                ");
			}
			
			box(3,9,116,11);
			for(int i=23; i <= 116; i = i+24)
			{
				gotoxy(10,i);		// Tengah
				printf("%c", 179);
				gotoxy(9,i);		// Atas
				printf("%c", 194);
				gotoxy(11,i);		// Bawah
				printf("%c", 193);
			}
			
			gotoxy(10,4);
			printf("                   ");
			gotoxy(10,4);
			warna(11);
			printf("Baris: %d", baris+1);
			
			gotoxy(10,24);	
			printf("                   ");
			gotoxy(10,24);
			warna(11);
			printf("Kolom: %d", kolom+1);
			
			gotoxy(10,48);
			printf("                   ");	
			gotoxy(10,48);
			warna(11);
			printf("Karakter: %d", karakter);
			
			gotoxy(10,72);
			printf("                   ");
			gotoxy(10,72);
			warna(11);
			printf("Kata: %d", kata);
			
			gotoxy(10,96);
			gotoxy(10,96);
			warna(11);
			printf("NuxtJS.Text-Editor");
			warna(7);
		}else{
			gotoxy(5,4);
			printf("                   ");
			gotoxy(5,4);
			warna(11);
			printf("Baris: %d", baris+1);
				
			gotoxy(5,24);
			printf("                   ");
			gotoxy(5,24);
			warna(11);
			printf("Kolom: %d", kolom+1);
				
			gotoxy(5,48);
			printf("                   ");
			gotoxy(5,48);
			warna(11);
			printf("Karakter: %d", karakter);
			
			gotoxy(5,72);
			printf("                   ");
			gotoxy(5,72);
			warna(11);
			printf("Kata: %d", kata);
			
			gotoxy(5,96);
			warna(11);
			printf("NuxtJS.Text-Editor");
			warna(7);
		}	
	}
}

void barMenu()
{
	/* Menampilkan Kotak */
	box(1,27,118,29);
}

bool selectionMenu(list *L)
{
	/* --- Kamus Data --- */
	int opsiWarna[6] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}; // Array warna mula-mula
	int pilihan = 1; // penanda posisi
	char ch; // penampung input
	char namaFile[30]; // untuk nama file
	bool validasi_file = false; // untuk validasi file
	
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
		printf("	[C] Duplicate File");
		
		gotoxy(21,5);
		warna(opsiWarna[3]);
		printf("	[D] Delete File");
		
		gotoxy(22,5);
		warna(opsiWarna[4]);
		printf("	[R] Rename File");
		
		gotoxy(23,5);
		warna(opsiWarna[5]);
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
				input_keyboard(&(*L), &baris, &kolom, namaFile, validasi_file); // Modul Insert --> Save File or Exit
				
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
			
			/* Menghapus file yang sudah tersimpan */
			if(pilihan == 4)
			{
				system("cls"); // Clear Screen 
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				ListFile(&(*L)); // Menampilkan daftar file 
				deleteFile(); // Memilih kemudian menghapus file
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Mengganti nama file */
			if(pilihan == 5)
			{
				system("cls"); // Clear Screen 
				
				warna(WHITE); // Mengembalikan warna menjadi normal 
				ListFile(&(*L)); // Menampilkan daftar file 
				renameFile(); // Memilih kemudian mengganti nama file
				
				return true; // Return True : untuk menampilkan menu kembali
			}
			
			/* Exit */
			if(pilihan == 6)
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
			input_keyboard(&(*L), &baris, &kolom, namaFile, validasi_file); // Modul Insert --> Save File or Exit
			
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
		
		/* Tombol C : Duplikasi */
		if(ch == 'c' || ch == 'C')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			ListFile(&(*L)); // Menampilkan daftar file
			duplicate(); // Memilih kemudian menduplikasi file
			
			return true; // Return True untuk menampilkan menu kembali
		}else 
		
		/* Tombol  D: Delete File */
		if(ch == 'd' || ch == 'D')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			ListFile(&(*L)); // Menampilkan daftar file
			deleteFile(); // Memilih kemudian menghapus file
			
			return true; // Return True untuk menampilkan menu kembali
		}else 
		
		/* Tombol R : Rename */
		if(ch == 'r' || ch == 'R')
		{
			system("cls"); // Clear Screen
			
			warna(WHITE); // Mengembalikan warna menjadi normal 
			ListFile(&(*L)); // Menampilkan daftar file
			renameFile(); // Memilih kemudian mengganti nama file
			
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
			opsiWarna[5] = WHITE; // Mengembalikan warna menjadi normal 
			
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
			
			if(pilihan == 6)
			{
				opsiWarna[5] = LIGHTM;
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

int jumlah_karakter(list L)
{
	int count_char = 0;
	
	address P;
	P = Head(L);
	while (P != NULL)
	{
		if (Info(P) != NULL and Info(P) != 32)
		{
			count_char++;
		}
		P = Next(P);
	}

	return count_char;
}

int jumlah_kata(list L)
{
	int count_word = 0;
	
	address P;
	P = Head(L);
	while (P != NULL)
	{
		if (Info(P) == NULL)
		{
			if (Next(P) != NULL)
			{
				if (Info(Next(P)) != NULL)
				{
					count_word++;
				}
			}
		}
		
		if (Info(P) == 32)
		{
			if (Next(P) != NULL)
			{
				if (Info(Next(P)) != 32)
				{
					count_word++;
				}
			}
		}
		
		P = Next(P);
	}
	
	return count_word;
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

void SetWindow(int *tinggi_max, int *lebar_max, int baris, int kolom, list L)
{
	COORD coord;
	HANDLE Handle;
	SMALL_RECT Rect;
	int max_kolom = 0;
	int max_baris = 0;
	
	address P;
	
	P = Head(L);
	while (P != NULL)
	{
		max_kolom = max_kolom + 1;
		if (*lebar_max < max_kolom)
		{
			*lebar_max = max_kolom;
		}
		
		if (Info(P) == NULL)
		{
			max_baris = max_baris + 1;
			max_kolom = 0;
		}
		if (*tinggi_max < max_baris)
		{
			*tinggi_max = max_baris;
		}
		
		P = Next(P);
	}
	
//	// Size Height Window
//	if (*tinggi_max < baris)
//	{
//		*tinggi_max = baris;
//	}
//	
//	// Size Window X
//	if (*lebar_max < kolom)
//	{
//		*lebar_max = kolom;
//	}
	
	coord.Y = *tinggi_max+1;
	coord.X = *lebar_max+2;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleScreenBufferSize(Handle,coord);
}

void gotoxy(int baris,int kolom)
{
	COORD coord;
	HANDLE handle;
	
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
    coord.X = kolom;
    coord.Y = baris;
    SetConsoleCursorPosition(handle,coord);
}

void GetWindowSize(int *height, int *width)
{
	// Sumber
	// https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
	
	// Deklarasi
	HANDLE handle;
	CONSOLE_SCREEN_BUFFER_INFO size;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int column, row;
	
	// Ambil Informasi Screen Buffer
	GetConsoleScreenBufferInfo(handle,&size);
	// Ambil ukuran maksimal tinggi (y) dan lebar (x)
	*width = size.dwSize.X;
    *height = size.dwSize.Y;
}

void Pull_Down_Menu(int *baris, int *kolom, list *L, bool *status_bar)
{
	int pilihan = 1;	    			// Untuk Memilih Pilihan Kategori Pull
	int pilihan_fitur = 1; 				// Untuk Memilih Pilihan Fitur pada Pull
	char ch;							// Untuk Input Karakter
	int warna_teks[5] = {7,7,7,7,7}; 	// Untuk memberikan warna
	bool status = false;				// Untuk mengecek apakah pull down menu sedang terjadi atau tidak
	bool pull_mode = false; 			// Sebagai penanda mode pull down sedang digunakan
		
	// Membuat Menu Dalam Mode Pull Down
	system("cls");
	printf("\e[?25l");	// Menghilangkan Kursor
	pull_mode = true;
	gotoxy(0,0);
	printf("PULL DOWN MODE : ON");
	barInput(*baris, *kolom, *L, pull_mode, &(*status_bar));
	box(3,1,116,3);
	for(int i=23; i <= 116; i = i+24)
	{
		gotoxy(2,i);		// Tengah
		printf("%c", 179);
		gotoxy(1,i);		// Atas
		printf("%c", 194);
		gotoxy(3,i);		// Bawah
		printf("%c", 193);
	}
	while(pull_mode == true)
	{	
		// Membuat Border
		gotoxy(0,0);
		printf("PULL DOWN MODE : ON");
		
		box(3,1,116,3);
		for(int i=23; i <= 116; i = i+24)
		{
			gotoxy(2,i);		// Tengah
			printf("%c", 179);
			gotoxy(1,i);		// Atas
			printf("%c", 194);
			gotoxy(3,i);		// Bawah
			printf("%c", 193);
		}

		gotoxy(2,12);
		warna(warna_teks[0]);
		printf("FILE");
			
		gotoxy(2,33);
		warna(warna_teks[1]);
		printf("EDIT");
			
		gotoxy(2,56);
		warna(warna_teks[2]);
		printf("FORMAT");
		
		gotoxy(2,81);
		warna(warna_teks[3]);
		printf("VIEW");
		
		gotoxy(2,104);
		warna(warna_teks[4]);
		printf("HELP");
		warna(7);
		
		// Membuat Status Bar
		barInput(*baris,*kolom,*L,pull_mode,&(*status_bar)); 
		
		// Membaca Input Keyboard
		fflush(stdin);
		ch = getch();
		
		// Esc
		if (ch == 27)
		{
			pull_mode = false;
		}
		
		// Arrow
		if (ch == -32)
		{
			ch = getch();
			// Right arrow
			if (ch == 77)
			{
				if (pilihan < 5)
				{
					pilihan++;
				}else{
					pilihan = pilihan - 4;
				}
			}
			
			// Left arrow
			if (ch == 75)
			{
				if (pilihan > 1)
				{
					pilihan--;
				}else{
					pilihan = 5;
				}
			}
			
			// Perubahan warna pada fitur yang dipilih
			for (int i=0; i < 5; i++)
			{
				warna_teks[i] = 7;
			}
			warna_teks[pilihan-1] = 10;
		}
		
		// Enter
		if (ch == 13)
		{
			switch (pilihan)
			{
				case 1:
				{
					Create_Border(pilihan,&status,warna_teks);
					Feature_Selection(&(*L),pilihan,&pull_mode,&(*baris),&(*kolom), &(*status_bar));
					break;
				}
				
				case 2:
				{
					Create_Border(pilihan,&status,warna_teks);
					Feature_Selection(&(*L),pilihan,&pull_mode,&(*baris),&(*kolom), &(*status_bar));
					break;
				}
				
				case 3:
				{
					Create_Border(pilihan,&status,warna_teks);
					Feature_Selection(&(*L),pilihan,&pull_mode,&(*baris),&(*kolom), &(*status_bar));
					break;
				}
				
				case 4:
				{
					Create_Border(pilihan,&status,warna_teks);
					Feature_Selection(&(*L),pilihan,&pull_mode,&(*baris),&(*kolom), &(*status_bar));
					break;
				}
				
				case 5:
				{
					Create_Border(pilihan,&status,warna_teks);
					Feature_Selection(&(*L),pilihan,&pull_mode,&(*baris),&(*kolom), &(*status_bar));
					break;
				}
				
				default:
				{
					break;
				}
			}
		}	
	}	
}

void Create_Border(int pilihan, bool *status, int warna_teks[])
{
	switch(pilihan)
	{
		case 1:
		{
			if (*status == false)
			{				
				gotoxy(3,3);
				printf("%c", 195);
				gotoxy(3,23);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,3);
					printf("%c", 179);
					gotoxy(i,23);
					printf("%c", 179);	
				}
				gotoxy(8,3);
				printf("%c", 192);
				gotoxy(8,23);
				printf("%c", 217);
				for(int i=4; i<=22; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				*status = true;	
			}else{
				//Clear Screen Sebagian
				for(int i=0; i <= 5; i++)
				{
					gotoxy(i,0);
					printf("                                                                                                                                  ");
				}
				
				gotoxy(0,0);
				printf("PULL DOWN MODE : ON");
				
				// Membuat Border
				box(3,1,116,3);
				for(int i=23; i <= 116; i = i+24)
				{
					gotoxy(2,i);		// Tengah
					printf("%c", 179);
					gotoxy(1,i);		// Atas
					printf("%c", 194);
					gotoxy(3,i);		// Bawah
					printf("%c", 193);
				}
				
				gotoxy(3,3);
				printf("%c", 195);
				gotoxy(3,23);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,3);
					printf("%c", 179);
					gotoxy(i,23);
					printf("%c", 179);	
				}
				gotoxy(8,3);
				printf("%c", 192);
				gotoxy(8,23);
				printf("%c", 217);
				for(int i=4; i<=22; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				
				gotoxy(2,12);
				warna(warna_teks[0]);
				printf("FILE");
					
				gotoxy(2,33);
				warna(warna_teks[1]);
				printf("EDIT");
					
				gotoxy(2,56);
				warna(warna_teks[2]);
				printf("FORMAT");
				
				gotoxy(2,81);
				warna(warna_teks[3]);
				printf("VIEW");
				
				gotoxy(2,104);
				warna(warna_teks[4]);
				printf("HELP");
				warna(7);
				*status = false;
			}
			break;
		}
		
		case 2:
		{
			if (*status == false)
			{
				gotoxy(3,23);
				printf("%c", 197);
				gotoxy(3,47);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,23);
					printf("%c", 179);
					gotoxy(i,47);
					printf("%c", 179);	
				}
				gotoxy(8,23);
				printf("%c", 192);
				gotoxy(8,47);
				printf("%c", 217);
				for(int i=24; i<=46; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				*status = true;
			}else{
				//Clear Screen Sebagian
				for(int i=0; i <= 5; i++)
				{
					gotoxy(i,0);
					printf("                                                                                                                                  ");
				}
				
				gotoxy(0,0);
				printf("PULL DOWN MODE : ON");
				
				box(3,1,116,3);
				for(int i=23; i <= 116; i = i+24)
				{
					gotoxy(2,i);		// Tengah
					printf("%c", 179);
					gotoxy(1,i);		// Atas
					printf("%c", 194);
					gotoxy(3,i);		// Bawah
					printf("%c", 193);
				}
				
				gotoxy(3,23);
				printf("%c", 197);
				gotoxy(3,47);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,23);
					printf("%c", 179);
					gotoxy(i,47);
					printf("%c", 179);	
				}
				gotoxy(8,23);
				printf("%c", 192);
				gotoxy(8,47);
				printf("%c", 217);
				for(int i=24; i<=46; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				
				gotoxy(2,12);
				warna(warna_teks[0]);
				printf("FILE");
					
				gotoxy(2,33);
				warna(warna_teks[1]);
				printf("EDIT");
					
				gotoxy(2,56);
				warna(warna_teks[2]);
				printf("FORMAT");
				
				gotoxy(2,81);
				warna(warna_teks[3]);
				printf("VIEW");
				
				gotoxy(2,104);
				warna(warna_teks[4]);
				printf("HELP");
				warna(7);
				*status = false;	
			}
			break;
		}
		
		case 3:
		{
			if (*status == false)
			{
				gotoxy(3,47);
				printf("%c", 197);
				gotoxy(3,71);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,47);
					printf("%c", 179);
					gotoxy(i,71);
					printf("%c", 179);	
				}
				gotoxy(8,47);
				printf("%c", 192);
				gotoxy(8,71);
				printf("%c", 217);
				for(int i=48; i<=70; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				*status = true;
			}else{
				//Clear Screen Sebagian
				for(int i=0; i <= 5; i++)
				{
					gotoxy(i,0);
					printf("                                                                                                                                  ");
				}
				
				gotoxy(0,0);
				printf("PULL DOWN MODE : ON");
				
				box(3,1,116,3);
				for(int i=23; i <= 116; i = i+24)
				{
					gotoxy(2,i);		// Tengah
					printf("%c", 179);
					gotoxy(1,i);		// Atas
					printf("%c", 194);
					gotoxy(3,i);		// Bawah
					printf("%c", 193);
				}
				
				gotoxy(3,47);
				printf("%c", 197);
				gotoxy(3,71);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,47);
					printf("%c", 179);
					gotoxy(i,71);
					printf("%c", 179);	
				}
				gotoxy(8,47);
				printf("%c", 192);
				gotoxy(8,71);
				printf("%c", 217);
				for(int i=48; i<=70; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				
				gotoxy(2,12);
				warna(warna_teks[0]);
				printf("FILE");
					
				gotoxy(2,33);
				warna(warna_teks[1]);
				printf("EDIT");
					
				gotoxy(2,56);
				warna(warna_teks[2]);
				printf("FORMAT");
				
				gotoxy(2,81);
				warna(warna_teks[3]);
				printf("VIEW");
				
				gotoxy(2,104);
				warna(warna_teks[4]);
				printf("HELP");
				warna(7);
				*status = false;	
			}
			break;
		}
		
		case 4:
		{
			if (*status == false)
			{
				gotoxy(3,71);
				printf("%c", 197);
				gotoxy(3,95);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,71);
					printf("%c", 179);
					gotoxy(i,95);
					printf("%c", 179);	
				}
				gotoxy(8,71);
				printf("%c", 192);
				gotoxy(8,95);
				printf("%c", 217);
				for(int i=72; i<=94; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				*status = true;	
			}else{
				//Clear Screen Sebagian
				for(int i=0; i <= 5; i++)
				{
					gotoxy(i,0);
					printf("                                                                                                                                  ");
				}
				
				gotoxy(0,0);
				printf("PULL DOWN MODE : ON");
				
				box(3,1,116,3);
				for(int i=23; i <= 116; i = i+24)
				{
					gotoxy(2,i);		// Tengah
					printf("%c", 179);
					gotoxy(1,i);		// Atas
					printf("%c", 194);
					gotoxy(3,i);		// Bawah
					printf("%c", 193);
				}
				
				gotoxy(3,71);
				printf("%c", 197);
				gotoxy(3,95);
				printf("%c", 197);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,71);
					printf("%c", 179);
					gotoxy(i,95);
					printf("%c", 179);	
				}
				gotoxy(8,71);
				printf("%c", 192);
				gotoxy(8,95);
				printf("%c", 217);
				for(int i=72; i<=94; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				
				gotoxy(2,12);
				warna(warna_teks[0]);
				printf("FILE");
					
				gotoxy(2,33);
				warna(warna_teks[1]);
				printf("EDIT");
					
				gotoxy(2,56);
				warna(warna_teks[2]);
				printf("FORMAT");
				
				gotoxy(2,81);
				warna(warna_teks[3]);
				printf("VIEW");
				
				gotoxy(2,104);
				warna(warna_teks[4]);
				printf("HELP");
				warna(7);
				*status = false;	
			}
			break;
		}
		
		case 5:
		{
			if (*status == false)
			{
				gotoxy(3,95);
				printf("%c", 197);
				gotoxy(3,116);
				printf("%c", 180);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,95);
					printf("%c", 179);
					gotoxy(i,116);
					printf("%c", 179);	
				}
				gotoxy(8,95);
				printf("%c", 192);
				gotoxy(8,116);
				printf("%c", 217);
				for(int i=96; i<=115; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				*status = true;
			}else{
				//Clear Screen Sebagian
				for(int i=0; i <= 5; i++)
				{
					gotoxy(i,0);
					printf("                                                                                                                                  ");
				}
				
				gotoxy(0,0);
				printf("PULL DOWN MODE : ON");
				
				box(3,1,116,3);
				for(int i=23; i <= 116; i = i+24)
				{
					gotoxy(2,i);		// Tengah
					printf("%c", 179);
					gotoxy(1,i);		// Atas
					printf("%c", 194);
					gotoxy(3,i);		// Bawah
					printf("%c", 193);
				}
				
				gotoxy(3,95);
				printf("%c", 197);
				gotoxy(3,116);
				printf("%c", 180);
				for(int i=4; i<=7; i++)
				{
					gotoxy(i,95);
					printf("%c", 179);
					gotoxy(i,116);
					printf("%c", 179);	
				}
				gotoxy(8,95);
				printf("%c", 192);
				gotoxy(8,116);
				printf("%c", 217);
				for(int i=96; i<=115; i++)
				{
					gotoxy(8,i);
					printf("%c", 196);
				}
				
				gotoxy(2,12);
				warna(warna_teks[0]);
				printf("FILE");
					
				gotoxy(2,33);
				warna(warna_teks[1]);
				printf("EDIT");
					
				gotoxy(2,56);
				warna(warna_teks[2]);
				printf("FORMAT");
				
				gotoxy(2,81);
				warna(warna_teks[3]);
				printf("VIEW");
				
				gotoxy(2,104);
				warna(warna_teks[4]);
				printf("HELP");
				warna(7);
				*status = false;	
			}
			break;
		}
		
		default:
		{
			break;
		}
	}
}

void Feature_Selection(list *L, int pilihan, bool *pull_mode, int *baris, int *kolom, bool *status_bar)
{
	address P,Q;
	
	int warna_teks[3] = {7,7,7};
	char ch;
	int pilihan_fitur = 1;
	int max_fitur = 0;
	bool status = true;
	
	switch(pilihan)
	{
		case 1:
		{
			max_fitur = 3;
			break;
		}
		
		case 2:
		{
			max_fitur = 3;
			break;
		}
		
		case 3:
		{
			max_fitur = 2;
			break;
		}
		
		case 4:
		{
			max_fitur = 1;
			break;
		}
		
		case 5:
		{
			max_fitur = 1;
			break;
		}
	}
	
	while(status == true)
	{
		// Membuat tulisan fitur pada border
		switch (pilihan)
		{
			case 1:
			{
				gotoxy(4,5);
				warna(warna_teks[0]);
				printf("NEW FILE");
					
				gotoxy(5,5);
				warna(warna_teks[1]);
				printf("OPEN FILE");
					
				gotoxy(6,5);
				warna(warna_teks[2]);
				printf("SAVE FILE");
				warna(7);
				break;
			}
			
			case 2:
			{
				gotoxy(4,25);
				warna(warna_teks[0]);
				printf("FIND & REPLACE");
					
				gotoxy(5,25);
				warna(warna_teks[1]);
				printf("DUPLICATE FILE");
					
				gotoxy(6,25);
				warna(warna_teks[2]);
				printf("DELETE FILE");
				warna(7);
				break;
			}
			
			case 3:
			{
				gotoxy(4,49);
				warna(warna_teks[0]);
				printf("UPPERCASE CHAR");
					
				gotoxy(5,49);
				warna(warna_teks[1]);
				printf("LOWERCASE CHAR");
				warna(7);
				break;
			}
			
			case 4:
			{
				gotoxy(4,73);
				warna(warna_teks[0]);
				printf("STATUS BAR");
				break;
			}
			
			case 5:
			{
				gotoxy(4,97);
				warna(warna_teks[0]);
				printf("INFORMATION");
				break;
			}
		}
		
		// Membaca Input Keyboard
		fflush(stdin);
		ch = getch();
		
		// Arrow
		if (ch == -32)
		{
			ch = getch();
			// Down Arrow
			if (ch == 80)
			{
				if (pilihan_fitur < max_fitur)
				{
					pilihan_fitur++;
				}else{
					pilihan_fitur = pilihan_fitur - (max_fitur-1);
				}
			}
			
			// Up Arrow
			if (ch == 72)
			{
				if (pilihan_fitur > 1)
				{
					pilihan_fitur--;
				}else{
					pilihan_fitur = max_fitur;
				}
			}
			
			// Perubahan warna pada fitur yang dipilih
			for (int i=0; i < max_fitur; i++)
			{
				warna_teks[i] = 7;
			}
			warna_teks[pilihan_fitur-1] = 12;	
		}
		
		// Enter
		if (ch == 13)
		{
			switch(pilihan)
			{
				// FILE
				case 1:
				{
					switch(pilihan_fitur)
					{
						// NEW FILE
						case 1:
						{
//							gotoxy(13,4);
//							printf("Apakah kamu akan menyimpan file yang kamu tulis? (Y/N)\n");
//							fflush(stdin);
//							ch = toupper(getch());
//							if (ch == 'Y')
//							{
//								save(&(*L));
//							}
							dealokasi(&(*L));
							create_text_editor(&(*L));
							*baris = 0;
							*kolom = 0;
							
							status = false;
							*pull_mode = false;
							break;
						}
						
						// OPEN FILE
						case 2:
						{
							gotoxy(13,4);
							printf("Apakah kamu akan menyimpan file yang kamu tulis? (Y/N)\n");
							fflush(stdin);
							ch = toupper(getch());
							if (ch == 'Y')
							{
								save(&(*L));
							}
							dealokasi(&(*L));
							create_text_editor(&(*L));
							*baris = 0;
							*kolom = 0;
							printf("\e[?25h");
							ListFile(&(*L));
							modify(&(*L));
							create_text_editor(&(*L));
							status = false;
							*pull_mode = false;
							break;
						}
						
						// SAVE FILE
						case 3:
						{
							fflush(stdin);
							save(&(*L));
							gotoxy(1,1);
							printf("File Berhasil Disimpan!");
							gotoxy(2,1);
							printf("Tekan enter untuk keluar dari program!");
							while(1)
							{
								ch = getch();
								if (ch == 13)
								{
									exit(0);
								}
							}
							break;
						}
					}
					break;
				}
				
				// EDIT
				case 2:
				{
					switch(pilihan_fitur)
					{
						// FINREP
						case 1:
						{
							break;
						}
						
						// Duplikat File
						case 2:
						{
							break;
						}
						
						// Delete File
						case 3:
						{
							break;
						}
					}
					break;
				}
				
				// FORMAT
				case 3:
				{
					switch(pilihan_fitur)
					{
						// Uppercase
						case 1:
						{
							P = Next(Head(*L));
							while (P != NULL)
							{
								Info(P) = toupper(Info(P));
								P = Next(P);
							}
							status = false;
							*pull_mode = false;
							
							break;
						}
						
						// Lowercase
						case 2:
						{
							P = Next(Head(*L));
							while (P != NULL)
							{
								Info(P) = tolower(Info(P));
								P = Next(P);
							}
							status = false;
							*pull_mode = false;
							
							break;
						}
					}
					break;
				}
				
				// VIEW
				case 4:
				{
					switch(pilihan_fitur)
					{
						// Status Bar
						case 1:
						{
							if (*status_bar == true)
							{
								*status_bar = false;
							}else{
								*status_bar = true;
							}
							status = false;
							*pull_mode = false;
							warna(7);
							
							break;
						}
					}
					break;
				}
				
				// HELP
				case 5:
				{
					warna(7);
					break;
				}
			}
		}
		
		// ESC
		if (ch == 27)
		{
			for(int i=0; i <= 12; i++)
			{
				gotoxy(i,0);
				printf("                                                                                                                                  ");
			}
			warna(7);
			status = false;
		}
	}	
}