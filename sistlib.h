/*///////////////////////////////////////////////////////////////////////////////
//PRZYKLAD DYDAKTYCZNY APLIKACJI DZIALAJACEJ W TRYBIE KONSOLI TEKSTOWEJ ORAZ  //
//WSPOLDZIALAJACEJ Z PANELEM GRAFICZNYM SISTLAB30 (WERSJA 3.2/2021/11+DLL3.2) //
////////////////////////////////////////////////////////////////////////////////
//PRAWA AUTORSKIE DO PAKIETU,OPRACOWANIE I KOMENTARZE: DR INZ.JAROSLAW SZYMANDA/
//TESTOWANIE I IMPLEMENTACJE:  DR INZ.LESZEK WOZNY                            //
////////////////////////////////////////////////////////////////////////////////
//SiSTLab30-Klient -syntaktycznie przygotowany do kompilacji w Dev-C++ 5.11  //
///////////////////////////////////////////////////////////////////////////////*/
/*sprawdzic czy w opcjach dla linkera: Narzedzia-->Opcje kompilatora --> -static-libgcc */

/*//////////////////////////////////////////////////////////////////////////////
// INTERFEJS DO OBIEKTOW ZDEFINIOWANYCH W BIBLIOTECE DYNAMICZNEJ "DLL" /////////
////////////////////////////////////////////////////////////////////////////////
///W TYM BLOKU NIE WOLNO MODYFIKOWAC DEFINICJI NAZW TYPOW I FUNKCJI ////////////
//////////////////////////////////////////////////////////////////////////////*/

typedef double DBLARRAY[500];      
typedef WORD (__stdcall *CONSLEEP)(INT);CONSLEEP consleep;
typedef WORD (__stdcall *USTMAPE)(PCHAR);USTMAPE UstawMape;
typedef WORD (__stdcall *SISTLAB)();SISTLAB StartSISTLab,StopSISTLab;
typedef WORD (__stdcall *USTOBIEKT)(WORD,double,long int,long int,long int,long int,long int,long int,
             long int,long int,long int); 
USTOBIEKT UstawObiekt;
typedef WORD (__stdcall *USTWYKRES)(long int,long int,long int,long int, /*we*/
                                  long int,long int,long int,long int,   /*we*/ 
                                  long int,long int,                     /*we*/       
                                  double,double,double,double,           /*we*/
                                  PCHAR,PCHAR,PCHAR,                     /*we*/
                                  DBLARRAY,DBLARRAY,DBLARRAY,DBLARRAY);  /*we*/
USTWYKRES UstawWykres;

typedef WORD (__stdcall *CZTOBIEKT)(long int,double *a);CZTOBIEKT CzytajObiekt;
typedef WORD (__stdcall *CZTPOZYCJE)(long int *x,long int *y);CZTPOZYCJE CzytajPozycje;
typedef WORD (__stdcall *CZTSUWAK)(long int,long int *p);CZTSUWAK CzytajSuwak;

typedef WORD (__stdcall *USTNAPIS)(long int,long int,long int,long int, /*we*/
                                   long int,long int,long int,long int, /*we*/
                                   long int,long int,long int,long int, /*we*/
                                   PCHAR);                              /*we*/
USTNAPIS UstawNapis;

typedef WORD (__stdcall *ZMENAPIS)(long int,PCHAR);                     /*we*/
ZMENAPIS ZmienNapis;

typedef WORD (__stdcall *USTTEKST)(long int,long int,long int,long int, /*we*/
                                   long int,long int,long int,long int, /*we*/
                                   long int,long int,long int,long int, /*we*/
                                   PCHAR);                              /*we*/
USTTEKST UstawTekst;

typedef WORD (__stdcall *USTTABELE)(long int,long int,long int,long int, /*we*/
                                    long int,long int,                   /*we*/
                                    long int,long int,long int,long int, /*we*/
                                    long int,long int,PCHAR);            /*we*/
USTTABELE UstawTabele;

void gotoxy(int x, int y)
 {
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 }

/*//////////////////////////////////////////////////////////////////////////////
// KONIEC INTERFEJSU DO OBIEKTOW ZDEFINIOWANYCH W BIBLIOTECE DYNAMICZNEJ "DLL"
//////////////////////////////////////////////////////////////////////////////*/

/* Panel Graficzny - kolory obiektow */
static const long int clBlack=0x000000;   
static const long int clMaroon=0x000080;
static const long int clGreen=0x008000;
static const long int clOlive=0x008080;
static const long int clNavy=0x800000;
static const long int clPurple=0x800080;
static const long int clTeal=0x808000;
static const long int clGray=0x808080;
static const long int clSilver=0xC0C0C0;
static const long int clRed=0x0000FF;
static const long int clLime=0x00FF00;
static const long int clYellow=0x00FFFF;
static const long int clBlue=0xFF0000;
static const long int clFuchsia=0xFF00FF;
static const long int clAqua=0xFFFF00;
static const long int clLtGray=0xC0C0C0;
static const long int clDkGray=0x808080;
static const long int clWhite=0xFFFFFF;
static const long int clMoneyGreen=0xC0DCC0;
static const long int clSkyBlue=0xF0CAA6;
static const long int clCream=0xF0FBFF;
static const long int clMedGray=0xA4A0A0;
static const long int clNone=0x1FFFFFFF;
static const long int clDefault=0x20000000;
/*/////////////////////////////////////////////////////////////////////////////*/
