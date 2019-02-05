#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <objbase.h>
#include <CommCtrl.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <bits/stdc++.h>
////////////////////////////////////
#include <mysql.h>
////////////////////////////////////

#define MENU_ZAMKNIJ 2
#define MENU_WYDATEK 3
#define MENU_DOCHOD 4
#define MENU_POMOC 5
#define MENU_OSIAGNIECIA 6
#define BUTTON_DOCHOD 7
#define BUTTON_WYDATEK 8
#define WYCZYSC_PORTFEL 9
#define ZAMKNIJ_OSIAGI 10
#define MENU_HISTORIA 11
#define MENU_RANKING 12

#define SZUKAJ_DOCHOD 13




////////////////////////////////////////////////////////////


using namespace std;

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);                                              // OKNO !G£ÓWNE!
////////////////////////////////////////////////////////////
//                 WYGL¥D OKNO !G£ÓWNE!                   //
////////////////////////////////////////////////////////////
void DodajMenu(HWND);                                                                                   // WYGL¥D I MENU OKNO !G£ÓWNE!

void DodajKontrolki(HWND hWnd);                                                                         // PRZYCISKI, OKNA I GRAFIKA - OKNO !G£ÓWNE!

void DodajObrazki();                                                                                    // FUNKCJA WCZYTUJ¥CA GRAFIKÊ DO OKNO !G£ÓWNE!
////////////////////////////////////////////////////////////

void DodajDochod();                                                                                     // PÊTLA DO ZAPISYWANIA DOCHODÓW W HISTORII

void DodajWydatek();                                                                                    // PÊTLA DO ZAPISYWANIA WYDATKÓW W HISTORII

void ZapisDochody();                                                                                    // FUNKCJA ZAPISUJ¥CA DOCHÓD I TYTU£ Z OKIEN STATIC hWartosc I hTytul DO PLIKU.TXT

void ZapisWydatki();                                                                                    // FUNKCJA ZAPISUJ¥CA WYDATEK I TYTU£ Z OKIEN STATIC hWartosc I hTytul DO PLIKU.TXT

void ZapisPortfel();                                                                                    // FUNKCJA ZAPISUJ¥CA OSTATNI¥ WARTOŒÆ STANU KONTA DO PLIKU.TXT

void PokazPortfel();                                                                                    // FUNKCJA ODCZYTUJ¥CA WARTOŒÆ STANU KONTA Z PLIKU.TXT -> WYŒWIETLA W OKNIE hStan zmienna portfel

////////////////////////////////////////////////////////////
//             HISTORIA DOCHODÓW I WYDATKÓW               //
////////////////////////////////////////////////////////////
void ZapisDochodyHistoria();                                                                            //FUNKCJA ZAPISUJ¥CA KWOTÊ DOCHODÓW Z HISTORII DO PLIKU.TXT

void PokazDochodyHistoria();                                                                            // FUNKCJA WCZYTUJ¥CA HISTORIÊ KWOTY DOCHODÓW Z PLIKU.TXT I WCZYTUJ¥CA JE DO OKIEN STATIC

void ZapisDochodyTytulyHistoria();                                                                      //FUNKCJA ZAPISUJ¥CA TYTU£Y DOCHODÓW Z HISTORII DO PLIKU.TXT

void PokazDochodyTytulyHistoria();                                                                      // FUNKCJA WCZYTUJ¥CA HISTORIÊ TYTU£ÓW DOCHODÓW Z PLIKU.TXT I WCZYTUJ¥CA JE DO OKIEN STATIC

void ZapisWydatkiHistoria();                                                                            //FUNKCJA ZAPISUJ¥CA KWOTÊ DOCHODÓW Z HISTORII DO PLIKU.TXT

void PokazWydatkiHistoria();                                                                            // FUNKCJA WCZYTUJ¥CA HISTORIÊ KWOTY WYDATKÓW Z PLIKU.TXT I WCZYTUJ¥CA JE DO OKIEN STATIC

void ZapisWydatkiTytulyHistoria();                                                                      //FUNKCJA ZAPISUJ¥CA TYTU£Y WYDATKÓW Z HISTORII DO PLIKU.TXT

