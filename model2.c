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
UstawMape("model1.emf"); /* opcjonalne wczytanie mapy (schematu) */
gotoxy(1,23);printf("Dev-C++ 5.1.1: Zakonczenie aplikacji klienta po nacisnieciu 'q'\n");    
/*//////////////////////////////////////////////////////////////////////////////*/

DBLARRAY ax,ay1,ay2; 
WORD Num,nr,x,y,w,h,c,v,k,r,j,m,Poziom1;
DOUBLE typ, BitBtn1,BitBtn2,BitBtn3,BitBtn4,BitBtn5,Edit1;
DOUBLE ext[15];
DWORD cspeed;
CHAR znak[4] = {'|','/','-','\\'}; /* uwaga: pierwszy znak \ w '\\' to znak specjany */
CHAR koniec, s1[80],s2[80],s3[80],s4[80], s5[80], s10[1024],s20[1024];
long int Suwak1,Suwak2,PozX,PozY,Kolor;

srand(time(NULL));/* uruchomeinie ziarna generatora liczb pseudolosowych */
/* przykladowa inicjalizacja zmiennych */
koniec='\0';  
k=0;x=190;y=396;r=0;typ=4;nr=0;BitBtn1=0;BitBtn2=0;BitBtn2=0;BitBtn3=0;Edit1=0;
/*/////////////////////////////////////////////////////////////////////////////*/
UstawObiekt(11,0,609,652,0,0,0,1,0,0,0);   /*Przycisk "sterowanie automatyka" */
UstawObiekt(12,0,307,652,0,0,0,1,0,0,0);   /*Przycisk "aktywnosc procesu"     */
UstawObiekt(13,0,721,652,0,0,0,1,0,0,0);   /*Przycisk "STOP" - zatrzymanie programu */
UstawObiekt(14,0,321,457,0,0,0,1,0,0,0);   /*Przycisk "Zawory turbogeneratora (8)" -schemat */
UstawObiekt(15,0,1470,570,0,0,0,1,0,0,0);  /*Przycisk "Zawory turbogeneratora (8)" -algorytm */

UstawObiekt(4,0,911,831,100,5,clRed,1,0,0,0);    /* Oznaczenie poziomu bezpieczenstwa 1 */
UstawObiekt(5,0,1040,831,100,5,clYellow,1,0,0,0);/* Oznaczenie poziomu bezpieczenstwa 2 */
UstawObiekt(6,0,1060,831,25,5,clYellow,1,0,0,0); /* Oznaczenie poziomu bezpieczenstwa 2 */

UstawObiekt(21,190.0,1205,544,0,0,0,1,0,0,0); /* Pole edycji "Zmien nastawy" -algorytm */

UstawObiekt(31,0,500,717,350,20,1,1,0,80,45); /* Suwak poziomy */   
UstawObiekt(32,1,1270,600,20,740,1,1,0,240,190); /* Suwak pionowy */   

/*////////////////////////////////////////////////////////////////////////////// */

