#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

#define NIEBIESKI 8700  // Definicje kolorow
#define ZIELONY 8701    
#define CZERWONY 8702   
#define ZOLTY 8703      
#define BLEKIT 8704    
#define FIOLETOWY 8705  


using namespace std;

typedef COORD WskaznikNaMapie;  // zmienia typ COORD na WskaznikNaMapie

void koloruj(int KOLOR)  // kolorouje tekst konsoli
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

int menu()  // Wyswietla menu glowne oraz decyduje o tym czy grac, czy wyjsc z programu
{
	char wybor;
	
	system("cls");
	
	koloruj(ZIELONY);
	cout<<"\t\tGRA W KOLKO I KRZYZYK by Wienio"<<endl<<endl;
	
	koloruj(ZOLTY);
	cout<<"Co chcesz zrobic?"<<endl;
	
	koloruj(NIEBIESKI);
	cout<<"1)Zacznij gre!"<<endl;
		
	koloruj(CZERWONY);
	cout<<"2)Skoncz gre!";
	
	cout<<endl<<endl;
	
	do
	{
		wybor=getch(); // Wybor akcji jaka ma podjac
		
		if(wybor==49)   // (1)
		{
			system("cls");	
			wyswietl_plansze();
			return false;
		}
		
		else if (wybor == 50)  // (2)
		{
			system("cls");
			koloruj(CZERWONY);
			cout<<"Do zobaczenia!";
			return true;
		}
		
	} while(wybor!=49 || wybor!=50); // warunek
}

void ZmienPozycjeKursora( WskaznikNaMapie Wspolrzedne )
{
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), Wspolrzedne );  // zmienia polozenie kursora
}

void czysc_blad(WskaznikNaMapie &BLAD)
{
	for(int i = 20 ; i < 56 ; ++i)
	{
		BLAD.X=i;
		ZmienPozycjeKursora(BLAD);
		cout<<" ";
	}
	
	BLAD.X=20;
}

void moja_tura(int * tab, int & licznik, WskaznikNaMapie &wstaw, WskaznikNaMapie &wyjsciowy, char * pomocnicza, WskaznikNaMapie & BLAD)
{
	char liczba;
	bool czy_blad=false;  // sprawdza czy czyscic konsole
	
	liczba=getch();
	
	if( liczba <= 48 || liczba >= 58)  // sprawdza czy wprowadzono odpowieni znak ( liczbe 1-9 )
	{
		ZmienPozycjeKursora(BLAD);
		koloruj(CZERWONY);
		cout<<"BLAD, podaj wartosc wlasciwa (1-9) !";
		czy_blad=true;
		moja_tura(tab,licznik,wstaw,wyjsciowy,pomocnicza,BLAD);
	}
	
	for(int i = 0 ; i < licznik ; ++i)  // sprawdza czy pole nie jest zajete
	{
		if( tab[i] == (liczba-48) )
		{
			liczba=getch();
			i=-1;
		}
	}
	
	if(czy_blad)   // czysci konsole w przypadku bledu
	{
		czysc_blad(BLAD);
	}
	
	tab[licznik]=liczba-48;    // zapisuje liczbe w tablicy, zeby wiedziec ktore pola zajete
	++licznik;
	
	pomocnicza[liczba-49]='X';  // do sprawdzenia wyniku gry
	
	if(liczba >=49 && liczba <=51 )  // okreslenie gdzie wstawic znak
	{
		wstaw.Y=0;
		
		if( liczba == 49)
		{
			wstaw.X=1;
		}
		
		if( liczba == 50)
		{
			wstaw.X=5;
		}
		
		if( liczba == 51)
		{
			wstaw.X=9;
		}
	}
	else if ( liczba >=52 && liczba <=54 )
	{
		wstaw.Y=2;
		
		if( liczba == 52)
		{
			wstaw.X=1;
		}
		
		if( liczba == 53)
		{
			wstaw.X=5;
		}
		
		if( liczba == 54)
		{
			wstaw.X=9;
		}
	}
	else if ( liczba >=55 && liczba <=57 )
	{
		wstaw.Y=4;
		
		if( liczba == 55)
		{
			wstaw.X=1;
		}
		
		if( liczba == 56)
		{
			wstaw.X=5;
		}
		
		if( liczba == 57)
		{
			wstaw.X=9;
		}
	}
	
	koloruj(FIOLETOWY);
	ZmienPozycjeKursora(wstaw);  // wstawia X w dobre miejsce
	cout<<"X";
	
	ZmienPozycjeKursora(wyjsciowy);  // do prawidlowego wyswietlania sie planszy
}


