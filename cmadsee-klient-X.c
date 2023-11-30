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
/* pliku "cmadsee.h" w celu zwiekszenia czytelnosci kodu programu modulu CMADSEE-KLIENT */   


int i,j;

double temp;
quit = '\0';    

   
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

   UstawObiekt(13,0,747,345,0,0,0,1,0,0,0);    /*Panel graficzny --> Ustawienie przycisku    "STOP"  */    
   UstawObiekt(13,0,747,345,0,0,0,1,0,0,0);    /*Panel graficzny --> Ustawienie przycisku    "STOP"  */       

do { /* Poczatek glownej petli modulu klienta CMADSEE-KLIENT, patrz instrukcja do zajec projektowych   */                        

   CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Odczytywanie statusu przycisku Stop */
   
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
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */                       
   if((ATKon>=0)&&(ATKon<=5)){ATKon++; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   strcpy(SYGNATURA ,"ATK:ZZZZ:12345:KILL:END\n");     
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};   
  break;
  case 's': 
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */   
   if(STNon==0){STNon=1; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   strcpy(SYGNATURA ,"STN:END\n");            
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};     
  break;
  case 'z': /* ODWOLANIE "ATK:KOD1:KOD2:RESET:END\n" */   
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */                            
   if(ATKon>0){ATKon=0; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */ 
   strcpy(SYGNATURA ,"ATK:ZZZZ:12345:RESET:END\n");       
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
  attack(szInBuffer);
/* Przyklad prezentacji sygnalu. */
/* W projekcie nalezy uwzglednic takze inne obiekty opisane w "SiSTLab-SEE Instrukcja uzytkownika" */   
  UstawWykres (1,30,100,700,250,0,clBlue,1,50,1, 0.0, 10.0,-200.0,200.0,"Sygnal komunikacyjny","Czas [s]","Aplituda sygnalu [-]",Ttab,Ytab,Ttab,Ytab);  
  
  gendft(Ytab,FxSyg,Fp,Atab, Btab);  /* Procedura wewnetrzna systemu CMAD-SEE */       
   

   
   for(i=1;i<20;i++){ /* Do przemyslenia ... */ 
 
   CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Ponowne odczytywanie statusu przycisku Stop */
 	
   Ctab[i]=moduldft(Atab[i],Btab[i]); /* Procedura wewnetrzna systemu CMAD-SEE */        	
   Dtab[i]=fazadft( Atab[i],Btab[i]); /* Procedura wewnetrzna systemu CMAD-SEE */
/* Testowy podglad sekwencji znakow ASCII po kryptoanalizie sygnalu komunikacyjnego (ATK:KOD1) */ 
/*printf("\n%.5lf\t%c",Ttab[i],dbl2ascii(Ctab[i])); *//* dbl2ascii()-procedura wewnetrzna systemu CMAD-SEE */        
    
  } /* Dotyczy: for(i=1;i<20;i++){*/  

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



/* Funkcja dostaje przechwycony komunikat z sygnalem i bedzie zwracac uzyskany z niego kod dostepu */
double attack(char text[]){
       /* To wszystko tutaj rozklada tekst na tablice wartosci sygnalu */
       int i = 0;
       char *part = strtok(text, ",");
       char *array[52];
       char *x[52];
       char *t[52];
       while(part != NULL){
                  array[i++] = part;
                  part = strtok(NULL, ",");
       }
       for(i = 0; i<52; ++i){
             char *part2;
             x[i] = strtok(array[i], ":");
             t[i] = strtok(NULL, ":");
       }
       /* x[] i t[] przechowuja nasz sygnal, trzeba teraz z tego zrobic widmo sygnalu"
}