void PokazWydatkiTytulyHistoria();                                                                      // FUNKCJA WCZYTUJ¥CA HISTORIÊ TYTU£ÓW WYDATKÓW Z PLIKU.TXT I WCZYTUJ¥CA JE DO OKIEN STATIC
///////////////////////////////////////////
//                  BAZA                 //
///////////////////////////////////////////
const char* server= "sql7.freemysqlhosting.net";
const char* username = "sql7277178";
const char* password= "RyUQ83sbzh";
const char* dataBaseName="sql7277178";
const int port = 3306;

void Baza();

int qstate;
MYSQL* conn;
stringstream ss;

///////////////////////////////////////
void DodajObrazkiOsiagniecia();

void registerOsiagiClass(HINSTANCE hInst);                                                            // FUNKCJA OD 2.OKNA WPIÊTA DO 1

void registerHistoriaClass(HINSTANCE hInst);

void registerRankingClass(HINSTANCE hInst);

void PokazOsiagi(HWND);

void ObrazkiOsiagniecia();
////////////////////////////////////
void PokazHistorie(HWND);

void OknoHistorii(HWND hWnd);

void time();
time_t now;
char* dt;

HWND oknoData[0];
//////////////////////////////////////////////////////////////////////
string tekst;
char tekstd [30];
int n;
void WyszukajDochod();

bool sprawdz;
void PokazRanking(HWND);
void ZapisRankingD();
///////////////////////////////////////

//void DodajComboBox(HWND);
///////////////////////////////////////////////////////////////////////
// ZMIENNE OD OSI¥GNIEÆ




LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);                            // OKNO OSI¥GNIÊCIA
LRESULT CALLBACK HistoriaProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK RankingProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
////////////////////////////////////////////////////////////
//                        ZMIENNE                         //
////////////////////////////////////////////////////////////


int liczba_klikow_D; // ZMIENNA ++ GDY WCIŒNIEMY PRZYCISK DOCHÓD
int liczba_klikow_W; // ZMIENNA ++ GDY WCIŒNIEMY PRZYCISK WYDATEK
char tytul[20]; // TABLICA DO ZAPISYWANIA TEKSTU TYTU£
char portfel[10], zmiana[10];
float portfel_f, zmiana_f, ranking_f0, ranking_f1;

char zmiennaD[20],zmiennaTD[20],zmiennaW[20],zmiennaTW[20];                                 // ZMIENNE DO ZAPISU TEKSTU Z OKNA HISTORII, ABY ZAPISAÆ GO W PLIKU.TXT
char zmiennaRD0[10],zmiennaRW0[10];
char zmiennaRD1[10],zmiennaRW1[10];
char zmiennaRD2[10],zmiennaRW2[10];
char zmiennaRD3[10],zmiennaRW3[10];
char zmiennaRD4[10],zmiennaRW4[10];
char zmiennaRD5[10],zmiennaRW5[10];




HWND oknoD[5], oknoW[5], oknoTD[5], oknoTW[5];                                              // ZMIENNE DO OKIEN HISTORII

HWND oknoRD[5], oknoRW[5];


HWND hO2000N,hO2000T,hO10000N,hO10000T,hO50000N,hO50000T,hO100000N,hO100000T,hO1000000N,hO1000000T,hO5000000N,hO5000000T,hOwyd1,hOwyd2,hOwyd3;

HWND hSzukajOkno, hSzukajDochod, hSzukajWydatek, hKasuj;
HWND hOsiagi, hRanking;
HWND hStan;
HWND hTytul;
HWND hWartosc;
HWND hLogo;
HWND hDochodButton, hWydatekButton;
///////////////////////
HWND hHistoriaW, hHistoriaD, hHistoria;
/////////////////////// DO WYSWIELTANIA HISTORII


//HWND hComboBox;                       <-------- Combobox


HBITMAP hDodajObrazki, hDochodObrazek,hWydatekObrazek;

HBITMAP hOsiag2000N,hOsiag10000N, hOsiag50000N, hOsiag100000N, hOsiag1000000N, hOsiag5000000N, hOsiag2000T, hOsiag10000T, hOsiag50000T, hOsiag100000T, hOsiag1000000T, hOsiag5000000T,hOsiagwydatek1, hOsiagwydatek2, hOsiagwydatek3;


HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"MojeOknoKlasa";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

        registerOsiagiClass(hInst);
        registerHistoriaClass(hInst);
        registerRankingClass(hInst);

        CreateWindowW(L"MojeOknoKlasa",L"ZAKUPOHOLIK",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,600, NULL,NULL,NULL,NULL);
        MSG msg = {0};




        while( GetMessage(&msg,NULL,NULL,NULL) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    MessageBox(NULL,"DO NASTEPNEGO RAZU!","Kalkulator wydatkow",MB_OK); // OKNO POJAWIAJ¥CE SIÊ PO ZAKOÑCZENIU PROGRAMU
    return 0;
}

///////////////////////////////////////////////////////////////////////// FUNKCJONALNOŒÆ PROGRAMU

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
        case WM_COMMAND:

            switch(wp)
            {


                case MENU_ZAMKNIJ:
                    DestroyWindow(hWnd);
                    break;

                case MENU_WYDATEK:
                    MessageBeep(MB_ICONINFORMATION);
                    break;



                case MENU_DOCHOD:
                    MessageBeep(MB_APPLMODAL);
                    break;



                case MENU_POMOC:
                    MessageBeep(MB_CUR_MAX);
                    break;


                case MENU_HISTORIA:
                    PokazHistorie(hWnd);
                    break;

                case MENU_RANKING:
                    PokazRanking(hWnd);
                    break;




                case MENU_OSIAGNIECIA:
                    PokazOsiagi(hWnd);
                    break;



                case BUTTON_DOCHOD:
                    GetWindowText(hStan,portfel,10);
                    GetWindowText(hWartosc,zmiana,10);
                    GetWindowText(hTytul, tytul,20);
                    time();
                    if(zmiana[0] == NULL || tytul[0] == NULL)
                    {
                        break;
                    }
                    else
                    {
                        for(int i = 0; i<10; i++)                                        // ZAMIANA PRZECINKA NA KROPKÊ
                        {
                            if(zmiana[i] == ',')
                            {
                                zmiana[i] = '.';
                            }
                        }

                        string zd(zmiana);
                        for(int i=0;i<zd.length();i++)
                        {
                            if((zmiana[i]>='0' && zmiana[i]<='9') || zmiana[i] == '.')
                                sprawdz = TRUE;

                            else
                                sprawdz = FALSE;

                        }

                            if(sprawdz == TRUE)
                            {
                            string zd(zmiana);
                            string td(tytul);
                            cout <<zd<<endl;
                            cout <<td<<endl;
                            ss<<"INSERT into Dochody(Kwota,Tytul,Data) Values("+zd+",\""+td+"\", NOW());";
                            string query = ss.str();
                            const char* q = query.c_str();
                            qstate = mysql_query(conn,q);
                            if(qstate == 0)
                            cout<<"inserted";
                            else
                            cout<<"inserted failure";

                            //
                            liczba_klikow_D++;
                            portfel_f = atof(portfel);
                            zmiana_f = atof(zmiana);
                            portfel_f += zmiana_f;
                            sprintf(portfel,"%.2f",portfel_f);
                            SetWindowText(hStan, portfel);
                            DodajDochod();
                            ZapisDochody();
                            ZapisPortfel();
                            ZapisRankingD();
                            break;
                            }



                        }
                        break;

                case BUTTON_WYDATEK:
                    GetWindowText(hStan,portfel,10);                                    // Odczyt tekstu z okna Stan Konta:
                    GetWindowText(hWartosc,zmiana,10);                              // Odczyt wartoœci wpisanej w okno Kwota
                    GetWindowText(hTytul,tytul,20);
                    time();
                    if(zmiana[0] == NULL || tytul[0] == NULL)
                    {
                        break;
                    }
                    else
                    {
                        for(int i = 0; i<10; i++)                                           // ZAMIANA PRZECINKA NA KROPKÊ
                        {
                            if(zmiana[i] == ',')
                            {
                                zmiana[i] = '.';
                            }
                        }
                        string zd(zmiana);
                        for(int i=0;i<zd.length();i++)
                        {
                            if((zmiana[i]>='0' && zmiana[i]<='9') || zmiana[i] == '.')
                                sprawdz = TRUE;

                            else
                                sprawdz = FALSE;

                        }

                        if(sprawdz == TRUE)
                        {
                        liczba_klikow_W++;
                        portfel_f = atof(portfel);                                                 // U¿ycie funkcji atof na Stanie Portfela w celu zamiany znaków cyfr na cyfry, aby móc liczyæ
                        zmiana_f = atof(zmiana);                                                   // U¿ycie funkcji atof na Kwocie
                        portfel_f -= zmiana_f;                                                     // Odjêcie Kwoty od Stanu Portfela
                        sprintf(portfel,"%.2f",portfel_f);
                        SetWindowText(hStan, portfel);
                        DodajWydatek();
                        ZapisWydatki();
                        ZapisPortfel();
                        break;
                        }

                    }
                    break;







                case WYCZYSC_PORTFEL:
                    portfel_f = 0;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);
                    break;


                case SZUKAJ_DOCHOD:
                    WyszukajDochod();
                    break;
            }


            break;


        case WM_CREATE:
            Baza();
            DodajObrazki();
            DodajMenu(hWnd);
            DodajKontrolki(hWnd);
            time();
            PokazPortfel();
            PokazDochodyHistoria();
            PokazDochodyTytulyHistoria();
            PokazWydatkiHistoria();
            PokazWydatkiTytulyHistoria();
            break;


        case WM_DESTROY:
            ZapisPortfel();
            ZapisDochodyHistoria();
            ZapisDochodyTytulyHistoria();
            ZapisWydatkiHistoria();
            ZapisWydatkiTytulyHistoria();
            PostQuitMessage(0);
            break;


        default:
            return DefWindowProcW(hWnd,msg,wp,lp);
    }

}



