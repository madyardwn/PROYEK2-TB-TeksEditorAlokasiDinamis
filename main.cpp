#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "input.h"
#include "file.h"
#include "design.h"

int main()
{
	/* --- Kamus Data --- */
	list L;
	bool loop = true;
	
	/* --- Algoritma --- */
	loading(); // menampilkan tampilan loading
	
	while(loop == true)
	{
		create_text_editor(&L); // membuat root tesk editor
		loop = selectionMenu(&L); // masuk selection menu dan shortcutnya
	}
	return 0;
}
