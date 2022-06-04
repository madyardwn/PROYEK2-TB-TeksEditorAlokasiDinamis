#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "input.h"
#include "file.h"
#include "design.h"

// modul disable window resizing dan fit buffer 
void adjustWindowSize()
{
    SMALL_RECT test; 

    HANDLE hStdout;
    COORD coord;
    BOOL ok;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 120;
    coord.Y = 30;
    ok = SetConsoleScreenBufferSize(hStdout, coord);

    test.Left = 0;
    test.Top = 0;
    test.Right = coord.X-1;
    test.Bottom = coord.Y-1;

    SetConsoleWindowInfo(hStdout, ok, &test);
    HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

int main()
{
	list L;
	bool loop = true;
	
	loading();
	adjustWindowSize();
	
	while(loop == true)
	{
		create_text_editor(&L);
		loop = selectionMenu(&L);
	}
	return 0;
}
