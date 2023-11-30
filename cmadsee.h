/*** BEGIN ******** BEGIN ********** BEGIN ********* BEGIN ********** BEGIN ********    */ 
/*  zalecene jest by w tym bloku, az do jego zakonczenia:  ********** END **********    */
/*  nic nie zmieniac bez uprzedniego przemyslenia poprawnosci dzialania calego programu */

 typedef double WEKTOR[1000];      
 typedef double (__stdcall *GENDFT)(WEKTOR,double,double,WEKTOR,WEKTOR); GENDFT gendft;  
 typedef double (__stdcall *MODULDFT)(double,double); MODULDFT moduldft; 
 typedef double (__stdcall *FAZADFT)(double,double); FAZADFT fazadft; 
 typedef double (__stdcall *DEKODOWANIE)(PCHAR,WEKTOR,WEKTOR); DEKODOWANIE dekodowanie; 
 typedef char (__stdcall *DBL2ASCII)(double); DBL2ASCII dbl2ascii; 
 
 WEKTOR Ttab,Ytab,Atab,Btab,Ctab,Dtab;	
 char komunikat[4096]; 
 int ATKon=0;
 int STNon=0;
 
 int recvTimeOutTCP(SOCKET socket, long sec, long usec)
 { 
 struct timeval timeout;
 struct fd_set fds;
 timeout.tv_sec = sec;
 timeout.tv_usec = usec;
 FD_ZERO(&fds);
 FD_SET(socket, &fds);
 return select(0, &fds, 0, 0, &timeout);
}
int main()
{
	
HINSTANCE hSistlab = LoadLibrary ("sistlib.dll");
if (hSistlab == NULL) {return 0;} /* Sprawdzenie poprawnosci zaladowania biblioteki	 */
HINSTANCE hSistnum = LoadLibrary ("sistnum.dll");
if (hSistnum == NULL) {return 0;}  /* Sprawdzenie poprawnosci zaladowania biblioteki  */

/*//////////////////////////////////////////////////////////////////////////////
// INTERFEJS DO OBIEKTOW ZDEFINIOWANYCH W BIBLIOTECE DYNAMICZNEJ "DLL" /////////
////////////////////////////////////////////////////////////////////////////////
///W TYM BLOKU NIE WOLNO MODYFIKOWAC DEFINICJI NAZW TYPOW I FUNKCJI ////////////
/* ////////////////////////////////////////////////////////////////////////////////// */
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

gendft = (GENDFT) GetProcAddress (hSistnum, "GENDFTC");
moduldft = (MODULDFT) GetProcAddress (hSistnum, "moduldft");
fazadft = (FAZADFT) GetProcAddress (hSistnum, "fazadft");
dekodowanie = (DEKODOWANIE) GetProcAddress (hSistnum, "dekodowanie");
dbl2ascii = (DBL2ASCII) GetProcAddress (hSistnum, "Dbl2ASCIIC");


   WSADATA wsda;				/* Informacja zwracana przez WSAStartup */
   struct hostent *host;		/* Informacja CMADSEE-ENGINE */
   char szMessage[80];			/* Bufor wykorzystywany do komunikacji z CMADSEE-ENGINE */
   int iMessageLen;				/* Informacja CMADSEE-ENGINE */
   int ret;						/* Informacja CMADSEE-ENGINE */
   char szInBuffer[4096];		/* Informacja CMADSEE-ENGINE */	
   int iBufferLen;				/* Informacja CMADSEE-ENGINE */
   char szAddress[64];			/* Informacja CMADSEE-ENGINE */
   int iPort;					/* Informacja CMADSEE-ENGINE */
   int licznik = 0;				/* Informacja CMADSEE-ENGINE */
   char adresip[20]; 			/* Informacja CMADSEE-ENGINE */
   char quit;  					/* Informacja CMADSEE-ENGINE */
   char SYGNATURA[80];   		/* Informacja CMADSEE-ENGINE */
   char t1[20];      			/* Informacja CMADSEE-ENGINE */
   struct timeval timeout;		/* Informacja CMADSEE-ENGINE */	
   
   SOCKET s;		 			/* Uzywane gniazdo */
   SOCKADDR_IN addr; 			/* Adres hosta */
   
   int iResult = 0;				/* Informacja CMADSEE-ENGINE */
   BOOL bOptVal = FALSE;		/* Informacja CMADSEE-ENGINE */
   int bOptLen = sizeof (BOOL);	/* Informacja CMADSEE-ENGINE */
   int iOptVal = 0;				/* Informacja CMADSEE-ENGINE */
   int iOptLen = sizeof (int);  /* Informacja CMADSEE-ENGINE */  
   int SelectTiming;			/* Informacja CMADSEE-ENGINE */	
   double attack(char text[]);
/* zakonczenie zastrzezonego bloku, ktorego poczatek byl oznaczony:  ***** BEGIN ******** */
/*** END ******** END ********** END ********* END ********** END ********* END ******    */  
