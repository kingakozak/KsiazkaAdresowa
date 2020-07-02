#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <cstdio>

using namespace std;

struct KsiazkaAdresowa
{
    int id = 0;
    int idUzytkownika = 0;
    string imie, nazwisko, telefon, email, adres;
};
struct Uzytkownicy
{
    int idUzytkownika = 0;
    string login, haslo;
};

int podajIdOstatniegoKontaktu ()
{
    int idOstatniegoKontaktu = 0;

    fstream plik;
    plik.open("Kontakty.txt", ios::in);

    if (plik.good() == true)
    {
        string poprzedniaLinia;
        string linia;
        char znak = '|';

        while(true)
        {
            poprzedniaLinia = linia;
            getline(plik,linia);
            if(plik.eof())
            {
                break;
            }
        }
        int pozycja = poprzedniaLinia.find(znak);
        idOstatniegoKontaktu = atoi(poprzedniaLinia.substr(0,pozycja).c_str());
    }
    plik.close();
    return idOstatniegoKontaktu;
}

void zapiszUzytkownikowDoPliku (vector<Uzytkownicy> listaUzytkownikow)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    for (vector<Uzytkownicy>::iterator itr = listaUzytkownikow.begin(); itr != listaUzytkownikow.end(); itr++)
    {
        plik <<itr->idUzytkownika<<'|'<<itr->login<<'|'<<itr->haslo<<'|'<<endl;
    }
    plik.close();
}

vector<Uzytkownicy> odczytajUzytkownikowZPliku (vector<Uzytkownicy> listaUzytkownikow, Uzytkownicy uzytkownik)
{
    string login, haslo;
    int idUzytkownika = 0;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == true)
    {
        string linia;
        char znak = '|';

        while(getline(plik,linia))
        {
            int pozycja = linia.find(znak);
            idUzytkownika = atoi(linia.substr(0,pozycja).c_str());
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            login = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            pozycja = linia.find(znak);
            haslo = linia.substr(0,pozycja);
            linia.erase(0,pozycja+1);

            uzytkownik.idUzytkownika = idUzytkownika;
            uzytkownik.login = login;
            uzytkownik.haslo = haslo;

            listaUzytkownikow.push_back(uzytkownik);
        }
    }
    plik.close();
    return listaUzytkownikow;
}

void zapiszKontaktDoPliku (vector<KsiazkaAdresowa> adresaci)
{
    fstream plik;
    plik.open("Kontakty.txt", ios::out | ios::app);

    vector<KsiazkaAdresowa>::iterator itr = adresaci.end();
    itr--;
    plik <<itr->id<<'|'<<itr->idUzytkownika<<'|'<<itr->imie<<'|'<<itr->nazwisko<<'|'<<itr->telefon<<'|'<<itr->email<<'|'<<itr->adres<<'|'<< endl;

    plik.close();
}

void zapiszKontaktDoPlikuPoEdycji (vector<KsiazkaAdresowa> adresaci, int doEdycji)
{
    fstream plik, plikTymczasowy;
    plik.open("Kontakty.txt", ios::in);
    plikTymczasowy.open("Kontakty_tymczasowy.txt", ios::out);

    string linia;
    char znak = '|';
    int id =0;

    while(getline(plik,linia))
    {
        int pozycja = linia.find(znak);
        id = atoi(linia.substr(0,pozycja).c_str());

        if(id != doEdycji)
        {
            plikTymczasowy <<linia << endl;
        }
        else
        {
            for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr->id == doEdycji)
                {
                    plikTymczasowy <<itr->id<<'|'<<itr->idUzytkownika<<'|'<<itr->imie<<'|'<<itr->nazwisko<<'|'<<itr->telefon<<'|'<<itr->email<<'|'<<itr->adres<<'|'<< endl;
                }
            }
        }
    }

    plik.close();
    plikTymczasowy.close();

    remove("Kontakty.txt");
    rename("Kontakty_tymczasowy.txt","Kontakty.txt");
}