void tura_komputera(char * pomocnicza,int * tab, WskaznikNaMapie & wstaw, int &licznik, WskaznikNaMapie &wyjsciowy )
{
	int n;

	n=(rand()%9)+1;  // losuje liczbe z przedzialu 1-9
	
	for(int i = 0 ; i < licznik ; ++i)  // sprawdza czy jest wolne miejsce na planszy, jesli nie to losuje nowa liczbe do skutku
	{
		if( tab[i] == n )
		{
			n=(rand()%9)+1;
			i=-1;
		}
	}
	
	tab[licznik]=n;  // zapamietuje liczbe czy juz wystapila
	++licznik;
	
	pomocnicza[n-1]='O';    // zapisuje znak do sprawdzenia stanu gry (okresla wynik)
	
	if ( n == 1 || n == 4 || n == 7)   // szybsze przypisanie niz poprzednio, mniej sprawdzania warunkow
	{
		wstaw.X=1;
	}
	else if ( n== 2 || n == 5 || n == 8 )
	{
		wstaw.X=5;
	}
	else
	{
		wstaw.X=9;
	}
	
	if( n > 0 && n < 4 )
	{
		wstaw.Y=0;
	}
	else if ( n > 3 && n < 7 )
	{
		wstaw.Y=2;
	}
	else
	{
		wstaw.Y=4;
	}

	koloruj(BLEKIT);
	ZmienPozycjeKursora(wstaw);  // wstawia O w dobre miejsce
	cout<<"O";
	
	ZmienPozycjeKursora(wyjsciowy);  // do prawidlowego wyswietlania sie planszy
}

void czy_koniec( WskaznikNaMapie & koniec_gry , char * pomocnicza, bool &wygrana )
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
		
	short int czy_koniec=0;    // pomocnicza ktora okresla remis
		
	for(int i = 0; i < 9 ; ++i)
	{
		if ( pomocnicza[i] == 'O' || pomocnicza[i] == 'X' )
		{
			++czy_koniec;
		}
		else
		{
			break;
		}
	}	
		
	if(czy_koniec==9) // jezeli wszystkie pola sa zapelnione i nikt nie wygral
	{
		ZmienPozycjeKursora(koniec_gry);
		koloruj(ZIELONY);
		cout<<"REMIS !!";
		wygrana=true;
		return;
	}	
		
}


int main()
{
	srand(time(NULL));
	int tab[9];     // tablica przechowujaca zajete pola
	int licznik=0;  // indeks dla tablicy powyzej
	char pomocnicza[9];  // tablica okreslajaca czy ktos wygral
	int kto_zaczyna;   // okresla czy jako pierwszy zaczyna komputer czy gracz
	bool wygrana=false;  // zmienna boolowska okreslajaca koniec gry
	
	kto_zaczyna=rand()%101; // losowanie, 50% szans dla obu
	
	WskaznikNaMapie wstaw;      // jeden odpowiedzialny za odpowiednie miejsce dla obu znakow
	WskaznikNaMapie wyjsciowy;  // odpowiada za poprawne wyswietlanie planszy
	WskaznikNaMapie koniec_gry; // wskaznik na koncu gry
	WskaznikNaMapie BLAD;      // dla obslugi bledu getch
	
	BLAD.X=20;   // pozycja wyswietlania bledu
	BLAD.Y=3;
	
	koniec_gry.X=5;   // do wyswietlenia wyniku
	koniec_gry.Y=7;
	
	wyjsciowy.X=9;   // dla poprawnosci wyswietlania planszy
	wyjsciowy.Y=4;
	
	wygrana = menu();   // sprawdzenie czy chcemy w ogole grac oraz wyswietlenie MENU gry
	
	if(wygrana==false)   // jesli chcemy zagrac
	{
		while(wygrana!=true)  // petla okreslajaca rozgrywke
		{
			if(kto_zaczyna>50)
			{
				moja_tura(tab,licznik,wstaw,wyjsciowy,pomocnicza,BLAD);
				czy_koniec(koniec_gry,pomocnicza,wygrana);
				
				if(!wygrana)
				{
					tura_komputera(pomocnicza,tab,wstaw,licznik,wyjsciowy);
					czy_koniec(koniec_gry,pomocnicza,wygrana);
				}
				
			}
			else
			{
				tura_komputera(pomocnicza,tab,wstaw,licznik,wyjsciowy);
				czy_koniec(koniec_gry,pomocnicza,wygrana);
				
				if(!wygrana)
				{
					moja_tura(tab,licznik,wstaw,wyjsciowy,pomocnicza,BLAD);
					czy_koniec(koniec_gry,pomocnicza,wygrana);
				}
			}
		}
	}
	
	koniec_gry.X=3;   // ustawia kursor na koniec
	koniec_gry.Y=12;
	ZmienPozycjeKursora(koniec_gry); // wyswietlenie system pause poprawne
	
	system("PAUSE");
	return 0;
}
