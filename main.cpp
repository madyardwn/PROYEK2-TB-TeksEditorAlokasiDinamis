#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "input.h"
#include "file.h"
#include "design.h"

// modul disable window resizing dan fit buffer 
void adjustWindowSize()
{
	/* https://localcoder.org/making-the-console-window-bigger-in-c */
    SMALL_RECT test;
    HANDLE hStdout;
    COORD coord;
    BOOL ok;
	
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    /*
		- GetStdHandle 				: fungsi untuk membaca STD_OUTPUT_HANDLE
		- STD_OUTPUT_HANDLE 		: standard ouput device, menginisialiasasi buffer konsole yang aktif 
	*/
    coord.X = 120;
    coord.Y = 30;
    
    /* Fungsi untuk menentukan ukuran buffer */
    ok = SetConsoleScreenBufferSize(hStdout, coord);

    test.Left = 0;
    test.Top = 0;
    test.Right = coord.X-1;
    test.Bottom = coord.Y-1;

	/* Mengontrol atau scroll content dalam konsol tanpa merubah size window */
    SetConsoleWindowInfo(hStdout, ok, &test); 
    
    /* Funsi untuk mendapatkan ukuran window*/
	HWND consoleWindow = GetConsoleWindow();
	
	/* Fix ukuran window dan mematikan resize oleh mouse */
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

int main()
{
	/* --- Kamus Data --- */
	list L;
	bool loop = true;
	
	/* --- Algoritma --- */
//	loading(); // menampilkan tampilan loading
//	adjustWindowSize(); // mengatur ukuran window
	
	while(loop == true)
	{
		create_text_editor(&L); // membuat root tesk editor
		loop = selectionMenu(&L); // masuk selection menu dan shortcutnya
	}
	return 0;
}