void zapiszKontaktDoPlikuPoUsunieciu (vector<KsiazkaAdresowa> adresaci, int doUsuniecia)
{
    fstream plik, plikTymczasowy;
    plik.open("Kontakty.txt", ios::in);
    plikTymczasowy.open("Kontakty_tymczasowy.txt", ios::out);

    string linia;
    char znak = '|';
    int id =0;

    while(getline(plik,linia))
    {
        int pozycja = linia.find(znak);
        id = atoi(linia.substr(0,pozycja).c_str());

        if(id != doUsuniecia)
        {
            plikTymczasowy <<linia<< endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("Kontakty.txt");
    rename("Kontakty_tymczasowy.txt","Kontakty.txt");
}

vector<KsiazkaAdresowa> odczytajZPliku (vector<KsiazkaAdresowa> adresaci, KsiazkaAdresowa kontakt, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, telefon, email, adres;
    int id = 0;
    int idUzytkownika = 0;

    fstream plik;
    plik.open("Kontakty.txt", ios::in);

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
            idUzytkownika = atoi(linia.substr(0,pozycja).c_str());
            linia.erase(0,pozycja+1);

            if(idUzytkownika == idZalogowanegoUzytkownika)
            {
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

                kontakt.id = id;
                kontakt.idUzytkownika = idUzytkownika;
                kontakt.imie = imie;
                kontakt.nazwisko = nazwisko;
                kontakt.telefon = telefon;
                kontakt.email = email;
                kontakt.adres = adres;

                adresaci.push_back(kontakt);
            }
        }
    }
    plik.close();
    return adresaci;
}

vector<Uzytkownicy> rejestracja (vector<Uzytkownicy> listaUzytkownikow)
{
    string login, haslo;
    int idUzytkownika = 0;

    cout<< "Wprowadz nastepujace dane dla nowego uzytkownika: "<<endl;
    cout<< "Login: "<<endl;
    cin >> login;

    for (vector<Uzytkownicy>::iterator itr = listaUzytkownikow.begin(); itr != listaUzytkownikow.end(); itr++)
    {
        if (itr->login == login)
        {
            cout << "Taki uzytkownik istnieje. Podaj inny login: "<<endl;
            cin >> login;
            itr = listaUzytkownikow.begin();
        }
    }
    cout<< "Haslo: "<<endl;
    cin >> haslo;

    Uzytkownicy uzytkownik;

    if (listaUzytkownikow.empty())
    {
        idUzytkownika = 1;
    }
    else
    {
        int wielkoscWektora = listaUzytkownikow.size();
        idUzytkownika = listaUzytkownikow[wielkoscWektora-1].idUzytkownika + 1;
    }

    uzytkownik.idUzytkownika = idUzytkownika;
    uzytkownik.login = login;
    uzytkownik.haslo = haslo;
    listaUzytkownikow.push_back(uzytkownik);

    cout << "Konto zarejestrowane pomyslnie"<<endl;
    Sleep(1500);

    zapiszUzytkownikowDoPliku (listaUzytkownikow);
    return listaUzytkownikow;
}

int logowanie (vector<Uzytkownicy> listaUzytkownikow)
{
    string login, haslo;
    cout<< "Aby sie zalogowac podaj login: "<<endl;
    cin >> login;

    for (vector<Uzytkownicy>::iterator itr = listaUzytkownikow.begin(); itr != listaUzytkownikow.end(); itr++)
    {
        if (itr->login == login)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Ilosc prob: "<< 3-proby <<endl;
                cin >> haslo;
                if (itr->haslo == haslo)
                {
                    cout << "Udalo sie zalogowac"<<endl;
                    Sleep(1500);
                    return itr->idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo - poczekaj 3 sekundy i sprobuj ponownie"<<endl;
            Sleep(3000);
        }
    }
    return 0;
}

