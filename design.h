#ifndef design_H
#define design_H
#include "input.h"

void tampil_list(list *L);
void gotoxy(int baris,int kolom);
void loading();
void border();
void box(int x1,int y1,int x2,int y2);
void creadit();
void menu();
void displayLogo();
void warna(int color);
bool selectionMenu(list *L);
void barInput(int baris, int kolom, list L, bool pull_mode, bool *status_bar);
void barMenu();
int jumlah_karakter(list L);
int jumlah_kata(list L);
void SetWindow(int *tinggi_max, int *lebar_max, int baris, int kolom, list L);
void Create_Border(int pilihan, bool *status, int warna_teks[]);
void Feature_Selection(list *L, int pilihan, bool *pull_mode, int *baris, int *kolom, bool *status_bar);
void Pull_Down_Menu(int *baris, int *kolom, list *L, bool *status_bar);

#endif
