//============================================================================
// Karol Malek
// gr. 1514
// nr albumu 3937
//============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include<math.h>
#include <time.h>
using namespace std;

#define NBUF 1024
string pobierzsciezke();
string polecenie;
const string domowy = pobierzsciezke();
const char * domowy_katalog = domowy.c_str();

//*****************************************************************************************


string pobierzsciezke()
{
    //funkcja getcwd z jezyka C
    char buffer[NBUF];
    getcwd(buffer,NBUF);
    string ret(buffer);
    return ret;
}
void pwd()
{
    //funkcja podajaca sciezke korzystajaca z pobierzsciezke
    cout << pobierzsciezke() <<endl;
}

void cd(string argument2)
{
    const char *par2=argument2.c_str();
    if (argument2 == "")
        chdir(domowy_katalog);
    else
    {
        chdir(par2);
    }
}

void ls()
{
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir("./");
    if (dpdf != NULL)
    {
        while ((epdf = readdir(dpdf)))
        {
            cout << epdf->d_name << endl;
        }
    }
}

void kopiuj(string par2,string par3)
{
    ifstream plik1 (par2.c_str(), fstream::binary);
    if (!plik1.good() )
        cout << "plik nie istnieje" <<endl;
    else
    {
        ofstream plik2 (par3.c_str(), fstream::trunc|fstream::binary);
        if(!plik2.good())
            cout << "Nie mozna otworzyc pliku do zapisu" << endl;
        else
        {
            plik2 << plik1.rdbuf ();
            plik1.close();
            plik2.close();
            cout << " Wykonano " << endl;
        }
    }
}


void wypisz(string inp)
{
    ifstream plik1 (inp.c_str(), fstream::in);
    if (!plik1.good() )
        cout << " Plik nie istnieje lub brak dostepu " <<endl;
    else
    {
        cout << plik1.rdbuf ();
        cout << endl;
        plik1.close();
    }
}

void triangle(string inp)
{
    int nParam = stod(inp, NULL);
    for (int i=0; i<nParam; ++i)
    {
        for (int j=i; j<nParam; ++j)
        {
            printf("*");
        }
        printf("\n");
    }
}

void help()
{
    cout << endl;
    cout << " Mozliwe polecenia : "<< endl;
    cout << "'cd' 'ls' 'pwd' 'kopiuj' 'help' 'wypisz' 'triangle' 'pt' 'szyfroj' 'deszyfroj' 'usun' 'rectangle' 'circle' 'exit'"<<endl;
    cout << " <nazwa polecenia> --help (Wyswietla pomoc do danego polecenia)"<<endl;
    cout << " exit -konczy dzialanie programu "<< endl;
    cout << endl;
}

//***************wlasne polecenia********************* 

//funkcja tworzaca plik tekstowy
void pt(string arg){
	ofstream PlikTekstowy;
	PlikTekstowy.open("arg.txt");
	
	string text;
	getline(cin, text);
	PlikTekstowy << text;
	
	PlikTekstowy.close();
}

//funkcja szyfrojaca plik tekstowy wg szyfru cezara
void szyfroj(string arg){
	int klucz = 5;
	
	ifstream plik1 (arg.c_str(), fstream::in);
    if (!plik1.good() )
        cout << " Plik nie istnieje lub brak dostepu " <<endl;
    else
    {
        char *tekst;
        plik1 >> tekst;
        
		for (int i=0; tekst[i] != '\0'; i++)
		{
			tekst[i] = ( tekst[i] + klucz );
		}      
		plik1.close();
	}
}

//funkcja deszyfrojaca plik tekstowy wg szyfru cezara
void deszyfroj(string arg){
	int klucz = 5;
	
	ifstream plik1 (arg.c_str(), fstream::in);
    if (!plik1.good() )
        cout << " Plik nie istnieje lub brak dostepu " <<endl;
    else
    {
        char *tekst;
        plik1 >> tekst;
        
		for (int i=0; tekst[i] != '\0'; i++)
		{
			tekst[i] = ( tekst[i] - klucz );
		}      
		plik1.close();
	}
}

//funkcja usuwa plik
void usun(string arg){
	ifstream plik1 (arg.c_str());
    if (!plik1.good() )
        cout << " Plik nie istnieje lub brak dostepu " <<endl;
    else remove(arg.c_str());
}

//funkcja rysojaca prostokat
void rectangle(string arg1, string arg2){
	int side1 = stod(arg1, NULL);
	int side2 = stod(arg2, NULL);
      for (int i=1; i<=side1; i++){
         for (int j=1; j<=side2; j++){
         cout << "*";
			  }
 
		 cout<<"\n";
         } 
}

