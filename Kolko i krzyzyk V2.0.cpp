#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

#define NIEBIESKI 8700  /* Numer specjalny koloru. */
#define ZIELONY 8701    /* Numer specjalny koloru. */
#define CZERWONY 8702   /* Numer specjalny koloru. */
#define ZOLTY 8703      /* Numer specjalny koloru. */
#define BLEKIT 8704     /* Numer specjalny koloru. */
#define FIOLETOWY 8705  /* Numer specjalny koloru. */


using namespace std;

typedef COORD WskaznikNaMapie;

void koloruj(int KOLOR)
{
	if ( KOLOR == 8700)
	{
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
    
    if( KOLOR == 8701 )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    }
    
    if( KOLOR == 8702 )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED | FOREGROUND_INTENSITY );
    }
    
    if( KOLOR == 8703 )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
    }
    
    if( KOLOR == 8704 )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    }
    
    if( KOLOR == 8705 )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
    
}


void wyswietl_plansze( )  // rysuje plansze
{
	cout<<"   |   |     "<<endl;
	cout<<"---+---+---"<<endl;
	cout<<"   |   |     "<<endl;
	cout<<"---+---+---"<<endl;
	cout<<"   |   |     "<<endl;
}

int menu()
{
	char wybor;
	
	koloruj(ZIELONY);
	cout<<"\t\tGRA W KOLKO I KRZYZYK by Wienio"<<endl<<endl;
	
	koloruj(ZOLTY);
	cout<<"Co chcesz zrobic?"<<endl;
	
	koloruj(NIEBIESKI);
	cout<<"1)Zacznij gre!"<<endl;
		
	koloruj(CZERWONY);
	cout<<"2)Skoncz gre!";
	
	cout<<endl<<endl;
	
	wybor=getch();
	
	
	if(static_cast<int>(wybor)==49)
	{
		system("cls");
			
		wyswietl_plansze();
		return false;
		
	}
	else
	{
		system("cls");
		koloruj(CZERWONY);
		cout<<"Do zobaczenia!";
		return true;
	}
	
}

void ZmienPozycjeKursora( WskaznikNaMapie Wspolrzedne )
{
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Wspolrzedne );
}

void moja_tura(int * tab, int & licznik, WskaznikNaMapie &krzyzyk, WskaznikNaMapie &wyjsciowy, char * pomocnicza, WskaznikNaMapie & BLAD)
{
	char liczba;
	
	liczba=getch();
	
	if(static_cast<int>(liczba)!=49 && static_cast<int>(liczba)!=50 && static_cast<int>(liczba)!=51 && static_cast<int>(liczba)!=52 && static_cast<int>(liczba)!=53
	&& static_cast<int>(liczba)!=54 && static_cast<int>(liczba)!=55 && static_cast<int>(liczba)!=56 && static_cast<int>(liczba)!=57)
	{
		ZmienPozycjeKursora(BLAD);
		koloruj(CZERWONY);
		cout<<"BLAD, podaj wartosc wlasciwa (1-9) !";
		moja_tura(tab,licznik,krzyzyk,wyjsciowy,pomocnicza,BLAD);
	}
	
	for(int i = 0 ; i < licznik ; ++i)
	{
		if( tab[i] == (static_cast<int>(liczba)-48) )
		{
			liczba=getch();
			i=-1;
		}
	}
	int konwersja=(static_cast<int>(liczba))-48;
	
	tab[licznik]=konwersja;
	++licznik;
	
	pomocnicza[static_cast<int>(liczba)-49]='X';
	
	if(static_cast<int>(liczba) == 49 || static_cast<int>(liczba) == 50 || static_cast<int>(liczba) == 51 )
	{
		krzyzyk.Y=0;
		
		if( static_cast<int>(liczba) == 49)
		{
			krzyzyk.X=1;
		}
		
		if(static_cast<int>(liczba) == 50)
		{
			krzyzyk.X=5;
		}
		
		if(static_cast<int>(liczba) == 51)
		{
			krzyzyk.X=9;
		}
	}
	else if ( static_cast<int>(liczba) == 52 || static_cast<int>(liczba) == 53 || static_cast<int>(liczba) == 54 )
	{
		krzyzyk.Y=2;
		
		if( static_cast<int>(liczba) == 52)
		{
			krzyzyk.X=1;
		}
		
		if(static_cast<int>(liczba) == 53)
		{
			krzyzyk.X=5;
		}
		
		if(static_cast<int>(liczba) == 54)
		{
			krzyzyk.X=9;
		}
	}
	else if ( static_cast<int>(liczba) == 55 || static_cast<int>(liczba) == 56 || static_cast<int>(liczba) == 57 )
	{
		krzyzyk.Y=4;
		
		if( static_cast<int>(liczba) == 55)
		{
			krzyzyk.X=1;
		}
		
		if(static_cast<int>(liczba) == 56)
		{
			krzyzyk.X=5;
		}
		
		if(static_cast<int>(liczba) == 57)
		{
			krzyzyk.X=9;
		}
	}
	
	koloruj(FIOLETOWY);
	ZmienPozycjeKursora(krzyzyk);  // wstawia X w dobre miejsce
	cout<<"X";
	
	ZmienPozycjeKursora(wyjsciowy);  // do prawidlowego wyswietlania sie planszy
}