void DodajMenu(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hMenuPlikow = CreateMenu();
    HMENU hDrugieMenu = CreateMenu();
    HMENU hRankingD = CreateMenu();
    HMENU hRankingW = CreateMenu();

    AppendMenu(hMenuPlikow,MF_STRING,WYCZYSC_PORTFEL,"Wyczysc");

//    AppendMenu(hDrugieMenu,MF_POPUP,(UINT_PTR)hRankingW,"Wydatki");
//
//    AppendMenu(hDrugieMenu,MF_POPUP,(UINT_PTR)hRankingD,"Dochody");


    AppendMenu(hMenuPlikow,MF_SEPARATOR,NULL,NULL);

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenuPlikow,"Portfel");

    AppendMenu(hMenu,MF_STRING,MENU_HISTORIA,"Historia");

    AppendMenu(hMenu,MF_POPUP,MENU_RANKING,"Ranking");

    AppendMenu(hMenu,MF_STRING,MENU_OSIAGNIECIA,"Osiagniecia");


    AppendMenu(hMenu,MF_STRING,MENU_ZAMKNIJ,"Zamknij");

    SetMenu(hWnd, hMenu);
}

void DodajKontrolki(HWND hWnd)
{
    CreateWindowW(L"Static", L"STAN KONTA", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 25, 100, 50, hWnd, NULL, NULL,NULL);

    hStan = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_CENTER, 201, 48, 98, 24, hWnd, NULL, NULL,NULL);

    CreateWindowW(L"Static", L"KWOTA: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 145, 60, 25, hWnd, NULL, NULL,NULL);

    hWartosc = CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 145, 100, 25, hWnd, NULL, NULL, NULL);  // OKIENKO DO WPISYWANIA WARTOŒCI DOCHODU/WYDATKU

    CreateWindowW(L"Static", L"TYTUŁ: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 180, 60, 25, hWnd, NULL, NULL,NULL);

    hTytul = CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 180, 100, 25, hWnd, NULL, NULL, NULL);

    hWydatekButton = CreateWindowW(L"Button", L"WYDATEK", WS_VISIBLE | WS_CHILD | BS_BITMAP, 35, 225, 75, 50, hWnd, (HMENU)BUTTON_WYDATEK, NULL, NULL);
    SendMessageW(hWydatekButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hWydatekObrazek);

    hDochodButton = CreateWindowW(L"Button", L"DOCHOD", WS_VISIBLE | WS_CHILD | BS_BITMAP, 35, 150, 75, 50, hWnd, (HMENU)BUTTON_DOCHOD, NULL, NULL);
    SendMessageW(hDochodButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDochodObrazek);

    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_BITMAP, 25, 25, 100, 50, hWnd, NULL, NULL,NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDodajObrazki);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                OKNA DOCHODY HISTORIA                                                    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int y = 378;
    hHistoriaD = CreateWindowW(L"Static", L"DOCHODY", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 325, 200, 25, hWnd, NULL, NULL,NULL);
    hHistoriaW = CreateWindowW(L"Static", L"WYDATKI", WS_VISIBLE | WS_CHILD | SS_CENTER, 255, 325, 200, 25, hWnd, NULL, NULL,NULL);
    for(int i=0; i<5; i++)
    {
        oknoD[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, y, 100, 25, hWnd, NULL, NULL,NULL);
        oknoTD[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, y, 100, 25, hWnd, NULL, NULL,NULL);
        oknoW[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, y, 100, 25, hWnd, NULL, NULL,NULL);
        oknoTW[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, y, 100, 25, hWnd, NULL, NULL,NULL);
        y = y + 28;
    }


    oknoData[0] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 320, 40, 100, 40, hWnd, NULL, NULL,NULL);
}

