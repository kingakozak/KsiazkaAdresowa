#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

using namespace std;

struct KsiazkaAdresowa
{
    int id = 0;
    string imie, nazwisko, telefon, email, adres;
};

void zapiszDoPliku (vector<KsiazkaAdresowa> adresaci)
{
    string imie, nazwisko, telefon, email, adres;
    int id = 0;

    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::out);

    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        plik <<itr->id<<'|'<<itr->imie<<'|'<<itr->nazwisko<<'|'<<itr->telefon<<'|'<<itr->email<<'|'<<itr->adres<<'|'<<endl;
    }

    plik.close();
}

vector<KsiazkaAdresowa> odczytajZPliku (vector<KsiazkaAdresowa> adresaci, KsiazkaAdresowa kontakt)
{
    string imie, nazwisko, telefon, email, adres;
    int id = 0;

    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::in);

    if (plik.good() == true)
    {
        string linia;
        char znak = '|';

        while(getline(plik,linia))
        {
            int pozycja = linia.find(znak);
            id = atoi(linia.substr(0,pozycja).c_str());
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            imie = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            nazwisko = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            telefon = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            email = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            adres = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            kontakt.imie = imie;
            kontakt.nazwisko = nazwisko;
            kontakt.telefon = telefon;
            kontakt.email = email;
            kontakt.adres = adres;
            kontakt.id = id;

            adresaci.push_back(kontakt);
        }
    }
    plik.close();

    return adresaci;
}

vector<KsiazkaAdresowa> stworzKontakt(vector<KsiazkaAdresowa> adresaci)
{
    string imie, nazwisko, telefon, email, adres;
    int id = 0;

    cout<< "Wprowadz nastepujace dane dla nowego kontaktu: "<<endl;
    cout<< "Imie: "<<endl;
    cin >> imie;
    cout<< "Nazwisko: "<<endl;
    cin >> nazwisko;
    cout<< "Nr telefonu: "<<endl;
    cin.sync();
    getline(cin,telefon);
    cout<< "Adres email: "<<endl;
    cin.sync();
    getline(cin,email);
    cout<< "Adres zamieszkania: "<<endl;
    cin.sync();
    getline(cin,adres);

    KsiazkaAdresowa kontakt;

    if (adresaci.empty())
    {
        id = 1;
    }
    else
    {
        int wielkoscWektora = adresaci.size();
        id = adresaci[wielkoscWektora-1].id + 1;
    }

    kontakt.id = id;
    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.telefon = telefon;
    kontakt.email = email;
    kontakt.adres = adres;

    adresaci.push_back(kontakt);

    return adresaci;
}
void wyswietlKontakt (KsiazkaAdresowa kontakt)
{
    cout<< kontakt.id<<endl;
    cout<< kontakt.imie<<endl;
    cout<< kontakt.nazwisko<<endl;
    cout<< kontakt.telefon<<endl;
    cout<< kontakt.email<<endl;
    cout<< kontakt.adres<<endl;
    system("pause");
}

void wyswietlWszystkieKontakty (vector<KsiazkaAdresowa> adresaci)
{
    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        wyswietlKontakt(*itr);
    }
}
void wyszukajPoImieniu (string szukaneImie, vector<KsiazkaAdresowa> adresaci)
{
    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->imie == szukaneImie)
        {
            wyswietlKontakt(*itr);
        }
    }
}

void wyszukajPoNazwisku (string szukaneNazwisko, vector<KsiazkaAdresowa> adresaci)
{
    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->nazwisko == szukaneNazwisko)
        {
            wyswietlKontakt(*itr);
        }
    }
}

vector<KsiazkaAdresowa> usuwanieKontaktow (int doUsuniecia, vector<KsiazkaAdresowa>adresaci)
{
    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->id == doUsuniecia)
        {
            adresaci.erase(itr);
            break;
        }
    }
    return adresaci;
}

