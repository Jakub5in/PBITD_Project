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

WORD Num,k,j;
DOUBLE ext[15];
DOUBLE BitBtn1,BitBtn3;
DWORD cspeed;
CHAR znak[4] = {'|','/','-','\\'}; /* uwaga: pierwszy znak \ w '\\' to znak specjany */
CHAR koniec,s10[1024],s20[1024]; 
long int kolor;

srand(time(NULL));/* uruchomeinie ziarna generatora liczb pseudolosowych */
/* przykladowa inicjalizacja zmiennych  */
koniec='\0';  
BitBtn1=0;BitBtn3=0;
/*/////////////////////////////////////////////////////////////////////////////*/
UstawObiekt(11,0,113,55,0,0,0,1,0,0,0);    /* Przycisk kontrolny */
UstawObiekt(13,0,213,55,0,0,0,1,0,0,0);    /* Przycisk "STOP" - zatrzymanie programu */
/*/////////////////////////////////////////////////////////////////////////////*/

/* START GLOWNEJ PETLI PROGRAMU "WSPOLDZIALAJACEJ" Z PANELEM GRAFICZNYM SISTLAB30 */
while ((koniec != 'q')&&((int)(BitBtn3) != 1))
{            
cspeed=GetTickCount();
gotoxy(1,15);printf("Kontrola wartosci BitBtn1  %d ",(int)(BitBtn1));

CzytajObiekt(11,&BitBtn1); /* Przycisk kontrolny */
CzytajObiekt(13,&BitBtn3); /* Stop - zakonczenie programu, powrot do edytora */

/* symulacja  UstawTabele(11, ......) */
/* przykladowa prezentacja wartosci rzeczywistych w obiekcie UstawTabela(1, ...) */
for (j=0;j<15;j++){ext[j]=(rand()%1000)*sin((rand()%10));} /* generowanie wartosci losowych */


strcpy(s20,";A;B;C;D");
for (j=0;j<9;j++){ 
if ((int)(BitBtn1)==1){
ZmienNapis(1,"AWARIA SYSTEMU !");kolor=clRed;
sprintf(s10,";%15.2lf;%15.2lf;%15.2lf;%15.2lf",ext[rand()%14],0.0,ext[rand()%14],0.0);
}else {kolor=clBlack;
UstawNapis(1,50,100,450,35,1,0,0,clBlack,clSkyBlue,1,10,"Parametry monitorowania wezlow stacji Pasikurowice");
sprintf(s10,";%15.2lf;%15.2lf;%15.2lf;%15.2lf",ext[rand()%14],ext[rand()%14],ext[rand()%14],ext[rand()%14]);}
strcat(s20,s10);
}

UstawTabele(1,50,120,450,220,10,4,104,kolor,1,1,1,s20); 

if (k>=3) {k=0;} else {k++;} /* sterowanie opcjonalnym znacznikiem znak[k] */
gotoxy(1,5);printf("%c Czas algorytmu [ms]: %ld   ",znak[k],GetTickCount()-cspeed);

if (kbhit()) {koniec = getch();} /* po nacisnieciu, odczytanie klawisza */

} /* zakonczenie petli "while {}" */

StopSISTLab(); /* zakonczenie dzialania Panelu Graficznego SiSTLab30 */
consleep(100);
FreeLibrary (hSistlab); /*zwolnienie uchwytu(pamieci) systemowego biblioteki DLL  */  
return EXIT_SUCCESS; /* zakonczenie procesu konsoli trybu tekstowego */
}
