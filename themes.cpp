#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include "themes.h"
#include "design.h"

void menu_themes()
{
	bool status;
	char ulang;
	int pilihan;
	
	while(1)
	{
		system("cls");
		printf("\n");
		printf("\t ===============================\n");
		printf("\t | Pilih Tema Yang Diinginkan: |\n");
		printf("\t | 1.Bright Theme              |\n");		
		printf("\t | 2.Dark Theme                |\n");
		printf("\t | 3.Custom Theme              |\n");
		printf("\t | 4.Kembali                   |\n");
		printf("\t ===============================\n");	
		printf("\t Pilihan Kamu: ");
		scanf("%d", &pilihan);
		printf("\n");
		
		switch (pilihan)
		{
			case 1:
			{
				system("color F9");
				printf("\t Apakah kamu yakin menggunakan tema ini? (Y/T)\n");
				printf("\t Pilihan Kamu: ");
				ulang = toupper(getche());
				printf("\n\n");
				if (ulang == 'Y')
				{
					printf("\t Bright Theme Berhasil Digunakan!\n");
					printf("\t Tekan Enter Untuk Kembali!");
					(getche());
					system("cls");
					status = 'Y';
					break;
				}else{
					system("Color 07");
					system("cls");
					printf("\t Kembali Ke Tema Default\n");
				}
				break;
			}
			
			case 2:
			{
				system("color 0F");
				printf("\t Apakah kamu yakin menggunakan tema ini? (Y/T)\n");
				printf("\t Pilihan Kamu: ");
				ulang = toupper(getche());
				printf("\n\n");
				if (ulang == 'Y')
				{
					printf("\t Dark Theme Berhasil Digunakan!\n");
					printf("\t Tekan Enter Untuk Kembali!");
					(getche());
					system("cls");
					status = 'Y';
					break;
				}else{
					system("Color 07");
					system("cls");
					printf("\t Kembali Ke Tema Default\n");
				}
				break;
			}
			
			case 3:
			{
				custom_themes(&status);
				break;
			}
			
			case 4:
			{
				status = true;
				break;
			}
			
			default:
			{
				printf("\t Pilihan Tidak Tersedia!");
				status = false;
				break;
			}
		}
		
		if (status == true)
		{
			break;
		}
	}
}

