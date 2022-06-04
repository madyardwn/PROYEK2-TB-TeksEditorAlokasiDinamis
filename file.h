#ifndef file_H
#define file_H

void save(list *L);
void FileToList(list *L, int *baris, int *kolom, bool fileTersedia);
void modify(list *L);
void lastCursor(int *row, int *col);
void ListFile(list *L);
bool txt_extension(char const *name);
void inputNamaFile(char karakter[25]);
bool cekNama(char namaFile[25]);
void duplicate();
void saveModify(list *L, char namaFile[30]);

#endif
