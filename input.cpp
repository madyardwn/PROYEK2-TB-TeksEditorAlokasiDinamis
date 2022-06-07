#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "input.h"
#include "design.h"
#include "file.h"

address Alokasi(char ch)
{
	address P;
	P = (address) malloc (sizeof(element_list));
	if (P != NULL)
	{
		Prev(P) = NULL;
		Info(P) = ch;
		Next(P) = NULL;
		return P;
	}else{
		return NULL;
	}
}

void dealokasi(list *L)
{
	/* --- Kamus Data --- */
	address P, temp;
	
	/* --- Algortima ---*/
	P = Next(Head(*L));
	while(P != NULL){
		temp = P;
		P = Next(P);
		free(temp); // dealokasi
	}
	
	free(Head(*L)); // dealokasi root
}

void create_text_editor(list *L)
{
	address P;
	P = Alokasi(NULL);
	
	Head(*L) = P;
	Current(*L) = P;
	Tail(*L) = P;
}

void input_keyboard(list *L, int *baris, int *kolom, char namaFile[], bool validasi_file)
{	
	/* --- Kamus Data --- */ 
	char ch; // variable penampung input
	bool validasi_input; // variable untuk menerima hasil pengecekan tipe input
	bool pull_mode=false; // Untuk mengecek pull mode
	bool status_bar=true;
	address P; // variable penampung address suatu node
	int max_width, max_height;
	int warna_teks[5] = {7,7,7,7,7};
	max_width = 120;
	max_height = 30;
	
	/* --- Algoritma --- */
	// Membuat Tampilan Header (Pull Down & Status Bar)
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
	if (status_bar == true)
	{
		box(3,4,116,6);
		for(int i=23; i <= 116; i = i+24)
		{
			gotoxy(5,i);		// Tengah
			printf("%c", 179);
			gotoxy(4,i);		// Atas
			printf("%c", 194);
			gotoxy(6,i);		// Bawah
			printf("%c", 193);
		}
		barInput(*baris,*kolom,*L,pull_mode,&status_bar);	
	}
	
	gotoxy(*baris+8,*kolom); // modul untuk memindahkan kursor
	
	while (1)
	{
		ch = getch();
		
		/* ctrl + q : untuk (membatalkan pengetikan) kembali ke menu */
		if (ch == 17)
		{
			break;
		}else
		
		/* ctrl + s : untuk Save */
		if(ch == 19)
		{
			if (validasi_file == true)
			{
				saveModify(&(*L), namaFile);
			}else{
				save(&(*L));
			}
			break;
		}
		
		/* Cek Validasi Input */
		validasi_input = cek_input(ch);
		
		/* Jika tidak perlu di handling, maka input normal */ 
		if (validasi_input != true)
		{
			P = Alokasi(ch);
			if (P != NULL)
			{
				normal_input(*(&L), P, &(*baris), &(*kolom));
			}else{
				Beep(1000,50);
			}
		}
		
		/* Jika perlu di handling, maka input di handle terlebih dahulu */
		else
		{
			handling_input(*(&L), ch, &(*baris), &(*kolom), &status_bar);
		}
		barInput(*baris,*kolom,*L,pull_mode,&status_bar); 
		SetWindow(&max_height+5, &max_width+5, *baris, *kolom, *L);
		gotoxy(*baris+8,*kolom);
	}
	dealokasi(&(*L)); // membersihkan memori setelah selesai input
}

bool cek_input(char ch)
{
	switch(ch)
	{	
		// F1-F12
		case 0:
		{
			return true;
			break;
		}
		
		// Backspace
		case 8:
		{
			return true;
			break;
		}
		
		// Enter
		case 13:
		{
			return true;
			break;
		}
		
		// Arrow & Del
		case -32:
		{
			return true;
			break;
		}
		
		// Tab
		case 9:
		{
			return true;
			break;
		}
		
		// ESC
		case 27:
		{
			return true;
			break;
		}
		
		// Normal
		default:
		{
			return false;
			break;
		}	
	}		
}

void normal_input(list *L, address P, int *baris, int *kolom)
{
	// Linked List
	if (Next(Current(*L)) != NULL)
	{
		Next(P) = Next(Current(*L));
		Prev(Next(Current(*L))) = P;
		Next(Current(*L)) = P;
		Prev(P) = Current(*L);
		Current(*L) = P; 
	}
	
	else
	{
		Next(Current(*L)) = P;
		Prev(P) = Current(*L);
		Tail(*L) = P;
		Current(*L) = P;
		if(Info(P) == NULL)
		{
			return;
		}
	}
	
	P = Current(*L);
	while(P != NULL)
	{
		if (Info(P) == NULL)
		{
			break;
		}
		printf("%c", Info(P));
		P = Next(P);
	}

	*kolom = *kolom + 1;
	gotoxy(*baris+8,*kolom);
}

