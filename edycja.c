/*///////////////////////////////////////////////////////////////////////////////
//PRZYKLAD DYDAKTYCZNY APLIKACJI DZIALAJACEJ W TRYBIE KONSOLI TEKSTOWEJ ORAZ  //
//WSPOLDZIALAJACEJ Z PANELEM GRAFICZNYM SISTLAB30 (WERSJA 3.2/2021/11+DLL3.2) //
////////////////////////////////////////////////////////////////////////////////
//PRAWA AUTORSKIE DO PAKIETU,OPRACOWANIE I KOMENTARZE: PROF. JAROSLAW SZYMANDA/
//TESTOWANIE I IMPLEMENTACJE:  DR LESZEK WOZNY                            //
////////////////////////////////////////////////////////////////////////////////
//SiSTLab30-Klient -syntaktycznie przygotowany do kompilacji w Dev-C++ 5.11  //
///////////////////////////////////////////////////////////////////////////////*/

#include <windows.h>
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <math.h> 
#include "sistlib.h" 

int main()
{
/*//////////////////////////////////////////////////////////////////////////////
// INTERFEJS DO OBIEKTOW ZDEFINIOWANYCH W BIBLIOTECE DYNAMICZNEJ "DLL" /////////
////////////////////////////////////////////////////////////////////////////////
///W TYM BLOKU NIE WOLNO MODYFIKOWAC DEFINICJI NAZW TYPOW I FUNKCJI ////////////
//////////////////////////////////////////////////////////////////////////////*/	
HINSTANCE hSistlab = LoadLibrary ("sistlib.dll");
if (hSistlab == NULL) {return 0;} /* sprawdzenie poprawnosci zaladowania biblioteki */
/* ///////////////////////////////////////////////////////////////////////////////////// */
/* ustalenie adresow funkcji w bibliotece "sistlab.dll" */
/* funkcje "Panelu Graficznego" SiSTLab30 */
consleep = (CONSLEEP) GetProcAddress (hSistlab, "ConSleep");
StartSISTLab = (SISTLAB) GetProcAddress (hSistlab, "StartSISTLab");
StopSISTLab = (SISTLAB) GetProcAddress (hSistlab, "StopSISTLab");
UstawMape = (USTMAPE) GetProcAddress (hSistlab, "ansic_UstawMape");
UstawObiekt = (USTOBIEKT) GetProcAddress (hSistlab, "UstawObiekt");
UstawWykres = (USTWYKRES) GetProcAddress (hSistlab, "ansic_UstawWykres");
CzytajObiekt = (CZTOBIEKT) GetProcAddress (hSistlab, "CzytajObiekt");
UstawTekst = (USTTEKST) GetProcAddress (hSistlab, "ansic_UstawTekst");
UstawNapis = (USTNAPIS) GetProcAddress (hSistlab, "ansic_UstawNapis");
ZmienNapis = (ZMENAPIS) GetProcAddress (hSistlab, "ansic_ZmienNapis");
UstawTabele = (USTTABELE) GetProcAddress (hSistlab, "ansic_UstawTabele");
CzytajPozycje = (CZTPOZYCJE) GetProcAddress (hSistlab, "CzytajPozycje");
CzytajSuwak = (CZTSUWAK) GetProcAddress (hSistlab, "CzytajSuwak");
printf("\n"); /* pusty wiersz w celu obnizenia komunikatu specjalnego SiSTLab30 */
/*//////////////////////////////////////////////////////////////////////////////
// KONIEC INTERFEJSU DO OBIEKTOW ZDEFINIOWANYCH W BIBLIOTECE DYNAMICZNEJ "DLL"
//////////////////////////////////////////////////////////////////////////////*/

StartSISTLab();/* uruchomienie "Panelu Graficznego" SiSTLab30 */
consleep(100);
gotoxy(1,23);printf("Dev-C++ 5.1.1: Zakonczenie aplikacji klienta po nacisnieciu 'q'\n");    
/*//////////////////////////////////////////////////////////////////////////////*/

WORD k,j;
DOUBLE BitBtn3,Edit1,Edit2,Wynik;
DWORD cspeed;
CHAR znak[4] = {'|','/','-','\\'}; /* uwaga: pierwszy znak \ w '\\' to znak specjany */
CHAR koniec, s1[80],s2[80]; 

srand(time(NULL));/* uruchomeinie ziarna generatora liczb pseudolosowych*/
/* przykladowa inicjalizacja zmiennych */
koniec='\0';  

BitBtn3=0;Edit1=0.0;Edit2=0.0;
/*/////////////////////////////////////////////////////////////////////////////*/

UstawObiekt(11,0,25,100,0,0,0,1,0,0,0);    /* Przycisk "STOP" - zatrzymanie programu */

UstawObiekt(21,15.0,25,50,0,0,0,1,0,0,0);  /* Pole edycji */
UstawObiekt(22,15.0,100,50,0,0,0,1,0,0,0); /* Pole edycji */

/*/////////////////////////////////////////////////////////////////////////////*/

/*START GLOWNEJ PETLI PROGRAMU "WSPOLDZIALAJACEJ" Z PANELEM GRAFICZNYM SISTLAB30*/
while ((koniec != 'q')&&((int)(BitBtn3) != 1))
{            
cspeed=GetTickCount();

CzytajObiekt(21,&Edit1);
CzytajObiekt(22,&Edit2);
Wynik=Edit1*Edit2;

gotoxy(1,15);printf("Kontrola wartosci Edit1  %5.5f      ",Edit1);
gotoxy(1,16);printf("Kontrola wartosci Edit2  %5.5f      ",Edit2);
gotoxy(1,17);printf("Kontrola wartosci Wynik  %5.5f      ",Wynik);

CzytajObiekt(11,&BitBtn3); /* Stop - zakonczenie programu, powrot do edytora*/

strcpy(s1,"  Wynik mnozenia = ");sprintf(s2,"%0.3lE",Wynik);strcat(s1,s2);
UstawNapis(1,170,50,235,20,1,0,0,clBlack,clWhite,1,10,s1);

if (k>=3) {k=0;} else {k++;} /* sterowanie opcjonalnym znacznikiem znak[k]*/
gotoxy(1,5);printf("%c Czas algorytmu [ms]: %ld   ",znak[k],GetTickCount()-cspeed);

if (kbhit()) {koniec = getch();} /* po nacisnieciu, odczytanie klawisza */

} /* zakonczenie petli "while {}" */

StopSISTLab(); /* zakonczenie dzialania Panelu Graficznego SiSTLab30 */
consleep(100);
FreeLibrary (hSistlab); /* zwolnienie uchwytu(pamieci) systemowego biblioteki dynamicznej DLL */
return EXIT_SUCCESS; /* zakonczenie procesu konsoli trybu tekstowego */
}
