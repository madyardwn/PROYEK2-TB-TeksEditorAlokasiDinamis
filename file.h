#ifndef file_H
#define file_H

void save(list L);
void FileToList(list *L, int *baris, int *kolom, bool fileTersedia);
void modify(list *L);
void lastCursor(int *row, int *col);
int ListFile(list *L);
bool txt_extension(char const *name);
void inputNamaFile(char karakter[25]);

#endif