void handling_input(list *L, char ch, int *baris, int *kolom, bool *status_bar)
{
	// F1-F12
	if (ch == 0)
	{
		F1_12(*(&L), ch, *(&baris), *(&kolom), *(&status_bar));
	}else
	
	// Backspace
	if (ch == 8)
	{
		backspace(*(&L), NULL, *(&baris), *(&kolom));
	}else
	
	// Enter
	if (ch == 13)
	{
		enter(*(&L), NULL, *(&baris), *(&kolom));
		
	}else
	
	// Arrows & Del
	if (ch == -32)
	{
		arrows(*(&L), ch, *(&baris), *(&kolom));
	}else
	
	// Tab
	if (ch == 9)
	{
		// Modul Tab
	}else
	
	// ESC
	if (ch == 27)
	{
		// Modul ESC
	}
}

void F1_12(list *L, char ch, int *baris, int *kolom, bool *status_bar)
{
	address P;
	ch = getch();
	int warna_teks[5]={7,7,7,7,7};
	
	// F1
	switch(ch)
	{
		// F1
		case 59:
		{
			Pull_Down_Menu(&(*baris),&(*kolom),&(*L), &(*status_bar));
			
			system("cls");
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
			if (*status_bar == true)
			{
				box(3,4,116,6);
			for(int i=23; i <= 116; i = i+24)
			{
				gotoxy(5,i);		// Tengah
				printf("%c", 179);
				gotoxy(4,i);		// Atas
				printf("%c", 194);
				gotoxy(6,i);		// Bawah
				printf("%c", 193);
			}
			barInput(*baris,*kolom,*L,false,&(*status_bar)); 	
			}
			
			gotoxy(8,0);
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
			printf("\e[?25h");
			break;
		}
		
		default:
		{
			break;
		}
	}
}