void DodajObrazki()
{
        hDodajObrazki = (HBITMAP)LoadImageW(NULL, L"nowelogo.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);

        hDochodObrazek = (HBITMAP)LoadImageW(NULL, L"dochodbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

        hWydatekObrazek = (HBITMAP)LoadImageW(NULL, L"wydatekbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
}

// <-------- Combobox
//void DodajComboBox(HWND hWnd)
//{
//     hComboBox = CreateWindowW(L"ComboBox", L"HISTORIA", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 200, 300, 100, 100, hWnd, NULL, NULL,NULL);
//
//
//}

void ZapisWydatki()
{
    fstream plik_wydatki;
    plik_wydatki.open("0Wydatki.txt", ios::out | ios::app);
    plik_wydatki<<zmiana_f;
    plik_wydatki<<tytul<<endl;
    plik_wydatki.close();
}


void ZapisDochody()
{
    fstream plik_dochody;
    plik_dochody.open("0Dochody.txt", ios::out | ios::app);
    plik_dochody<<zmiana_f;
    plik_dochody<<tytul<<endl;
    plik_dochody.close();

}

void ZapisPortfel()
{
    fstream plik_portfel;
    plik_portfel.open("0Stan Konta.txt", ios::out);
    plik_portfel<<portfel<<endl;
    plik_portfel.close();
}

void PokazPortfel()
{
    fstream plik_portfel;
    plik_portfel.open("0Stan Konta.txt", ios::in);
    if(plik_portfel.good()== false)
    {
        cout << "Nie mozna zaladowac stanu konta!" <<endl;
    }
    else
    {
            plik_portfel >> portfel;
            SetWindowText(hStan, portfel);
    }
}

void ZapisDochodyHistoria()
{
    fstream plik_dochodyhistoria;
    plik_dochodyhistoria.open("0Dochody Historia.txt", ios::out);
    for(int i=0;i<5;i++)
   {
        GetWindowText(oknoD[i],zmiennaD,20);
        plik_dochodyhistoria<<zmiennaD<<endl;

   }

}

void PokazDochodyHistoria()
{
    fstream plik_dochodyhistoria;
    plik_dochodyhistoria.open("0Dochody Historia.txt", ios::in);
    if(plik_dochodyhistoria.good()== false)
    {
        cout << "Nie mozna zaladowac kwoty z historii dochodów!" <<endl;
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            plik_dochodyhistoria>>zmiennaD;
            SetWindowText(oknoD[i], zmiennaD);
        }
    }

}
void ZapisDochodyTytulyHistoria()
{
    fstream plik_dochodytytulyhistoria;
    plik_dochodytytulyhistoria.open("0Dochody Tytuly Historia.txt", ios::out);
    for(int i=0;i<5;i++)
   {
       if(oknoTD[i] == '\0')
       {
           i++;
       }
       else
       {
            GetWindowText(oknoTD[i],zmiennaTD,20);
            plik_dochodytytulyhistoria<<zmiennaTD<<endl;
       }


   }
}

void PokazDochodyTytulyHistoria()
{
    fstream plik_dochodytytulyhistoria;
    plik_dochodytytulyhistoria.open("0Dochody Tytuly Historia.txt", ios::in);
    if(plik_dochodytytulyhistoria.good()== false)
    {
        cout << "Nie mozna zaladowac tytulow z historii dochodów!" <<endl;
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            plik_dochodytytulyhistoria>>zmiennaTD;
            SetWindowText(oknoTD[i], zmiennaTD);
        }
    }

}

void ZapisWydatkiHistoria()
{
    fstream plik_wydatkihistoria;
    plik_wydatkihistoria.open("0Wydatki Historia.txt", ios::out);
    for(int i=0;i<5;i++)
   {
        GetWindowText(oknoW[i],zmiennaW,20);
        plik_wydatkihistoria<<zmiennaW<<endl;

   }
}

void PokazWydatkiHistoria()
{
    fstream plik_wydatkihistoria;
    plik_wydatkihistoria.open("0Wydatki Historia.txt", ios::in);
    if(plik_wydatkihistoria.good()== false)
    {
        cout << "Nie mozna zaladowac kwoty z historii wydatkow!" <<endl;
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            plik_wydatkihistoria>>zmiennaW;
            SetWindowText(oknoW[i], zmiennaW);
        }
    }

}
void ZapisWydatkiTytulyHistoria()
{
    fstream plik_wydatkitytulyhistoria;
    plik_wydatkitytulyhistoria.open("0Wydatki Tytuly Historia.txt", ios::out);
    for(int i=0;i<5;i++)
   {
        GetWindowText(oknoTW[i],zmiennaTW,20);
        plik_wydatkitytulyhistoria<<zmiennaTW<<endl;

   }
}