vector<KsiazkaAdresowa> stworzKontakt(vector<KsiazkaAdresowa> adresaci, int idUzytkownika)
{
    int idOstatniegoKontaktu = podajIdOstatniegoKontaktu ();

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

    id = ++idOstatniegoKontaktu;

    system("pause");

    kontakt.id = id;
    kontakt.idUzytkownika = idUzytkownika;
    kontakt.imie = imie;
    kontakt.nazwisko = nazwisko;
    kontakt.telefon = telefon;
    kontakt.email = email;
    kontakt.adres = adres;

    adresaci.push_back(kontakt);

    zapiszKontaktDoPliku (adresaci);
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
    if (adresaci.empty())
    {
        cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
        Sleep(1500);
    }
    else
    {
        cout <<"Wszystkie kontakty z ksiazki adresowej:"<<endl;
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            wyswietlKontakt(*itr);
        }
    }
}

void wyszukajPoImieniu (vector<KsiazkaAdresowa> adresaci)
{
    string szukaneImie, imie;
    if (adresaci.empty())
    {
        cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
        Sleep(1500);
    }
    else
    {
        cout <<"Podaj szukane imie:"<<endl;
        cin >> szukaneImie;
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->imie == szukaneImie)
            {
                wyswietlKontakt(*itr);
            }
        }
    }
}

void wyszukajPoNazwisku (vector<KsiazkaAdresowa> adresaci)
{
    string szukaneNazwisko, nazwisko;
    if (adresaci.empty())
    {
        cout << "Nie ma zadnego kontaktu w ksiazce adresowej."<< endl;
        Sleep(1500);
    }
    else
    {
        cout <<"Podaj szukane nazwisko:"<<endl;
        cin >> szukaneNazwisko;
        for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->nazwisko == szukaneNazwisko)
            {
                wyswietlKontakt(*itr);
            }
        }
    }
}

bool sprawdzCzyKontaktNalezyDoUzytkownika (vector<KsiazkaAdresowa>adresaci, int idDoZmiany)
{
    for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->id == idDoZmiany)
        {
            return true;
        }
    }
    return false;
}

vector<KsiazkaAdresowa> usuwanieKontaktow (vector<KsiazkaAdresowa>adresaci)
{
    char usun;
    int doUsuniecia;
    cout <<" Podaj ID kontaktu, ktory chcesz usunac: "<<endl;
    cin >> doUsuniecia;
    bool sprawdzian = sprawdzCzyKontaktNalezyDoUzytkownika(adresaci,doUsuniecia);
    if(sprawdzian == true)
    {
        cout <<" Czy napewno chcesz usunac istniejacy kontakt? Jezeli tak wcisnij klawisz 't' : "<<endl;
        cin >> usun;
        if (usun == 't')
        {
            for (vector<KsiazkaAdresowa>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr->id == doUsuniecia)
                {
                    adresaci.erase(itr);
                    break;
                }
            }
            cout << "Kontakt zostal usuniety" << endl;
            Sleep(1500);
            zapiszKontaktDoPlikuPoUsunieciu (adresaci, doUsuniecia);
        }
    }
    else
    {
        cout <<" Nie ma kontaktu o podanym ID: "<<endl;
        Sleep(1500);
    }
    return adresaci;
}

vector<KsiazkaAdresowa> edytowanieKontaktow (vector<KsiazkaAdresowa>adresaci)
{
    string noweImie, noweNazwisko, nowyTelefon, nowyEmail, nowyAdres;
    char wybor;
    int doEdycji;
    cout <<" Podaj ID kontaktu, ktory chcesz edytowac: "<<endl;
    cin >> doEdycji;
    bool sprawdzian = sprawdzCzyKontaktNalezyDoUzytkownika(adresaci,doEdycji);
    if(sprawdzian == true)
    {
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
                    itr ->imie = noweImie;
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
                    itr ->nazwisko = noweNazwisko;
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
                    itr ->telefon = nowyTelefon;
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
                    itr ->email = nowyEmail;
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
                    itr ->adres = nowyAdres;
                }
            }
            cout << "Adres zostal zmieniony"<<endl;
            system("pause");
        }
        if (wybor == '6') {}
        zapiszKontaktDoPlikuPoEdycji (adresaci, doEdycji);
    }
    else
    {
        cout <<" Nie ma kontaktu o podanym ID: "<<endl;
        Sleep(1500);
    }
    return adresaci;
}