void arrows(list *L, char ch, int *baris, int *kolom)
{
	address P,Q;
	int count = 0;
	int last_line = -1;
	ch = getch();
	
	switch(ch)
	{
		// Up Arrow
		case 72:
		{
			P = Current(*L);
			if (P != Head(*L) and *baris != 0)
			{
				// Jika Pada Kolom Awal / Baris Kosong
				if (Info(P) == NULL)
				{
					P = Prev(P);
					while (Info(P) != NULL)
					{
						P = Prev(P);
					}
					*baris = *baris - 1;
					*kolom = 0;
					Current(*L) = P;
					gotoxy(*baris+8,*kolom);
					
				// Jika Bukan Pada Kolom Awal / Baris Berisi Suatu Karakter
				}else{
					while (Info(P) != NULL)
					{
						P = Prev(P);
						count = count + 1;
					}
					P = Prev(P);
					
					if (Info(P) == NULL)
					{
						*baris = *baris - 1;
						*kolom = 0;
						Current(*L) = P;
						gotoxy(*baris+8,*kolom);
					}else{
						while (Info(P) != NULL)
						{
							P = Prev(P);
						}
						P = Next(P);
						*kolom = 1;
						
						for (int i=1; i < count; i++)
						{
							if (Info(P) != NULL)
							{
								P = Next(P);
								*kolom = *kolom + 1;
							}else{
								P = Prev(P);
								*kolom = *kolom - 1;
								break;
							}
						}
						if (Info(P) == NULL)
						{
							P = Prev(P);
							*kolom = *kolom - 1;	
						}
						
						*baris = *baris - 1;
						Current(*L) = P;
						gotoxy(*baris+8,*kolom);	
					}
				}
			}
			break;
		}
		
		// Down Arrow
		case 80:
		{
			// Hitung Baris Terakhir
			P = Head(*L);
			while (P != NULL)
			{
				if (Info(P) == NULL)
				{
					last_line = last_line + 1;
				}
				P = Next(P);
			}		
			
			// Algoritma Down Arrow
			P = Current(*L);
			if (P != Tail(*L) and *baris != last_line)
			{
				// Jika Pada Kolom Awal / Baris Kosong
				if (Info(P) == NULL)
				{
					P = Next(P);
					while (Info(P) != NULL)
					{
						P = Next(P);
					}
					*baris = *baris + 1;
					*kolom = 0;
					Current(*L) = P;
					gotoxy(*baris+8,*kolom);
					
				// Jika Bukan Pada Kolom Awal / Baris Berisi Suatu Karakter
				}else{
					while (Info(P) != NULL)
					{
						P = Prev(P);
						count = count + 1;
					}
					P = Next(P);
					
					while (Info(P) != NULL)
					{
						P = Next(P);
					}
					P = Next(P);
					*kolom = 1;
					
					for (int i=1; i < count; i++)
					{
						if (Next(P) == NULL)
						{
							break;
						}else
						
						if (Info(P) != NULL)
						{
							P = Next(P);
							*kolom = *kolom + 1;
						}else{
							P = Prev(P);
							*kolom = *kolom - 1;
							break;
						}
					}
					*baris = *baris + 1;
					Current(*L) = P;
					gotoxy(*baris+8,*kolom);	
				}
			}
			break;
		}
		
		// Right Arrow
		case 77:
		{
			P = Current(*L);
			if (Next(P) != NULL)
			{
				Current(*L) = Next(P);
				*kolom = *kolom + 1;
				if (Info(Current(*L)) == NULL)
				{
					*kolom = 0;
					*baris = *baris + 1;
				}
				gotoxy(*baris+8,*kolom);
			}
			break;
		}
		
		// Left Arrow
		case 75:
		{
			P = Current(*L);
			if (Prev(P) != NULL)
			{
				Current(*L) = Prev(P);
				*kolom = *kolom - 1;
				if (Info(P) == NULL)
				{
					P = Prev(P);
					while(Info(P) != NULL)
					{
						P = Prev(P);
					}
					*kolom = 0;
					P = Next(P);
					while(Info(P) != NULL)
					{
						P = Next(P);
						*kolom = *kolom + 1;
					}
					*baris = *baris - 1;
				}
				gotoxy(*baris+8,*kolom);
			}
			break;
		}
		
		//Delete
		case 83:
		{	
			P = Current(*L);
			if (Next(P) != NULL)
			{
				Q = Next(P);
				if (Next(Next(P)) != NULL)
				{
					Prev(Next(Next(P))) = P;
					Next(P) = Next(Next(P));
					free(Q);
				}else{
					Next(P) = NULL;
					free(Q);
				}
				
				// Hitung Baris Terakhir
				P = Head(*L);
				while (P != NULL)
				{
					if (Info(P) == NULL)
					{
						last_line = last_line + 1;
					}
					P = Next(P);
				}
				
				// Bersihkan Layar
				for(int i=0; i <= last_line+10; i++)
				{
					gotoxy(i+8,0);
					printf("                                                                                                                                                                                                                                                                                              ");
				}
				
				// Print Layar
				gotoxy(8,0);
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
			gotoxy(*baris+8,*kolom);
			break;
		}
		
		default:
		{
			break;
		}
	}
}

void enter(list *L, char ch, int *baris, int *kolom)
{
	address P;
	int last_line = 0;
	
	P = Alokasi(ch);
	if (Next(Current(*L)) != NULL)
	{
		Prev(P) = Current(*L);
		Next(P) = Next(Current(*L));
		Prev(Next(Current(*L))) = P;
		Next(Current(*L)) = P;
		Current(*L) = P;
	}
	
	else
	{
		Next(Current(*L)) = P;
		Prev(P) = Current(*L);
		Current(*L) = P;
	}
	
	// Hitung Baris Terakhir
	P = Head(*L);
	while (P != NULL)
	{
		if (Info(P) == NULL)
		{
			last_line = last_line + 1;
		}
		P = Next(P);
	}
	
	//Bersihkan Layar
	for(int i=0; i <= last_line+10; i++)
	{
		gotoxy(i+8,0);
		printf("                                                                                                                                                                                                          ");
	}
	
	// Tampil Layar
	gotoxy(8,0);
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
	
	*baris = *baris + 1;
	*kolom = 0;
	gotoxy(*baris+8,*kolom);
}

void backspace(list *L, char ch, int *baris, int *kolom)
{
	address P;
	int count = 0;
	int last_line = 0;
	
	P = Current(*L);
	if (Current(*L) != Head(*L))
	{
		if (Next(P) != NULL)
		{
			Prev(Next(P)) = Prev(P);
			Next(Prev(P)) = Next(P);
			Current(*L) = Prev(P);
			free(P);
		}else{
			Next(Prev(P)) = NULL;
			Current(*L) = Prev(P);
			free(P);
		}
						
		if (*kolom != 0)
		{
			*kolom = *kolom - 1;
		}else{
			P = Current(*L);
			if (Info(P) != NULL)
			{
				P = Prev(P);
			}
			
			while (Info(P) != NULL)
			{
				count = count + 1;
				P = Prev(P);
			}
			*baris = *baris - 1;
			if (count == 0)
			{
				*kolom = count;
			}else{
				*kolom = count + 1;
			}
		}
	}
	
	// Hitung Baris Terakhir
	P = Head(*L);
	while (P != NULL)
	{
		if (Info(P) == NULL)
		{
			last_line = last_line + 1;
		}
		P = Next(P);
	}
	
	//Bersihkan Layar
	for(int i=0; i <= last_line+10; i++)
	{
		gotoxy(i+8,0);
		printf("                                                                                                                                                                                                          ");
	}

	//Tampil Layar
	gotoxy(8,0);
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
	gotoxy(*baris+8,*kolom);
}