void PokazWydatkiTytulyHistoria()
{
    fstream plik_wydatkitytulyhistoria;
    plik_wydatkitytulyhistoria.open("0Wydatki Tytuly Historia.txt", ios::in);
    if(plik_wydatkitytulyhistoria.good()== false)
    {
        cout << "Nie mozna zaladowac tytulow z historii dochodów!" <<endl;
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            plik_wydatkitytulyhistoria>>zmiennaTW;
            SetWindowText(oknoTW[i], zmiennaTW);
        }
    }

}

void DodajDochod()
{

    if(liczba_klikow_D == 6)
    {
        liczba_klikow_D = 1;
    }
    GetWindowText(hWartosc, zmiana,10);
    GetWindowText(hTytul, tytul,20);

    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKÊ
    {
        if(zmiana[i] == ',')
        {
            zmiana[i] = '.';
        }
    }
    SetWindowText(oknoD[liczba_klikow_D -1],zmiana);
    SetWindowText(oknoTD[liczba_klikow_D -1],tytul);





}


void DodajWydatek()
{
    if(liczba_klikow_W ==6)
    {
        liczba_klikow_W = 1;
    }
    GetWindowText(hWartosc, zmiana,10);
    GetWindowText(hTytul, tytul,20);

    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKÊ
    {
        if(zmiana[i] == ',')
        {
            zmiana[i] = '.';
        }
    }

    SetWindowText(oknoW[liczba_klikow_W -1],zmiana);
    SetWindowText(oknoTW[liczba_klikow_W -1],tytul);


}


/////////////////////////////////////////////////////////////
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
            case 1:
                DestroyWindow(hWnd);
                break;
        }
    case WM_CREATE:
        ObrazkiOsiagniecia();


    default:
        return DefWindowProcW(hWnd,msg,wp,lp);

    }
}

void registerOsiagiClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};
    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    dialog.hCursor = LoadCursor(NULL,IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"MojaOsiagiKlasa"; // dla lpsz zawsze L z prefixem
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);



}




void PokazOsiagi(HWND hWnd)
{
    HWND hOsiagi = CreateWindowW(L"MojaOsiagiKlasa",L"OSIAGNIECIA", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 100, 1000, 800, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button",L"Zamknij", WS_VISIBLE | WS_CHILD,870,720,100,40, hOsiagi,(HMENU)1,NULL,NULL);
    portfel_f = atof(portfel);


        hO2000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 20, 20, 150, 150, hOsiagi,NULL, NULL,NULL);
        hO10000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 177, 20, 150, 50, hOsiagi,NULL, NULL,NULL);
        hO50000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 334, 20, 150, 50, hOsiagi,NULL, NULL,NULL);
        hO100000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 491, 20, 100, 50, hOsiagi,NULL, NULL,NULL);
        hO1000000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 648, 20, 100, 50, hOsiagi,NULL, NULL,NULL);
        hO5000000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 805, 20, 100, 50, hOsiagi,NULL, NULL,NULL);

        if(portfel_f>=2000)
            SendMessageW(hO2000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag2000T);
        else
            SendMessageW(hO2000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag2000N);

        if(portfel_f>=10000)
            SendMessageW(hO10000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag10000T);
        else
            SendMessageW(hO10000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag10000N);

        if(portfel_f>=500000)
            SendMessageW(hO50000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag50000T);
        else
            SendMessageW(hO50000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag50000N);

        if(portfel_f>=100000)
            SendMessageW(hO100000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag100000T);
        else
            SendMessageW(hO100000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag100000N);

        if(portfel_f>=1000000)
            SendMessageW(hO1000000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag1000000T);
        else
            SendMessageW(hO1000000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag1000000N);

        if(portfel_f>=5000000)
            SendMessageW(hO5000000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag5000000T);
        else
            SendMessageW(hO5000000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag5000000N);



    //EnableWindow(hWnd, true); //wylaczenie okienka
}