void tura_komputera(char * pomocnicza,int * tab, WskaznikNaMapie & kolko, int &licznik, WskaznikNaMapie &wyjsciowy )
{
	int n;

	n=(rand()%9)+1;
	
	for(int i = 0 ; i < licznik ; ++i)
	{
		if( tab[i] == n )
		{
			n=(rand()%9)+1;
			i=-1;
		}
	}
	
	tab[licznik]=n;
	++licznik;
	
	pomocnicza[n-1]='O';
	
	if(n == 1 || n == 2 || n == 3 )
	{
		kolko.Y=0;
		
		if( n == 1)
		{
			kolko.X=1;
		}
		
		if(n == 2)
		{
			kolko.X=5;
		}
		
		if(n == 3)
		{
			kolko.X=9;
		}
	}
	else if ( n == 4 || n == 5 || n == 6 )
	{
		kolko.Y=2;
		
		if( n == 4 )
		{
			kolko.X=1;
		}
		
		if( n == 5 )
		{
			kolko.X=5;
		}
		
		if( n == 6 )
		{
			kolko.X=9;
		}
	}
	else if ( n == 7 || n == 8 || n == 9 )
	{
		kolko.Y=4;
		
		if( n == 7 )
		{
			kolko.X=1;
		}
		
		if(n == 8 )
		{
			kolko.X=5;
		}
		
		if(n == 9 )
		{
			kolko.X=9;
		}
	}
	
	koloruj(BLEKIT);
	ZmienPozycjeKursora(kolko);  // wstawia O w dobre miejsce
	cout<<"O";
	
	ZmienPozycjeKursora(wyjsciowy);  // do prawidlowego wyswietlania sie planszy
}

