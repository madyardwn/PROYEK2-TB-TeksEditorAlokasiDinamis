#ifndef design_H
#define design_H
#include "input.h"

void gotoxy(int baris,int kolom);
void loading();
void border();
void box(int x1,int y1,int x2,int y2);
void creadit();
void menu();
void displayLogo();
void color(int color);
bool selectionMenu(list *L);
void tampil_list(list *L);
void barInput(int *baris, int *kolom, int reset);
void barMenu();
void clear();

#endif
