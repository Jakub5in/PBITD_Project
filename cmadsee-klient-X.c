/*///////////////////////////////////////////////////////////////////////////////
//PRZYKLAD DYDAKTYCZNY APLIKACJI DZIALAJACEJ W TRYBIE KONSOLI TEKSTOWEJ ANSI C //
/////////////////////////// Wersja 3, kwiecien'2022 /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//PRAWA AUTORSKIE DO PAKIETU,OPRACOWANIE I KOMENTARZE: PROF.JAROSLAW SZYMANDA  //
/////////////////////////////////////////////////////////////////////////////////
//Przyklad syntaktycznie przygotowany do kompilacji ANSI C w Dev-C++ 5.11      //
//WERSJA INSTALACYJNA Dev-C++ 5.11 DO POBRANIA ZE STRONY KURSU                 //
////////////////////////////////////////////////////////////////////////////// //
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//W ramach zajec projektowych wykorzystujacych pakiet Dev-C++ nie tworzymy plikow
//projektu:*.dev;*.cpp;itd. DOPUSZCZALNE SA WYLACZNIE PLIKI ZRODLOWE *.c i *.h //
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/* BARDZO WAZNE - ABY ZACHOWAC PRAWIDLOWE DZIANIE PROGRAMU W BLOKACH:BEGIN-END 
   NIE NALEZY WPROWADZAC ZADNYCH MODYFIKACJI                                   */

/* W opcjach dla linkera:Narzedzia-->Opcje kompilatora--> -static-libgcc -lws2_32 
   W opcjach dla kompilatora:Narzedzia-->Opcje kompilatora-->Kompilator-->     
   Wytwarzanie/optymalizacja kodu-->Zachowaj zgodnosc ze standardem ANSI C:YES */

/* W USTAWIENIACH REGIONALNYCH SYSTEMU "MS WINDOWS" USTAWIC DOMYSLNIE KROPKE "." 
   JAKO SEPARATOR DZIESIETNY W FORMACIE PREZENTACJI LICZB RZECZYWISTYCH !!!    
   ZLE: 3,14159265; DOBRZE: 3.14159265                                         */
   
/* W opisach interfejsu konsoli oraz panelu graficznego raczej nie stosowac polskich znakow diakrytycznych */

#include <windows.h>
#include <time.h>
#include <winsock.h>
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h> 
#include "sistlib.h"  
#include "cmadsee.h"  


/* UWAGA: poczatek bloku glownej funkcji ANSI C "int main(){..." zostal przeniesiony do */
/* pliku "cmadsee.h" w celu zwiekszenFia czytelnosci kodu programu modulu CMADSEE-KLIENT */   

/* Struktura przechowujaca dane sugnalu */
typedef struct {
    int max_val;
    char ch;
    int matrix_col;
} Letter;

/* Funkcje porownujace uzywane do qsort */
int compareMatrixCol(const void *a, const void *b) {
    return ((Letter *)a)->matrix_col - ((Letter *)b)->matrix_col;
}

int compareMaxVal(const void *a, const void *b) {
    return ((const Letter *)b)->max_val - ((const Letter *)a)->max_val;
}

int i, j, m;                /* Zmienne petli for */
char kod1[4];               /* Zmienna przechowujaca obecnie wyliczony kod */
char kod_atak[4];           /* Zmienna przechowujaca uzyty kod */
int matrix[20][26] = {0};   /* Macierz otrzymanego sygnalu */
Letter tab[20];             /* Tablica struktur przechowujaca najwazniejsze dane z sygnalu */

double temp;
quit = '\0';    

/* Zmienne statusu przyciskow */
DOUBLE BitBtn5;
DOUBLE BitBtn4;
DOUBLE BitBtn3; /* przykladowa zmienna wykorzystywana podczas weryfikacji statusu przycisku BitBtn3 */

system("cls"); /* Czyszczenie okna konsoli trybu tekstowego */

StartSISTLab();/* Automatyczne uruchomienie "Panelu Graficznego" SiSTLab30 */
   
/*/////////////////////////////////////////////////////////////////////////////*/

BitBtn3=0; /* przykladowa zmienna wykorzystywana podczas weryfikacji statusu przycisku BitBtn3 */

double FxSyg=50.0; /* FxSyg - czestotliwosc harmonicznej podstawowej sygnalu w Hz */ 
double Fp=2500.0;  /* Fp - czestotliwosc probkowania sygnalu w Hz */