void ObrazkiOsiagniecia()
{
    hOsiag2000N = (HBITMAP)LoadImageW(NULL, L"o2000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag2000T = (HBITMAP)LoadImageW(NULL, L"o2000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag10000N = (HBITMAP)LoadImageW(NULL, L"o10000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag10000T = (HBITMAP)LoadImageW(NULL, L"o10000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag50000N = (HBITMAP)LoadImageW(NULL, L"o50000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag50000T = (HBITMAP)LoadImageW(NULL, L"o50000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag100000N = (HBITMAP)LoadImageW(NULL, L"o100000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag100000T = (HBITMAP)LoadImageW(NULL, L"o100000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag1000000N = (HBITMAP)LoadImageW(NULL, L"o1000000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag1000000T = (HBITMAP)LoadImageW(NULL, L"o1000000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag5000000N = (HBITMAP)LoadImageW(NULL, L"o5000000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag5000000T = (HBITMAP)LoadImageW(NULL, L"o5000000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiagwydatek1 = (HBITMAP)LoadImageW(NULL, L"owydatek1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiagwydatek2 = (HBITMAP)LoadImageW(NULL, L"owydatek2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiagwydatek3 = (HBITMAP)LoadImageW(NULL, L"owydatek3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);



}




LRESULT CALLBACK HistoriaProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
            case 1:
                DestroyWindow(hWnd);
                break;
        }
    case WM_CREATE:




    default:
        return DefWindowProcW(hWnd,msg,wp,lp);

    }
}

void registerHistoriaClass(HINSTANCE hInst)
{
    WNDCLASSW historia = {0};
    historia.hbrBackground = (HBRUSH)COLOR_WINDOW;
    historia.hCursor = LoadCursor(NULL,IDC_CROSS);
    historia.hInstance = hInst;
    historia.lpszClassName = L"MojaHistoriaKlasa"; // dla lpsz zawsze l z prefixem
    historia.lpfnWndProc = HistoriaProcedure;

    RegisterClassW(&historia);



}



void PokazHistorie(HWND hWnd)
{
HWND hHistoria = CreateWindowW(L"MojaHistoriaKlasa",L"HISTORIA", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 500, 300, hWnd, NULL, NULL, NULL);

    hSzukajOkno = CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 20, 100, 40, hHistoria, NULL, NULL, NULL);
    hSzukajDochod = CreateWindowW(L"Button",L"Szukaj Dochód", WS_VISIBLE | WS_CHILD,200,20,120,40, hHistoria,(HMENU)SZUKAJ_DOCHOD,NULL,NULL);
    hSzukajWydatek =  CreateWindowW(L"Button",L"Szukaj Wydatek", WS_VISIBLE | WS_CHILD,200,70,120,40, hHistoria,NULL,NULL,NULL);
    CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | WS_BORDER | SS_BITMAP, 20, 100, 100, 50, hHistoria,NULL, NULL,NULL);
    hKasuj = CreateWindowW(L"Button",L"Kasuj", WS_VISIBLE | WS_CHILD,200,130,100,40, hHistoria,NULL,NULL,NULL);


}





LRESULT CALLBACK RankingProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
            case 1:
                DestroyWindow(hWnd);
                break;
        }
    case WM_CREATE:



    default:
        return DefWindowProcW(hWnd,msg,wp,lp);

    }
}