//funkcja rysojaca kolo
void circle(string arg){
	int liczba = stod(arg, NULL);

	int i,l,j;
	int x;
	int y;
	int r;

	for(i=0;i<liczba;i++)
		{
				for (j=1;j<=liczba;j++)   
					{
					for (l=1;l<=liczba;l++)   
					{
                        float pierwsza = pow(j-x,2.);   
                        float druga = pow(l-y,2.);   
                        if ((((pierwsza+druga) <= pow(r,2.))  ||  (sqrt(pierwsza+druga) <= (r+0.5)))) cout<<"x";    
                        else cout <<" ";
                    }
                    cout<<"\n";
 
                  }
                cout<<"\n";   
      }
    
}

void godz(){
	time_t czas;
	struct tm * data;
	char godzina[ 80 ];
 
	time( & czas );
	data = localtime( & czas );
 
	strftime( godzina, 80, "Jest już %H:%M", data );
	cout<< godzina;
}

int main()
{
    help();
    cout <<endl;
    while((polecenie !="exit") && (polecenie !="EXIT"))
    {
        cout << [godz] pobierzsciezke() <<" -> ";
        getline(cin,polecenie);

        //###################################################
        string argument_1, argument_2, argument_3,argument_4,argument_5;
        istringstream StrStream(polecenie);

        StrStream >> argument_1;
        StrStream >> argument_2;
        StrStream >> argument_3;
        StrStream >> argument_4;
        StrStream >> argument_5;
        if(!argument_1.empty())
            cout << "argument_1: " <<  argument_1 << endl;
        if(!argument_2.empty())
            cout << "argument_2: " <<  argument_2 << endl;
        if(!argument_3.empty())
            cout << "argument_3: " <<  argument_3 << endl;
        if(!argument_4.empty())
            cout << "argument_4: " <<  argument_4 << endl;

        if (argument_2 == "--help")
        {
            if (argument_1=="pwd")
                cout << "pwd - wyswietla aktualna sciezke "<<endl;
            else if (argument_1=="ls")
                cout << "ls - wyswietla listing biezacego katalogu "<< endl;
            else if (argument_1=="help")
                cout << "help - wyswietla liste mozliwych komend " <<endl;
            else if (argument_1=="cd")
                cout << "cd <sciezka> - zmienia katalog roboczy, cd - zmienia na domowy." <<
                     " cd / -zmienia na glowny. cd .. -cofa "<< endl;
            else if (argument_1=="kopiuj")
                cout << "kopiuj <plik zrodlowy> <plik docelowy> " <<
                     "- kopiuje plik zrodlowy pod nazwa zadana jako docelowy"<< endl;
            else if (argument_1=="wypisz")
                cout << "wypisz <plik> - Wypisuje zawartosc pliku jako tekst"<<endl;
            else if (argument_1=="triangle")
                cout << "triangle liczba - rysuje trójkąt o podstawie liczba"<<endl;
			
//***************wlasne polecenia********************* 

			else if (argument_1=="pt")
                cout << "pt <nazwa pliku> - tworzy/nadpisuje plik o nazwie podanej w drogim argumecie"<<endl;
			else if (argument_1=="szyfroj")
                cout << "szyfroj <plik tekstowy> - szyfruje tekst zapisany w pliku"<<endl;
			else if (argument_1=="deszyfroj")
                cout << "deszyfroj <plik tekstowy> - deszyfruje tekst zapisany w pliku"<<endl;
			else if (argument_1=="usun")
                cout << "usun <plik> - usuwa plik"<<endl;
			else if (argument_1=="rectangle")
                cout << " rectangle <liczba1 liczba2> - tworzy prostokat o bokach rownych wartosci argumetow		liczba1 liczba2 lub kwadrat o boku rownym liczba1"<<endl;
			 else if (argument_1=="circle")
                cout << "circle liczba - rysuje kolo o promieniu liczba"<<endl;
        }
        else
        {
            if (argument_1 == "pwd")
                pwd();
            else if (argument_1 == "cd" && !argument_2.empty())
                cd(argument_2);
            else if (argument_1 == "ls")
                ls();
            else if (argument_1 == "kopiuj" && !argument_2.empty() && !argument_3.empty())
                kopiuj(argument_2,argument_3);
            else if (argument_1 == "help")
                help();
            else if (argument_1 == "wypisz" && !argument_2.empty())
                wypisz(argument_2);
            else if (argument_1 == "triangle" && !argument_2.empty())
                triangle(argument_2);
			
//***************wlasne polecenia********************* 

			else if (argument_1 == "pt" && !argument_2.empty())
                pt(argument_2);
			else if (argument_1 == "szyfroj" && !argument_2.empty())
                szyfroj(argument_2);
			else if (argument_1 == "deszyfroj" && !argument_2.empty())
                deszyfroj(argument_2);
			else if (argument_1 == "usun" && !argument_2.empty())
                usun(argument_2);
			else if (argument_1 == "rectangle" && !argument_2.empty() && !argument_3.empty())
                rectangle(argument_2, argument_3);
			else if (argument_1 == "rectangle" && !argument_2.empty() && argument_3.empty())
                rectangle(argument_2, argument_2);
        }
    }
    return 0;
}