void custom_themes(bool *status)
{	
	int font, background;
	char ulang;
	fflush(stdin);
	while(1)
	{
		system("cls");
		printf("\n");
		printf("\t =========================================\n");
		printf("\t | Pilih Warna Yang Diinginkan:          |\n");
		printf("\t | 1.Black           9 . Gray            |\n");		
		printf("\t | 2.Blue            10. Light Blue      ||\n");
		printf("\t | 3.Green           11. Light Green     |\n");
		printf("\t | 4.Aqua            12. Light Aqua      |\n");
		printf("\t | 5.Red             13. Light Red       |\n");
		printf("\t | 6.Purple          14. Light Purple    |\n");
		printf("\t | 7.Yellow          15. Light Yellow    |\n");
		printf("\t | 8.White           16. Bright White    |\n");
		printf("\t =========================================\n\n");	
		printf("\t Note: tidak bisa memilih jenis warna yang sama!\n");
		printf("\t Font      : ");
		scanf("%d", &font);
		printf("\t Background: ");
		scanf("%d", &background);
		printf("\n");	
		
		if (font != background and font < 17 and font > 0 and background < 17 and background > 0){
			*status = true;
		}else{
			*status = false;
		}
		
		switch(background)
		{
			case 1:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 00");
						break;
					}
					
					case 2:
					{
						system("Color 01");
						break;
					}
					
					case 3:
					{
						system("Color 02");
						break;
					}
					
					case 4:
					{
						system("Color 03");
						break;
					}
					
					case 5:
					{
						system("Color 04");
						break;
					}
					
					case 6:
					{
						system("Color 05");
						break;
					}
					
					case 7:
					{
						system("Color 06");
						break;
					}
					
					case 8:
					{
						system("Color 07");
						break;
					}
					
					case 9:
					{
						system("Color 08");
						break;
					}
					
					case 10:
					{
						system("Color 09");
						break;
					}
					
					case 11:
					{
						system("Color 0A");
						break;
					}
					
					case 12:
					{
						system("Color 0B");
						break;
					}
					
					case 13:
					{
						system("Color 0C");
						break;
					}
					
					case 14:
					{
						system("Color 0D");
						break;
					}
					
					case 15:
					{
						system("Color 0E");
						break;
					}
					
					case 16:
					{
						system("Color 0F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 2:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 10");
						break;
					}
					
					case 2:
					{
						system("Color 11");
						break;
					}
					
					case 3:
					{
						system("Color 12");
						break;
					}
					
					case 4:
					{
						system("Color 13");
						break;
					}
					
					case 5:
					{
						system("Color 14");
						break;
					}
					
					case 6:
					{
						system("Color 15");
						break;
					}
					
					case 7:
					{
						system("Color 16");
						break;
					}
					
					case 8:
					{
						system("Color 17");
						break;
					}
					
					case 9:
					{
						system("Color 18");
						break;
					}
					
					case 10:
					{
						system("Color 19");
						break;
					}
					
					case 11:
					{
						system("Color 1A");
						break;
					}
					
					case 12:
					{
						system("Color 1B");
						break;
					}
					
					case 13:
					{
						system("Color 1C");
						break;
					}
					
					case 14:
					{
						system("Color 1D");
						break;
					}
					
					case 15:
					{
						system("Color 1E");
						break;
					}
					
					case 16:
					{
						system("Color 1F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 3:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 20");
						break;
					}
					
					case 2:
					{
						system("Color 21");
						break;
					}
					
					case 3:
					{
						system("Color 22");
						break;
					}
					
					case 4:
					{
						system("Color 23");
						break;
					}
					
					case 5:
					{
						system("Color 24");
						break;
					}
					
					case 6:
					{
						system("Color 25");
						break;
					}
					
					case 7:
					{
						system("Color 26");
						break;
					}
					
					case 8:
					{
						system("Color 27");
						break;
					}
					
					case 9:
					{
						system("Color 28");
						break;
					}
					
					case 10:
					{
						system("Color 29");
						break;
					}
					
					case 11:
					{
						system("Color 2A");
						break;
					}
					
					case 12:
					{
						system("Color 2B");
						break;
					}
					
					case 13:
					{
						system("Color 2C");
						break;
					}
					
					case 14:
					{
						system("Color 2D");
						break;
					}
					
					case 15:
					{
						system("Color 2E");
						break;
					}
					
					case 16:
					{
						system("Color 2F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 4:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 30");
						break;
					}
					
					case 2:
					{
						system("Color 31");
						break;
					}
					
					case 3:
					{
						system("Color 32");
						break;
					}
					
					case 4:
					{
						system("Color 33");
						break;
					}
					
					case 5:
					{
						system("Color 34");
						break;
					}
					
					case 6:
					{
						system("Color 35");
						break;
					}
					
					case 7:
					{
						system("Color 36");
						break;
					}
					
					case 8:
					{
						system("Color 37");
						break;
					}
					
					case 9:
					{
						system("Color 38");
						break;
					}
					
					case 10:
					{
						system("Color 39");
						break;
					}
					
					case 11:
					{
						system("Color 3A");
						break;
					}
					
					case 12:
					{
						system("Color 3B");
						break;
					}
					
					case 13:
					{
						system("Color 3C");
						break;
					}
					
					case 14:
					{
						system("Color 3D");
						break;
					}
					
					case 15:
					{
						system("Color 3E");
						break;
					}
					
					case 16:
					{
						system("Color 3F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 5:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 40");
						break;
					}
					
					case 2:
					{
						system("Color 41");
						break;
					}
					
					case 3:
					{
						system("Color 42");
						break;
					}
					
					case 4:
					{
						system("Color 43");
						break;
					}
					
					case 5:
					{
						system("Color 44");
						break;
					}
					
					case 6:
					{
						system("Color 45");
						break;
					}
					
					case 7:
					{
						system("Color 46");
						break;
					}
					
					case 8:
					{
						system("Color 47");
						break;
					}
					
					case 9:
					{
						system("Color 48");
						break;
					}
					
					case 10:
					{
						system("Color 49");
						break;
					}
					
					case 11:
					{
						system("Color 4A");
						break;
					}
					
					case 12:
					{
						system("Color 4B");
						break;
					}
					
					case 13:
					{
						system("Color 4C");
						break;
					}
					
					case 14:
					{
						system("Color 4D");
						break;
					}
					
					case 15:
					{
						system("Color 4E");
						break;
					}
					
					case 16:
					{
						system("Color 4F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 6:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 50");
						break;
					}
					
					case 2:
					{
						system("Color 51");
						break;
					}
					
					case 3:
					{
						system("Color 52");
						break;
					}
					
					case 4:
					{
						system("Color 53");
						break;
					}
					
					case 5:
					{
						system("Color 54");
						break;
					}
					
					case 6:
					{
						system("Color 55");
						break;
					}
					
					case 7:
					{
						system("Color 56");
						break;
					}
					
					case 8:
					{
						system("Color 57");
						break;
					}
					
					case 9:
					{
						system("Color 58");
						break;
					}
					
					case 10:
					{
						system("Color 59");
						break;
					}
					
					case 11:
					{
						system("Color 5A");
						break;
					}
					
					case 12:
					{
						system("Color 5B");
						break;
					}
					
					case 13:
					{
						system("Color 5C");
						break;
					}
					
					case 14:
					{
						system("Color 5D");
						break;
					}
					
					case 15:
					{
						system("Color 5E");
						break;
					}
					
					case 16:
					{
						system("Color 5F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 7:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 60");
						break;
					}
					
					case 2:
					{
						system("Color 61");
						break;
					}
					
					case 3:
					{
						system("Color 62");
						break;
					}
					
					case 4:
					{
						system("Color 63");
						break;
					}
					
					case 5:
					{
						system("Color 64");
						break;
					}
					
					case 6:
					{
						system("Color 65");
						break;
					}
					
					case 7:
					{
						system("Color 66");
						break;
					}
					
					case 8:
					{
						system("Color 67");
						break;
					}
					
					case 9:
					{
						system("Color 68");
						break;
					}
					
					case 10:
					{
						system("Color 69");
						break;
					}
					
					case 11:
					{
						system("Color 6A");
						break;
					}
					
					case 12:
					{
						system("Color 6B");
						break;
					}
					
					case 13:
					{
						system("Color 6C");
						break;
					}
					
					case 14:
					{
						system("Color 6D");
						break;
					}
					
					case 15:
					{
						system("Color 6E");
						break;
					}
					
					case 16:
					{
						system("Color 6F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 8:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 70");
						break;
					}
					
					case 2:
					{
						system("Color 71");
						break;
					}
					
					case 3:
					{
						system("Color 72");
						break;
					}
					
					case 4:
					{
						system("Color 73");
						break;
					}
					
					case 5:
					{
						system("Color 74");
						break;
					}
					
					case 6:
					{
						system("Color 75");
						break;
					}
					
					case 7:
					{
						system("Color 76");
						break;
					}
					
					case 8:
					{
						system("Color 77");
						break;
					}
					
					case 9:
					{
						system("Color 78");
						break;
					}
					
					case 10:
					{
						system("Color 79");
						break;
					}
					
					case 11:
					{
						system("Color 7A");
						break;
					}
					
					case 12:
					{
						system("Color 7B");
						break;
					}
					
					case 13:
					{
						system("Color 7C");
						break;
					}
					
					case 14:
					{
						system("Color 7D");
						break;
					}
					
					case 15:
					{
						system("Color 7E");
						break;
					}
					
					case 16:
					{
						system("Color 7F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 9:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 80");
						break;
					}
					
					case 2:
					{
						system("Color 81");
						break;
					}
					
					case 3:
					{
						system("Color 82");
						break;
					}
					
					case 4:
					{
						system("Color 83");
						break;
					}
					
					case 5:
					{
						system("Color 84");
						break;
					}
					
					case 6:
					{
						system("Color 85");
						break;
					}
					
					case 7:
					{
						system("Color 86");
						break;
					}
					
					case 8:
					{
						system("Color 87");
						break;
					}
					
					case 9:
					{
						system("Color 88");
						break;
					}
					
					case 10:
					{
						system("Color 89");
						break;
					}
					
					case 11:
					{
						system("Color 8A");
						break;
					}
					
					case 12:
					{
						system("Color 8B");
						break;
					}
					
					case 13:
					{
						system("Color 8C");
						break;
					}
					
					case 14:
					{
						system("Color 8D");
						break;
					}
					
					case 15:
					{
						system("Color 8E");
						break;
					}
					
					case 16:
					{
						system("Color 8F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 10:
			{
				switch(font)
				{
					case 1:
					{
						system("Color 90");
						break;
					}
					
					case 2:
					{
						system("Color 91");
						break;
					}
					
					case 3:
					{
						system("Color 92");
						break;
					}
					
					case 4:
					{
						system("Color 93");
						break;
					}
					
					case 5:
					{
						system("Color 94");
						break;
					}
					
					case 6:
					{
						system("Color 95");
						break;
					}
					
					case 7:
					{
						system("Color 96");
						break;
					}
					
					case 8:
					{
						system("Color 97");
						break;
					}
					
					case 9:
					{
						system("Color 98");
						break;
					}
					
					case 10:
					{
						system("Color 99");
						break;
					}
					
					case 11:
					{
						system("Color 9A");
						break;
					}
					
					case 12:
					{
						system("Color 9B");
						break;
					}
					
					case 13:
					{
						system("Color 9C");
						break;
					}
					
					case 14:
					{
						system("Color 9D");
						break;
					}
					
					case 15:
					{
						system("Color 9E");
						break;
					}
					
					case 16:
					{
						system("Color 9F");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 11:
			{
				switch(font)
				{
					case 1:
					{
						system("Color A0");
						break;
					}
					
					case 2:
					{
						system("Color A1");
						break;
					}
					
					case 3:
					{
						system("Color A2");
						break;
					}
					
					case 4:
					{
						system("Color A3");
						break;
					}
					
					case 5:
					{
						system("Color A4");
						break;
					}
					
					case 6:
					{
						system("Color A5");
						break;
					}
					
					case 7:
					{
						system("Color A6");
						break;
					}
					
					case 8:
					{
						system("Color A7");
						break;
					}
					
					case 9:
					{
						system("Color A8");
						break;
					}
					
					case 10:
					{
						system("Color A9");
						break;
					}
					
					case 11:
					{
						system("Color AA");
						break;
					}
					
					case 12:
					{
						system("Color AB");
						break;
					}
					
					case 13:
					{
						system("Color AC");
						break;
					}
					
					case 14:
					{
						system("Color AD");
						break;
					}
					
					case 15:
					{
						system("Color AE");
						break;
					}
					
					case 16:
					{
						system("Color AF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 12:
			{
				switch(font)
				{
					case 1:
					{
						system("Color B0");
						break;
					}
					
					case 2:
					{
						system("Color B1");
						break;
					}
					
					case 3:
					{
						system("Color B2");
						break;
					}
					
					case 4:
					{
						system("Color B3");
						break;
					}
					
					case 5:
					{
						system("Color B4");
						break;
					}
					
					case 6:
					{
						system("Color B5");
						break;
					}
					
					case 7:
					{
						system("Color B6");
						break;
					}
					
					case 8:
					{
						system("Color B7");
						break;
					}
					
					case 9:
					{
						system("Color B8");
						break;
					}
					
					case 10:
					{
						system("Color B9");
						break;
					}
					
					case 11:
					{
						system("Color BA");
						break;
					}
					
					case 12:
					{
						system("Color BB");
						break;
					}
					
					case 13:
					{
						system("Color BC");
						break;
					}
					
					case 14:
					{
						system("Color BD");
						break;
					}
					
					case 15:
					{
						system("Color BE");
						break;
					}
					
					case 16:
					{
						system("Color BF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 13:
			{
				switch(font)
				{
					case 1:
					{
						system("Color C0");
						break;
					}
					
					case 2:
					{
						system("Color C1");
						break;
					}
					
					case 3:
					{
						system("Color C2");
						break;
					}
					
					case 4:
					{
						system("Color C3");
						break;
					}
					
					case 5:
					{
						system("Color C4");
						break;
					}
					
					case 6:
					{
						system("Color C5");
						break;
					}
					
					case 7:
					{
						system("Color C6");
						break;
					}
					
					case 8:
					{
						system("Color C7");
						break;
					}
					
					case 9:
					{
						system("Color C8");
						break;
					}
					
					case 10:
					{
						system("Color C9");
						break;
					}
					
					case 11:
					{
						system("Color CA");
						break;
					}
					
					case 12:
					{
						system("Color CB");
						break;
					}
					
					case 13:
					{
						system("Color CC");
						break;
					}
					
					case 14:
					{
						system("Color CD");
						break;
					}
					
					case 15:
					{
						system("Color CE");
						break;
					}
					
					case 16:
					{
						system("Color CF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 14:
			{
				switch(font)
				{
					case 1:
					{
						system("Color D0");
						break;
					}
					
					case 2:
					{
						system("Color D1");
						break;
					}
					
					case 3:
					{
						system("Color D2");
						break;
					}
					
					case 4:
					{
						system("Color D3");
						break;
					}
					
					case 5:
					{
						system("Color D4");
						break;
					}
					
					case 6:
					{
						system("Color D5");
						break;
					}
					
					case 7:
					{
						system("Color D6");
						break;
					}
					
					case 8:
					{
						system("Color D7");
						break;
					}
					
					case 9:
					{
						system("Color D8");
						break;
					}
					
					case 10:
					{
						system("Color D9");
						break;
					}
					
					case 11:
					{
						system("Color DA");
						break;
					}
					
					case 12:
					{
						system("Color DB");
						break;
					}
					
					case 13:
					{
						system("Color DC");
						break;
					}
					
					case 14:
					{
						system("Color DD");
						break;
					}
					
					case 15:
					{
						system("Color DE");
						break;
					}
					
					case 16:
					{
						system("Color DF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 15:
			{
				switch(font)
				{
					case 1:
					{
						system("Color E0");
						break;
					}
					
					case 2:
					{
						system("Color E1");
						break;
					}
					
					case 3:
					{
						system("Color E2");
						break;
					}
					
					case 4:
					{
						system("Color E3");
						break;
					}
					
					case 5:
					{
						system("Color E4");
						break;
					}
					
					case 6:
					{
						system("Color E5");
						break;
					}
					
					case 7:
					{
						system("Color E6");
						break;
					}
					
					case 8:
					{
						system("Color E7");
						break;
					}
					
					case 9:
					{
						system("Color E8");
						break;
					}
					
					case 10:
					{
						system("Color E9");
						break;
					}
					
					case 11:
					{
						system("Color EA");
						break;
					}
					
					case 12:
					{
						system("Color EB");
						break;
					}
					
					case 13:
					{
						system("Color EC");
						break;
					}
					
					case 14:
					{
						system("Color ED");
						break;
					}
					
					case 15:
					{
						system("Color EE");
						break;
					}
					
					case 16:
					{
						system("Color EF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			case 16:
			{
				switch(font)
				{
					case 1:
					{
						system("Color F0");
						break;
					}
					
					case 2:
					{
						system("Color F1");
						break;
					}
					
					case 3:
					{
						system("Color F2");
						break;
					}
					
					case 4:
					{
						system("Color F3");
						break;
					}
					
					case 5:
					{
						system("Color F4");
						break;
					}
					
					case 6:
					{
						system("Color F5");
						break;
					}
					
					case 7:
					{
						system("Color F6");
						break;
					}
					
					case 8:
					{
						system("Color F7");
						break;
					}
					
					case 9:
					{
						system("Color F8");
						break;
					}
					
					case 10:
					{
						system("Color F9");
						break;
					}
					
					case 11:
					{
						system("Color FA");
						break;
					}
					
					case 12:
					{
						system("Color FB");
						break;
					}
					
					case 13:
					{
						system("Color FC");
						break;
					}
					
					case 14:
					{
						system("Color FD");
						break;
					}
					
					case 15:
					{
						system("Color FE");
						break;
					}
					
					case 16:
					{
						system("Color FF");
						break;
					}
					
					default:
					{
						*status = false;
						break;
					}
				}
				break;
			}
			
			default:
			{
				*status = false;
				break;
			}
		}
			
		if (*status == true)
		{
			
			printf("\t Apakah kamu akan memilih tema ini? (Y/T)\n");
			printf("\t Jawaban: ");
			ulang = toupper(getche());
			if (ulang == 'Y'){
				*status = true;
				break;
			}else{
				*status = false;
			}
		}
	}
}