vector<Uzytkownicy> zmianaHasla (int idZalogowanegoUzytkownika, vector<Uzytkownicy>listaUzytkownikow)
{
    string noweHaslo;
    cout << "Podaj nowe haslo: "<<endl;
    cin >> noweHaslo;

    for (vector<Uzytkownicy>::iterator itr = listaUzytkownikow.begin(); itr != listaUzytkownikow.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika)
        {
            itr->haslo = noweHaslo;
            cout << "Twoje haslo zostalo zmienione "<<endl;
            Sleep(1500);
        }
    }
    zapiszUzytkownikowDoPliku (listaUzytkownikow);
    return listaUzytkownikow;
}

void wyswietlMenuUzytkownika ()
{
    system("cls");
    cout << "1. Stworz nowy kontakt "<<endl;
    cout << "2. Wyszukaj kontakt po imieniu "<<endl;
    cout << "3. Wyszukaj kontakt po nazwisku " <<endl;
    cout << "4. Wyswietl wszystkie kontakty "<<endl;
    cout << "5. Usun kontakt "<<endl;
    cout << "6. Edytuj kontakt "<<endl;
    cout << "7. Zmien haslo "<<endl;
    cout << "8. Wyloguj sie "<<endl;
    cout << "Twoj wybor: "<<endl;
}

void wyswietlMenuGlowne ()
{
    system("cls");
    cout << "1. Rejestracja "<<endl;
    cout << "2. Logowanie "<<endl;
    cout << "3. Zamknij program " <<endl;
}

int main()
{
    vector<KsiazkaAdresowa> adresaci;
    KsiazkaAdresowa kontakt;
    vector<Uzytkownicy> listaUzytkownikow;
    Uzytkownicy uzytkownik;
    char wybor;
    int idZalogowanegoUzytkownika = 0;
    listaUzytkownikow = odczytajUzytkownikowZPliku (listaUzytkownikow, uzytkownik);

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            wyswietlMenuGlowne();
            cin >> wybor;

            if (wybor == '1')
            {
                listaUzytkownikow = rejestracja (listaUzytkownikow);
            }
            if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie (listaUzytkownikow);
                if (idZalogowanegoUzytkownika != 0)
                {
                    adresaci = odczytajZPliku (adresaci, kontakt, idZalogowanegoUzytkownika);
                }
            }
            if (wybor == '3')
            {
                exit (0);
            }
        }
        else
        {
            wyswietlMenuUzytkownika();
            cin >> wybor;

            if (wybor == '1')
            {
                adresaci = stworzKontakt(adresaci, idZalogowanegoUzytkownika);
            }
            if (wybor == '2')
            {
                wyszukajPoImieniu(adresaci);
            }
            if (wybor == '3')
            {
                wyszukajPoNazwisku(adresaci);
            }
            if (wybor == '4')
            {
                wyswietlWszystkieKontakty(adresaci);
            }
            if (wybor == '5')
            {
                adresaci = usuwanieKontaktow(adresaci);
            }
            if (wybor == '6')
            {
                adresaci = edytowanieKontaktow(adresaci);
            }
            if (wybor == '7')
            {
                listaUzytkownikow = zmianaHasla(idZalogowanegoUzytkownika, listaUzytkownikow);
            }
            if (wybor == '8')
            {
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
            }
        }
    }
    return 0;
}