RECONNECT: /* etykieta wykorzystywana podczas automatycznego wznawiania polaczenia z CMADSEE-ENGINE */

   /* Uruchomienie WinSock w wersji 2.2, NIE zmieniac tych parametrow */
   WSAStartup(MAKEWORD(2,2), &wsda);
   
   strcpy(adresip,"156.17.32.93"); /* Adres IPv4 podaje prowadzacy zajecia projektowe */   
   strncpy (szAddress, adresip, strlen(adresip)+1);
   gotoxy(30,8); printf( "CMAD-SEE IPv4: %s ",szAddress);
   iPort = 9090; /* Port wykorzystywany przez modul CMADSEE-ENGINE, podaje prowadzacy zajecia projektowe */

   /* Utworzenie gniazda TCP (portu TCP), w naszych projektach wymagamy protokolu "polaczeniowego" */
   s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
   
   /* Sprawdzenie poprawnosci utworzenia gniazda,trzeba zadbac o jego dostepnosc w systemie MS WINDOWS ! */
   /* "Zapora windows" (firewall), programy antywirusowe np: ESET, itp. */

   /* Sprawdzenie poprawnosci utworzenia gniazda, trzeba zadbac o jego dostepnosc w systemie ! */
   if(s == SOCKET_ERROR)
   {
    system("cls");        
    printf("Blad przy inicjalizacji gniazda %d : ", WSAGetLastError()); 
    system("PAUSE");
    exit(1);       
   }

   /* Informacja o hoscie */
   addr.sin_family = AF_INET;
   addr.sin_port = htons(iPort);
   addr.sin_addr.s_addr = inet_addr(szAddress);
             
   /* Laczenie z modulem CMADSEE-ENGINE*/
   gotoxy(0,6);printf("Laczenie z CMADSEE-ENGINE IPv4 %s Port TCP %d ", szAddress,iPort);
   ret = connect(s, (struct sockaddr *) &addr, sizeof(addr));      
      
   /* Sprawdzenie bledu komunikacji z modulem CMADSEE-ENGINE */
   if(ret == SOCKET_ERROR)
   { 
   gotoxy(0,6);printf("\nBlad przy laczeniu z CMADSEE-ENGINE %d: ",WSAGetLastError());             
   licznik=0;  /* OBLIGATORYJNA zmienna monitorujaca poprawne dzialanie klienta CMADSEE-KLIENT */  
   if (kbhit()){if (getch()=='q')goto koniec;};  /* Zakonczenie dzialajacego klienta */
   }

/* Inicjacja ziarna dla generetora liczb pseudolosowych, ZAWSZE potrzebne gdy korzystamy z rand() */
   srand((unsigned)time(NULL));

/**************************************************************************************************/ 
/* REJESTRACJA KLIENTA, czyli danej grupy projektowej, IDENTYFIKATOR przekazuje prowadzacy zajecia*/
   strcpy(szInBuffer ,"ZVD-131-191\n"); /* Informacja CMADSEE-ENGINE */
/**************************************************************************************************/ 

/* Wysylamy do CMADSEE-ENGINE pytanie o zgode na rejestracje w systemie CMAD-SEE */
   ret = send(s, szInBuffer, strlen(szInBuffer), 0); 
/* Analizujemy otrzymana odpowiedz */   
   ret = recv(s, szInBuffer, sizeof(szInBuffer), 0);

   if(ret!=-1){  
   /* Jesli rejestracja zostanie potwierdzona, to tutaj jest nasz identyfikator klienta */
   iBufferLen = ret; 
   szInBuffer[iBufferLen] = '\0';   
   gotoxy(0,8);printf("REJESTRACJA: %s \n",szInBuffer);}


    /* Zdublowane ustawienie mapy, poniewaz dla jednego nie zawsze sie laduje */
    UstawMape("mapa.gif"); 
    UstawMape("mapa.gif"); 
    
    /* Tabela z etykietami przyciskow */
    UstawTabele(2,650,150,185,25,1,3,60,0,0,20,1,";Atak;Odwolanie;Wyjscie");
    
    /* Przyciski */
    UstawObiekt(15,0,650,175,61,0,0,1,0,0,0); /* Atak */
    UstawObiekt(14,0,711,175,61,0,0,1,0,0,0); /* Odwolanie */
    UstawObiekt(13,0,772,175,61,0,0,1,0,0,0); /* Wyjscie */