void registerRankingClass(HINSTANCE hInst)
{
    WNDCLASSW ranking = {0};
    ranking.hbrBackground = (HBRUSH)COLOR_WINDOW;
    ranking.hCursor = LoadCursor(NULL,IDC_CROSS);
    ranking.hInstance = hInst;
    ranking.lpszClassName = L"MojRankingKlasa"; // dla lpsz zawsze L z prefixem
    ranking.lpfnWndProc = RankingProcedure;

    RegisterClassW(&ranking);



}
void PokazRanking(HWND hWnd)
{
    HWND hRanking = CreateWindowW(L"MojRankingKlasa",L"RANKING", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 100, 300, 200, hWnd, NULL, NULL, NULL);
    int y=20;
    for(int i=1;i<5;i++)
    {

     oknoRD[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 20, y, 100, 25, hRanking, NULL, NULL,NULL);
     oknoRW[i] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 160, y, 100, 25, hRanking, NULL, NULL,NULL);
     y = y + 50;

    }


}

void ZapisRankingD()
{
    fstream plik_rankingd1;
    plik_rankingd1.open("rankingd1.txt",ios::out);
    if(plik_rankingd1.good()== false)
    {
        cout << "Nie mozna zaladowac 1st rank!" <<endl;
    }
    else
    {
    GetWindowText(hWartosc,zmiennaRD1,10);
    plik_rankingd1>>zmiennaRD0;
    if(zmiennaRD0 == NULL)
    {
        ranking_f0 = 0;
    }
    else
    {
    ranking_f0 = atof(zmiennaRD0);
    }

    ranking_f1 = atof(zmiennaRD1);
    if(ranking_f0<ranking_f1)
    {
        plik_rankingd1<<zmiennaRD1<<endl;
    }
    }

///////////////////////////






}

//////////////////
//void ZapisWydatkiTytulyHistoria()
//{
//    fstream plik_wydatkitytulyhistoria;
//    plik_wydatkitytulyhistoria.open("0Wydatki Tytuly Historia.txt", ios::out);
//    for(int i=0;i<5;i++)
//   {
//        GetWindowText(oknoTW[i],zmiennaTW,20);
//        plik_wydatkitytulyhistoria<<zmiennaTW<<endl;
//
//   }
//}
//
//
//
//void PokazWydatkiTytulyHistoria()
//{
//    fstream plik_wydatkitytulyhistoria;
//    plik_wydatkitytulyhistoria.open("0Wydatki Tytuly Historia.txt", ios::in);
//    if(plik_wydatkitytulyhistoria.good()== false)
//    {
//        cout << "Nie mozna zaladowac tytulow z historii dochodów!" <<endl;
//    }
//    else
//    {
//        for(int i=0;i<5;i++)
//        {
//            plik_wydatkitytulyhistoria>>zmiennaTW;
//            SetWindowText(oknoTW[i], zmiennaTW);
//        }
//    }
//
//}




///////////////////////////////

















void WyszukajDochod()
{
GetWindowText(hSzukajOkno,tekstd,30);
fstream plik("0Dochody.txt");
string tekst;
while(!plik.eof())
    {
        getline(plik, tekst);
        if(!(std::string::npos == tekst.find(tekstd)))
        {
            cout << tekst <<endl;
            n++;


        }

        else
           break;
}

/////////////////////////////////
//GetWindowText from EditBox - hSzukajOkno
//konwersja char tab[x] do string
//funkcja getline(nazwapliku,string)
//znalezc odpowiedni string w pliku ->if(!(std::string::npos == tekst.find(string)))
//odczytaæ kwotê zapisan¹ przed tytu³em, czyli zczytaæ wszystko do spacji
//zamieniæ odczytan¹ kwotê na typ float
//odj¹æ/dodaæ float od stanu portfela
////////////////////////////////////////

}

void Baza()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,server,username,password,dataBaseName,port,NULL,0);
    if(conn)
        cout<<"Polaczono z Baza Danych MySQL."<<endl;
    else
        cout<<"Nie polaczono z Baza Danych MySQL."<<endl;


    int qstate = 0;
    stringstream ss;
    float kwotaF = 90.50;
    string kwotaS = to_string(kwotaF);
    string tytul = "przelew";

  //  ss<<"INSERT into Wydatki(Kwota,Tytul,Data) Values("+kwotaS+",\""+tytul+"\", NOW());";
 //   string query = ss.str();
  //  const char* q = query.c_str();

  //  qstate = mysql_query(conn,q);
  //  if(qstate == 0)
  //      cout<<"inserted";
  //  else
   //     cout<<"inserted failure";

}


void time()
{
    time_t now = time(0);
    char* dt = ctime(&now);


    SetWindowText(oknoData[0],dt);
}