void czy_koniec( WskaznikNaMapie krzyzyk, WskaznikNaMapie kolko, WskaznikNaMapie & koniec_gry , char * pomocnicza, bool &wygrana )
{
	
	for(int i = 0; i < 9 ; i = i + 3)  // poziomo dla gracza
	{
		if( pomocnicza[i]=='X' && pomocnicza[i+1]=='X' && pomocnicza[i+2]=='X' )
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Gratulacje, wygrales!";
			wygrana=true;
			return;
		}
	}
	
	for(int i = 0; i < 3 ; ++i)  // pionowo dla gracza
	{
		if( pomocnicza[i]=='X' && pomocnicza[i+3]=='X' && pomocnicza[i+6]=='X' )
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Gratulacje, wygrales!";
			wygrana=true;
			return;
		}
	}
	
	if( ( pomocnicza[0]=='X' && pomocnicza[4]=='X' && pomocnicza[8]=='X' ) || ( pomocnicza[2]=='X' && pomocnicza[4]=='X' && pomocnicza[6]=='X' ) ) // po skosie dla gracza
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Gratulacje, wygrales!";
			wygrana=true;
			return;
		}
		
	for(int i = 0; i < 9 ; i = i + 3)  // poziomo dla komputera
	{
		if( pomocnicza[i]=='O' && pomocnicza[i+1]=='O' && pomocnicza[i+2]=='O' )
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Niestety, ale przegrales :(";
			wygrana=true;
			return;
		}
	}
	
	for(int i = 0; i < 3 ; ++i)  // pionowo dla komputera
	{
		if( pomocnicza[i]=='O' && pomocnicza[i+3]=='O' && pomocnicza[i+6]=='O' )
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Niestety, ale przegrales :(";
			wygrana=true;
			return;
		}
	}
	
	if( ( pomocnicza[0]=='O' && pomocnicza[4]=='O' && pomocnicza[8]=='O' ) || ( pomocnicza[2]=='O' && pomocnicza[4]=='O' && pomocnicza[6]=='O' ) ) // po skosie dla SI
		{
			ZmienPozycjeKursora(koniec_gry);
			koloruj(ZIELONY);
			cout<<"Niestety, ale przegrales :(";
			wygrana=true;
			return;
		}
		
	if( ( pomocnicza[0]=='O' || pomocnicza[0]=='X' ) && ( pomocnicza[1]=='O' || pomocnicza[1]=='X' ) && ( pomocnicza[2]=='O' || pomocnicza[2]=='X' ) &&
	( pomocnicza[3]=='O' || pomocnicza[3]=='X' ) && ( pomocnicza[4]=='O' || pomocnicza[4]=='X' ) && ( pomocnicza[5]=='O' || pomocnicza[5]=='X' ) &&
	( pomocnicza[6]=='O' || pomocnicza[6]=='X' ) && ( pomocnicza[7]=='O' || pomocnicza[7]=='X' ) && ( pomocnicza[8]=='O' || pomocnicza[8]=='X' ))  // brak rozwiazania
	{
		ZmienPozycjeKursora(koniec_gry);
		koloruj(ZIELONY);
		cout<<"REMIS !!";
		wygrana=true;
		return;
	}
}

void czysc_blad(WskaznikNaMapie &BLAD)
{
	for(int i = 20 ; i < 60 ; ++i)
	{
		BLAD.X=i;
		ZmienPozycjeKursora(BLAD);
		cout<<" ";
	}
	
	BLAD.X=20;
}

int main()
{
	srand(time(NULL));
	int koniec=1;
	int tab[9];
	int licznik=0;
	char pomocnicza[9];
	int kto_zaczyna;
	bool wygrana=false;
	
	kto_zaczyna=rand()%101;
	
	WskaznikNaMapie kolko;
	WskaznikNaMapie krzyzyk;
	WskaznikNaMapie wyjsciowy;
	WskaznikNaMapie koniec_gry;
	WskaznikNaMapie BLAD;
	
	BLAD.X=20;
	BLAD.Y=3;
	
	koniec_gry.X=3;
	koniec_gry.Y=8;
	
	wyjsciowy.X=9;
	wyjsciowy.Y=4;
	
	krzyzyk.X=9;
	krzyzyk.Y=4;
	
	kolko.X=7;
	kolko.Y=4;
	
	wygrana = menu();
	
	if(wygrana==false)
	{
		while(wygrana!=true)
		{
			if(kto_zaczyna>50)
			{
				moja_tura(tab,licznik,krzyzyk,wyjsciowy,pomocnicza,BLAD);
				czy_koniec(krzyzyk,kolko,koniec_gry,pomocnicza,wygrana);
				czysc_blad(BLAD);
				if(!wygrana)
				{
					tura_komputera(pomocnicza,tab,kolko,licznik,wyjsciowy);
					czy_koniec(krzyzyk,kolko,koniec_gry,pomocnicza,wygrana);
				}
				
			}
			else
			{
				tura_komputera(pomocnicza,tab,kolko,licznik,wyjsciowy);
				czy_koniec(krzyzyk,kolko,koniec_gry,pomocnicza,wygrana);
				
				if(!wygrana)
				{
					
					moja_tura(tab,licznik,krzyzyk,wyjsciowy,pomocnicza,BLAD);
					czy_koniec(krzyzyk,kolko,koniec_gry,pomocnicza,wygrana);
					czysc_blad(BLAD);
					
				}
			}
		}
	}
	koniec_gry.X=3;
	koniec_gry.Y=12;
	ZmienPozycjeKursora(koniec_gry);
	
	system("PAUSE");
	return 0;
}