/* START GLOWNEJ PETLI PROGRAMU "WSPOLDZIALAJACEJ" Z PANELEM GRAFICZNYM SISTLAB20*/
while ((koniec != 'q')&&((int)(BitBtn3) != 1))
{            
cspeed=GetTickCount();
gotoxy(4,15);printf("Status wybranych zdarzen kontrolnych %d %d %5.5f      ", (int)(BitBtn1),(int)(BitBtn2),Edit1);

CzytajSuwak(31,&Suwak1);
CzytajSuwak(32,&Suwak2);
UstawObiekt(21,240-Suwak2,1205,544,0,0,0,1,0,0,0);

CzytajPozycje(&PozX,&PozY);

if ((PozX>530)&&(PozX<710)&&(PozY>750)&&(PozY<836)){Kolor=clYellow;} else {Kolor=clGreen;};
if (BitBtn1==0){ UstawObiekt(8,2,550,750,150,Suwak1,Kolor,1,0,0,0);}
else {UstawObiekt(8,1,550,750,Suwak1,Suwak1,Kolor,1,0,0,0);}


/* przyklad symulacji ruchu obiektu graficznego (tutaj dla UstawObiekt(1, .....) */
/* BLOK GRAF*/
/* wylaczenie/zalaczenie 'zaworow turbogeneratora" poprzez dwa przyciski (XOR !!!) */
if (((int)(BitBtn4)==0)^((int)(BitBtn5)==1)) /* ^ to xor */
{ /*AA */
  if ((int)(BitBtn2)==0) /* aktywnosc (szybkosc) obiektu .... */
    { 
    switch( r )
    {
    case 0: {x=x+1;typ=4;if (x>350){ r=2;}/* prawo-->dol */
            break;}       
    case 1: {x=x-1;typ=4;if (x<316){y=560;} if (x<180){ r=3;} /*lewo-->gora */
            break;}       
    case 2: {y=y+1;typ=1;if (y>505) { r=1;}/* dol-->lewo */
            break;}       
    case 3: {y=y-1;typ=1;if (y<490){x=160;} if (y<386){ r=0;}/* gora-->prawo */
            break;} 
    }
} else {
    switch( r )
    {
    case 0: {x=x+1;typ=4;if (x>350){ r=2;}/* prawo-->dol */
            break;}       
    case 1: {x=x-1;typ=4;if (x<316){y=560;} if (x<180){ r=3;}/*lewo-->gora */
            break;}       
    case 2: {y=y+1;typ=1;if (y>505) { r=1;}/* dol-->lewo */
            break;}       
    case 3: {y=y-1;typ=1;if (y<490){x=160;} if (y<386){ r=0;}/* gora-->prawo */
            break;} 
   }  
}   

j=rand()%200;
if (j>Poziom1){
              UstawObiekt(3,0,927 ,831-j,25,j,clRed,1,0,0,0);
              m=1+rand()%200;
              UstawObiekt(5,0,1040,831-m,100,5,clYellow,1,0,0,0);
              UstawObiekt(6,0,1060,831-m,25,m,clYellow,1,0,0,0);               
              } else {
              UstawObiekt(3,0,927,831-j,25,j,clGreen,1,0,0,0);       
              }               
       
} /* AA */
else {
     /* "Zerowanie" niektorych obiektow podczas awarii (zamkniecia zaworu) */
     UstawObiekt(3,0,927,831,25,5,clGreen,1,0,0,0);
     UstawObiekt(1,typ,0,0,0,0,clYellow,1,0,0,0); /* sterowanie obiektem zmiana koloru podczas awarii */
     UstawObiekt(5,0,1040,831,100,5,clYellow,1,0,0,0);/* Oznaczenie poziomu bezpieczenstwa 2, zerowanie */
     UstawObiekt(6,0,1060,831,25,5,clYellow,1,0,0,0); /* Oznaczenie poziomu bezpieczenstwa 2, zerowanie */
     }
/* KONIEC GRAF*/            

/* przykladowa prezentacja wartosci rzeczywistych w obiekcie UstawTabela(1, ...) */
for (j=0;j<15;j++){ext[j]=(rand()%1000)*sin((rand()%10));} /* generowanie wartosci losowych */
UstawNapis(1,50,690,450,35,1,0,0,clBlack,clSkyBlue,1,10,"Parametry monitorowania wezlow stacji Pasikurowice");
strcpy(s20,";A;B;C;D");
for (j=0;j<5;j++){ 
sprintf(s10,";%15.2lf;%15.2lf;%15.2lf;%15.2lf",ext[rand()%14],ext[rand()%14],ext[rand()%14],ext[rand()%14]);
strcat(s20,s10);
}
UstawTabele(1,50,720,450,120,6,4,104,clBlack,1,1,1,s20);
  
/* przyklad wylaczony w model2.c */
/* przykladowa prezentacja wartosci rzeczywistych w obiekcie UstawTekst(1, ...) */
/*
sprintf(s1,"|%+10.3e |%+10.3e ",fabs(ext[1]),ext[11]);
sprintf(s2,"|%+10.3e |%+10.3e ",fabs(ext[2]),ext[6]);
sprintf(s3,"|%+10.3e |%+10.3e ",fabs(ext[5]),ext[3]);
sprintf(s4,"|%+10.3e |%+10.3e ",fabs(ext[10]),ext[14]);

UstawTekst(2,532,690,305,150,1, 1,1 ,clBlack,clOlive,6,0, "Moc zespolona turbogeneratora");
UstawTekst(2,532,690,305,150,1, 2,1 ,clBlack,clYellow ,0,0, "      P           Q          ");
UstawTekst(2,532,690,305,150,1, 3,1 ,clBlack,clWhite ,0,0,s1);
UstawTekst(2,532,690,305,150,1, 4,1 ,clBlack,clWhite ,0,0,s2);
UstawTekst(2,532,690,305,150,1, 5,1 ,clBlack,clWhite ,0,0,s3);
UstawTekst(2,532,690,305,150,1, 6,1 ,clBlack,clWhite ,0,0,s4);
*/

/* przykladowa prezentacja wartosci rzeczywistych w obiekcie UstawObiekt(1, ...) */
UstawObiekt(1,typ,x,y,Suwak1,Suwak1,clGreen,1,0,0,0); /* sterowanie obiektem ...  */

/* przyklad symulacji ruchu obiektu graficznego (tutaj dla UstawObiekt(2, .....) */
if ((int)(BitBtn1)==1){ UstawObiekt(2,typ,585,375,15+x/5,15+x/5,clBlue,1,0,0,0);
} else {UstawObiekt(2,typ,585,375,15+x/5,15+x/5,clBlue,0,0,0,0);}

/* przykladowa interpretacja przyciskow w modelu (schemacie projektu) */
CzytajObiekt(11,&BitBtn1); /* "wlaczenie/wylaczenie" automatyki */
CzytajObiekt(12,&BitBtn2); /* "wlaczenie/wylaczenie" aktywnosci */
CzytajObiekt(13,&BitBtn3); /* Stop - zakonczenie algorytmu (programu) */
CzytajObiekt(14,&BitBtn4); /* Zawory turbogeneratora (8) -schemat */
CzytajObiekt(15,&BitBtn5); /* Zawory turbogeneratora (8) -algorytm */

/* przykladowe pole odczytu i edycji wartosci liczb rzeczywistych (typ double) */
CzytajObiekt(21,&Edit1); /* sterowanie obiektem ... */
Poziom1=(int)(Edit1);
UstawObiekt(4,0,911,831-Poziom1,100,5,clRed,1,0,0,0);  /* Oznaczenie poziomu bezpieczenstwa */
Suwak2=Poziom1;
UstawObiekt(32,1,1270,600,20,140,1,1,0,200,240-Suwak2); /* Suwak pionowy */   

/* symulacja "dynamicznego" wykresu UstawWykres(11, ......) */
Num=20;
for (j=0;j<=Num-1;j++){
 ax[j]=j;
/* wylaczenie/zalaczenie 'zaworow turbogeneratora" poprzez dwa przyciski (XOR !!!) */
if (((int)(BitBtn4)==0)^((int)(BitBtn5)==1)){ ay1[j]=j*0.23*(rand()%9);} else {ay1[j]=0;}      
}
UstawWykres(11,860,103,312,200,0,clBlue,1,Num,1, 0.0, 18.0,0.0,25.0,"Dystrybucja energii elektrycznej","Punkty odbioru","Energia [kWh]",ax,ay1,ax,ay1);

if (ay1[10]>18) {/*AX*/  /*Przykladowa symulacja zdarzenia */
Num=20;
for (j=0;j<=Num-1;j++){
   ax[j]=j*0.23;
   ay1[j]=j*0.23*(rand()%9);
   ay2[j]=j*0.15*(rand()%9);
   }
UstawWykres(1,860,326,312,200,clRed,clBlue,1,Num-1,1, 0.0, 10.0,0.0,10.0,"Prognoza zuzycia energii","Znormalizowane punkty odbioru","Energia [kWh]",ax,ay1,ax,ay2);
}/*AX*/

if (k>=3) {k=0;} else {k++;} /* sterowanie opcjonalnym znacznikiem znak[k] */
gotoxy(1,5);printf("%c Czas algorytmu [ms]: %ld   ",znak[k],GetTickCount()-cspeed);

if (kbhit()) {koniec = getch();} /* po nacisnieciu, odczytanie klawisza, to rozwiazanie nie wstrzymuje petli podczas odczytu klawiszy */

} /* zakonczenie petli "while {}" */

StopSISTLab(); /* zakonczenie dzialania Panelu Graficznego SiSTLab30 */
consleep(100);
FreeLibrary (hSistlab); /* zwolnienie uchwytu(pamieci) systemowego biblioteki dynamicznej DLL  */  
return EXIT_SUCCESS; /* zakonczenie procesu konsoli trybu tekstowego */
}