do { /* Poczatek glownej petli modulu klienta CMADSEE-KLIENT, patrz instrukcja do zajec projektowych   */                        

   /* Odczytywanie stanu przyciskow */
   CzytajObiekt(15,&BitBtn5);
   CzytajObiekt(14,&BitBtn4);
   CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Odczytywanie statusu przycisku Stop */
   
   /* Tlo paska postepu */
   UstawObiekt(1,0,20,350,815,30,clWhite,1,0,0,0);
   
   /* Zmienna przechowujaca dlugosc paska */
   int pBarLength = 0;
   
   if(licznik < 3000){ /* Jezeli pasek nie jest pelny */
         /* Wyliczanie dlugosci paska uzywajac ratio dlugosc/czas */
         pBarLength = licznik/3.68;
         
         /* Tworzenie paska z kolorem zaleznym od postepu */
         if(licznik < 1000){
               UstawObiekt(2,0,20,350,pBarLength,30,clRed,1,0,0,0);
         }else if(licznik < 2000){
               UstawObiekt(2,0,20,350,pBarLength,30,0x0B70EA,1,0,0,0);
         }else{
               UstawObiekt(2,0,20,350,pBarLength,30,clYellow,1,0,0,0);
         }
   }else{ /* Jezeli pasek pelny */
         /* Tworzenie zielonego paska */
         pBarLength = 815;
         UstawObiekt(2,0,20,350,pBarLength,30,clGreen,1,0,0,0);
   }  
   
   /* Obsluga przyciskow */
   if((int)BitBtn5 != 0){
       BitBtn5 = 0;     
       UstawObiekt(15,0,650,175,61,0,0,1,0,0,0); /* Atak */  
       goto GO_ATAK;             
   }
   if((int)BitBtn4 != 0){ 
       BitBtn4 = 0;
       UstawObiekt(14,0,711,175,61,0,0,1,0,0,0); /* Odwolanie */  
       goto GO_RESET;   
   }
   
   gotoxy(0,9); printf("%i  ",licznik);  licznik++; /* Monitorowanie aktywnosci polaczenia z CMADSEE-ENGINE*/     
   strcpy(SYGNATURA ,"NUL\n"); 
   
  /*****************************************************************************************************/   
  /* Wykorzystanie licznika do okresowej komunikacji CMADSEE-ENGINE z naszym klientem,    */   
  /* w celu anulowania polecenia ostatnio wyslanego do CMADSEE-ENGINE, w tym bloku  */   
  /* aktywnym poleceniem jest jedynie "quit=' '" */   
  if((licznik % 10)==0){quit=' ';}; /* Wazne, NIE ZMIENIAC !,trigerowanie odbioru sygnalu komunikacyjnego */
  /*****************************************************************************************************/
   
switch (quit)
{
  case 'a': /* CYBERATAK "ATK:KOD1:KOD2:KILL:END\n" */
   GO_ATAK: 
            
   /* Przepisanie kodu do kod_atak, ktory bedzie wykorzystany do odwolania ataku */    
   kod_atak[0] = kod1[0];
   kod_atak[1] = kod1[1];
   kod_atak[2] = kod1[2];
   kod_atak[3] = kod1[3];
   
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */                       
   if((ATKon>=0)&&(ATKon<=5)){ATKon++; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   sprintf(SYGNATURA, "ATK:%c%c%c%c:15232:KILL:END\n", kod_atak[0],kod_atak[1],kod_atak[2],kod_atak[3]);
   
   /* Wyswietlenie wyslanej sygnatury */ 
   UstawNapis(1,500,50,400,40,1,1,0,0,0,0,14,SYGNATURA);
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};
  break;
  case 's': 
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */   
   if(STNon==0){STNon=1; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   strcpy(SYGNATURA ,"STN:END\n");            
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};     
  break;
  case 'z': /* ODWOLANIE "ATK:KOD1:KOD2:RESET:END\n" */
   GO_RESET:   
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */                            
   if(ATKon>0){ATKon=0; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */ 
   char syg[24];
   sprintf(syg, "ATK:%c%c%c%c:15232:RESET:END\n", kod_atak[0],kod_atak[1],kod_atak[2],kod_atak[3]);
   printf("\n%s", syg);
   strcpy(SYGNATURA ,syg); 
   
   /* Wyswietlenie wyslanej sygnatury */
   UstawNapis(1,500,50,400,40,1,1,0,0,0,0,14,SYGNATURA);     
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};      
  break;  
  /********************************************* NIE ZMIENIAC! *****************************************/
  case ' ': /*Okresowe odczytywanie probek sygnalu z warstwy komunikacyjnej CMAD-SEE, NIE ZMIENIAC !!! */     			 
   strcpy(SYGNATURA ,"SIN:0,0,0,0,0:0#:END\n");              
   fflush(stdin);quit='\0';
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);     
   gotoxy(0,11);printf("KOMUNIKAT:                                                                     :");     
   STNon=0;       
  break;
  /*****************************************************************************************************/  
  case 'r': /* Wznowienie/odswiezenie na ZYCZENIE polaczenia CMADSEE-KLIENT z CMADSEE-ENGINE */   
   fflush(stdin);quit='\0';
   WSACleanup();  /* Zamkniecie WinSock */       
   goto RECONNECT;
  break;
  /*****************************************************************************************************/  
}         