vector<KsiazkaAdresowa> edytowanieKontaktow (int doEdycji, vector<KsiazkaAdresowa>adresaci)
{
    string noweImie, noweNazwisko, nowyTelefon, nowyEmail, nowyAdres;
    char wybor;

    system("cls");
    cout << "1 - imie "<<endl;
    cout << "2 - nazwisko "<<endl;
    cout << "3 - telefon " <<endl;
    cout << "4 - email "<<endl;
    cout << "5 - adres "<<endl;
    cout << "6 - powrot do MENU GLOWNEGO "<<endl;
    cin >> wybor;

    if (wybor == '1')
    {
        cout << "Wprowadz imie: "<<endl;
        cin >> noweImie;
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == doEdycji)
            {
                itr ->imie =  noweImie;
            }
        }
        cout << "Imie zostalo zmienione"<<endl;
        system("pause");
    }
    if (wybor == '2')
    {
        cout << "Wprowadz nazwisko: "<<endl;
        cin >> noweNazwisko;
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == doEdycji)
            {
                itr ->nazwisko =  noweNazwisko;
            }
        }
        cout << "Nazwisko zostalo zmienione"<<endl;
        system("pause");
    }
    if (wybor == '3')
    {
        cout << "Wprowadz telefon: "<<endl;
        cin.sync();
        getline(cin,nowyTelefon);
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == doEdycji)
            {
                itr ->telefon =  nowyTelefon;
            }
        }
        cout << "Telefon zostal zmieniony"<<endl;
        system("pause");
    }
    if (wybor == '4')
    {
        cout << "Wprowadz email: "<<endl;
        cin.sync();
        getline(cin,nowyEmail);
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == doEdycji)
            {
                itr ->email =  nowyEmail;
            }
        }
        cout << "Email zostal zmieniony"<<endl;
        system("pause");
    }
    if (wybor == '5')
    {
        cout << "Wprowadz adres: "<<endl;
        cin.sync();
        getline(cin,nowyAdres);
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == doEdycji)
            {
                itr ->adres =  nowyAdres;
            }
        }
        cout << "Adres zostal zmieniony"<<endl;
        system("pause");
    }
    if (wybor == '6') {}

    return adresaci;
}

int main()
{
    vector<KsiazkaAdresowa> adresaci;
    KsiazkaAdresowa kontakt;
    string imie, nazwisko;
    char wybor;
    int id;

    adresaci = odczytajZPliku (adresaci, kontakt);

    while(1)
    {
        system("cls");
        cout << "1. Stworz nowy kontakt "<<endl;
        cout << "2. Wyszukaj kontakt po imieniu "<<endl;
        cout << "3. Wyszukaj kontakt po nazwisku " <<endl;
        cout << "4. Wyswietl wszystkie kontakty "<<endl;
        cout << "5. Usun kontakt "<<endl;
        cout << "6. Edytuj kontakt "<<endl;
        cout << "9. Wyjdz z programu "<<endl;
        cout << "Twoj wybor: "<<endl;
        cin >> wybor;

        if (wybor == '1')
        {
            adresaci = stworzKontakt(adresaci);
            zapiszDoPliku (adresaci);
        }
        if (wybor == '2')
        {
            if (adresaci.empty())
            {
                cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
                Sleep(1500);
            }
            else
            {
                cout <<"Podaj szukane imie:"<<endl;
                cin >> imie;
                wyszukajPoImieniu (imie, adresaci);
            }
        }
        if (wybor == '3')
        {
            if (adresaci.empty())
            {
                cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
                Sleep(1500);
            }
            else
            {
                cout <<"Podaj szukane nazwisko:"<<endl;
                cin >> nazwisko;
                wyszukajPoNazwisku (nazwisko, adresaci);
            }
        }
        if (wybor == '4')
        {
            if (adresaci.empty())
            {
                cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
                Sleep(1500);
            }
            else
            {
                cout <<"Wszystkie kontakty z ksiazki adresowej:"<<endl;
                wyswietlWszystkieKontakty(adresaci);
            }
        }
        if (wybor == '5')
        {
            char usun;
            int doUsuniecia;
            cout <<" Podaj ID kontaktu, ktory chcesz usunac: "<<endl;
            cin >> doUsuniecia;
            cout <<" Czy napewno chcesz usunac istniejacy kontakt? Jezeli tak wcisnij klawisz 't' : "<<endl;
            cin >> usun;
            if (usun == 't')
            {
                adresaci = usuwanieKontaktow (doUsuniecia, adresaci);
                cout << "Kontakt zostal usuniety" << endl;
                Sleep(1500);
                zapiszDoPliku (adresaci);
            }
        }
        if (wybor == '6')
        {
            int doEdycji;
            cout <<" Podaj ID kontaktu, ktory chcesz edytowac: "<<endl;
            cin >> doEdycji;

            adresaci = edytowanieKontaktow (doEdycji, adresaci);
            zapiszDoPliku (adresaci);
        }

        if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}