SelectTiming = recvTimeOutTCP(s, 0, 100000);/* Weryfikacja statusu polaczenia z CMADSEE-ENGINE */
   
switch (SelectTiming)
{
  case 0:
  /* Caly czas czekamy na jakakolwiek odpowiedz ... */
  /*printf("\nCMADSEE-ENGINE: Oczekiwanie na odpowiedz ....\n");*/
  break;
  case -1: 
  /* Nie jest dobrze, trzeba dokladniej zweryfikowac warunki polaczenia z CMADSEE-ENGINE */
  /*printf("\nCMADSEE-ENGINE: Problem z komunikacja: %ld\n", WSAGetLastError());*/
  break;
  default:     
  /* Jest OK, otrzymana odpowiedz przekazujemy do dalszej czesci naszego algorytmu */    
  ret = recv(s, szInBuffer, sizeof(szInBuffer), 0);   

  if(ret!=-1){ /* To nas zabezpiecza przed nieprawidlowym dalszym przetwarzaniem danych */
  iBufferLen = ret;  
  szInBuffer[iBufferLen] = '\0';   /* Do przemyslenia ... */
  
  /* Jezeli mamy zamiar poprawnie interpretowac otrzymywane z CMADSEE-ENGINE dane to         */
  /* NIE nalezy zmieniac znacznikow komunikacyjnych takich jak np: "REP:" oraz ":KON" , itp. */
  
  if ((strstr(szInBuffer,"REP:")>0)&&(strstr(szInBuffer,":KON")>0)){    
    
  gotoxy(0,13);printf("SYGNATURA: %s ",szInBuffer);      
  
  strcpy(komunikat,szInBuffer);      /* Procedura wewnetrzna systemu CMAD-SEE */ 
  dekodowanie(komunikat,Ttab,Ytab);  /* Procedura wewnetrzna systemu CMAD-SEE */      
/* Przyklad prezentacji sygnalu. */
/* W projekcie nalezy uwzglednic takze inne obiekty opisane w "SiSTLab-SEE Instrukcja uzytkownika" */   
   UstawWykres (1,20,90,610,250,0,clBlue,1,50,1, 0.0, 10.0,-200.0,200.0,"Sygnal komunikacyjny","Czas [s]","Aplituda sygnalu [-]",Ttab,Ytab,Ttab,Ytab);  
  
   gendft(Ytab,FxSyg,Fp,Atab, Btab);  /* Procedura wewnetrzna systemu CMAD-SEE */  
   
   for(i=1;i<20;i++){ /* Do przemyslenia ... */ 
   
       /* Odczytywanie stanu przyciskow */
       CzytajObiekt(15,&BitBtn5);
       CzytajObiekt(14,&BitBtn4);
       CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Ponowne odczytywanie statusu przycisku Stop */
       
       Ctab[i]=moduldft(Atab[i],Btab[i]); /* Procedura wewnetrzna systemu CMAD-SEE */
       Dtab[i]=fazadft(Atab[i],Btab[i]); /* Procedura wewnetrzna systemu CMAD-SEE */
       /* Testowy podglad sekwencji znakow ASCII po kryptoanalizie sygnalu komunikacyjnego (ATK:KOD1) */ 
       printf("\n%.5lf\t%c",Ttab[i],dbl2ascii(Ctab[i])); /* dbl2ascii()-procedura wewnetrzna systemu CMAD-SEE */
       
       /* Zliczanie wystapien liter do macierzy */
       matrix[i][dbl2ascii(Ctab[i]) - 'A']++;
       
       /* Wyswietlanie macierzy w cli */
       for(j = 0; j < 26; j++){
             printf("\t%d", matrix[i][j]);    
       }
       printf("\n");
   } /* Dotyczy: for(i=1;i<20;i++){*/
   
   /* Przepisywanie najwiekszych wartosci z kazdej kolumny macierzy do tablicy struktur */
   for(i = 0; i < 19; i++){
        tab[i].max_val= 0;
        tab[i].ch = 0;
        tab[i].matrix_col= i;

        for(j = 0; j < 26; j++){
               if(matrix[i+1][j] > tab[i].max_val){
                      tab[i].max_val = matrix[i+1][j];
                      tab[i].ch = j+'A';
               }      
        }
   }
   
   /* Sortowanie tab malejaco wedlug max_val */
   qsort(tab, 20, sizeof(Letter), compareMaxVal);
   
   /* Przepisanie 4 struktur z tab do top4 */
   Letter top4[4];
   for(i = 0; i < 4; i++){
         top4[i] = tab[i];      
   }
   
   /* Sortowanie top4 rosnaco wedlug matrix_col */
   qsort(top4, 4, sizeof(Letter), compareMatrixCol);
   
   /* Naglowki tabeli wyswietlajacej top4 */
   char table2[300] = ";Litera;Wartosc;Kolumna";
   
   /* Przepisanie liter z top4 do kodu i wartosci z top4 do tabeli */
   for(i = 0; i < 4; i++){
         kod1[i] = top4[i].ch;
         char temp_str[10];
         sprintf(temp_str, ";%c;%i;%i", top4[i].ch, top4[i].max_val, top4[i].matrix_col);
         strcat(table2, temp_str);      
   }
	
	/* Tabela wyswietlajaca kody i licznik */
   char table[50];
   sprintf(table, ";Kod 1;Kod 2;Licznik;%s;15232;%i", kod1, licznik);
   UstawTabele(1,650,90,185,50,2,3,60,0,0,20,1,table);
   
   /* Tabela wyswietlajaca top4 */
   UstawTabele(3,650,210,185,130,5,3,60,0,0,20,1,table2);
      
   /* Wyswietlanie kodow w cli */
   printf("\n\nKod 1:\t%s\nKod 2:\t15232", kod1);
 
 }; /* Dotyczy: ((strstr(szInBuffer,"REP:")*/  
  
 
  if ((strstr(szInBuffer,"CMD:")>0)&&(strstr(szInBuffer,":KON")>0)){      
  /* printf("\a"); /* sygnal dzwiekowy (hardware - PC board speaker) */       
  gotoxy(0,11);printf("KOMUNIKAT:                                                                     :");     
  gotoxy(0,11);printf("KOMUNIKAT: %s\t\t\t\t",szInBuffer);     
  /* ***************************************************************************************************/
  if (strstr(szInBuffer,"FINISH")>0){  /* Komunikat przesylany w przypadku wylaczenia CMADSEE-ENGINE   */  
  quit='q';
  }
  /* ***************************************************************************************************/  
  };   
  break;
  } else { /* Dotyczy: if(ret!=-1){ */
    licznik=0;    /* OBLIGATORYJNA zmienna monitorujaca poprawne dzialanie klienta CMADSEE-KLIENT */    
    WSACleanup(); /* Zamkniecie WinSock */        
    goto RECONNECT;    
    }  
  } /* Dotyczy: switch (SelectTiming)*/ 
 
skok:

if (kbhit()){quit=getch();}
}while ((quit != 'q')&&((int)(BitBtn3) != 1)); /* KONIEC glownej petli modulu klienta CMADSEE-KLIENT */

/*---------------------------------------------------------------------------------------------------*/
/* Na zyczenie bezwarunkowe zakonczenie dzialajacego klienta, mozliwe takze z Panelu graficznego     */
koniec:
/*---------------------------------------------------------------------------------------------------*/

WSACleanup();  /* Zamkniecie WinSock */    
StopSISTLab(); /* Zakonczenie dzialania Panelu Graficznego SiSTLab30 */
consleep(100);
FreeLibrary (hSistlab); /* zwolnienie uchwytu(pamieci) systemowego biblioteki DLL */
FreeLibrary (hSistnum); /* zwolnienie uchwytu(pamieci) systemowego biblioteki DLL */
/* Kod "0" zwracany do systemu operacyjnego po zakonczeniu dzialnia modulu CMADSEE-KLIENT  */
return 0; 
/*---------------------------------------------------------------------------------------------------*/
/* Powodzenia podczas opracowywania projektu */
/* prof. J.Szymanda */
/*---------------------------------------------------------------------------------------------------*/
}
