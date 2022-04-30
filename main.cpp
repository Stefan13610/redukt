#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
/// Problem z rozmiarami zwracanymi przez drmax
#include <tchar.h>
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <ctime>
#include "redukt.h"

#include <iostream>

#define ID_PRZYCISK1 501
#define ID_PRZYCISK2 502
#define ID_PRZYCISK3 503
#define ID_PRZYCISK4 504
#define ID_PRZYCISK5 505
#define ID_PRZYCISK6 506
#define RADIO1 507
#define RADIO2 508
#define RADIO3 509
#define RADIO4 510
#define RADIO5 511
#define FRAME1 512
#define FRAME2 513
#define TAB1 514
#define TAB2 515
#define ID_PRZYCISK_OK 515
#define ID_PRZYCISK7 516
#define ID_T1 516
#define ID_T2 516
#define ID_T3 516
#define ID_T4 516
WNDCLASSEX wincl;
    HWND hwnd;
    HWND Generuj;
    HWND Generuj_n;// wymiary tablicy i maksymalne wartosci
    HWND Generuj_m;
    HWND Generuj_z1; //maksymalne wartosci w tablicy stanu
    HWND Generuj_z2; //maksymalne wartosci w tablicy D
    HWND wczytaj;
    HWND zapisz;
    HWND policz;
    HWND drmax;
    HWND pomoc;
    HWND radio_1; //GEN1
    HWND radio_2; //GEN2
    HWND radio_3; //GEN3
    HWND radio_4; //DRMAX
    HWND radio_5; //NO-DRMAX
    HWND border_1; //obramowanie dla GEN
    HWND border_2; //obramowanie dla DRMAX
    HWND border_3;
    HWND border_4;
    HWND border_5;
    HWND tabView;
    HWND tabView2;
    RECT rcl;
    ///HWND hText;
    HWND pomoc_window;
    HWND pomoc_ok;
    HWND pomoc_text;

    RECT rect;

    string czas_obliczen;
tablica dane;
int ratio_state=0;
  string get_filename(){
    string ret="";
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT;
    ofn.lpstrDefExt = "txt";

    if(GetOpenFileName(&ofn))
    {
        // Do something usefull with the filename stored in szFileName
        ret=szFileName;
    }
    return ret;
  }



    string get_filename_to_save(){
    string ret="";
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT;
    ofn.lpstrDefExt = "txt";

    if(GetSaveFileName(&ofn))
    {
        // Do something usefull with the filename stored in szFileName
        ret=szFileName;
    }
    return ret;
  }





  void wczytaj_plik(){


dane=wczytaj_dane(chang_mark(get_filename()));
DestroyWindow(tabView);

 int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;

tabView = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |LVS_EDITLABELS |ES_AUTOVSCROLL | WS_VSCROLL, 5, 20, width-180, 400,
hwnd,( HMENU ) TAB2, wincl.hInstance, NULL );





LVCOLUMN lvc;
lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;


std::string s = int_to_string(42);
for(int i=0;i<dane.m-1;i++){

s="";
s=int_to_string(i+1);
s="A"+s;

lvc.iSubItem = i;
lvc.cx = 30;

lvc.pszText = string_to_wchar(s);
ListView_InsertColumn( tabView, i, & lvc );
}
lvc.iSubItem = dane.m-1;
lvc.cx = 30;
lvc.pszText = "D";
ListView_InsertColumn( tabView, dane.m-1, & lvc );

LVITEM lvi;
lvi.mask = LVIF_TEXT;



for(int i=0;i<dane.m-1;i++){

    for(int j=0;j<dane.n;j++){
if(i==0){

    lvi.pszText = string_to_wchar(int_to_string(dane.A[j][i]));
lvi.iItem = j;
lvi.iSubItem = i;
ListView_InsertItem( tabView, & lvi );
}
else{

    ListView_SetItemText( tabView, j, i, string_to_wchar(int_to_string(dane.A[j][i])));
}


    }

}
 for(int j=0;j<dane.n;j++){

    ListView_SetItemText( tabView, j, dane.m-1, string_to_wchar(int_to_string(dane.A[j][dane.m-1])));

 }
//zapisanie wyniku

D.resize(dane.n);
for(int i=0;i<dane.n;i++)D[i]=dane.A[i][dane.m-1];

wczytano=true;

  }


 void DRM(){
const clock_t begin_time = clock();


DestroyWindow(tabView);

D.resize(dane.n);
for(int i=0;i<dane.n;i++)D[i]=dane.A[i][dane.m-1];
dane.A=DRMAX_RS(dane.A,dane.n,dane.m);

dane.n=nb;
dane.m=mb;

dmax=true;

GetWindowRect(hwnd, &rect);

  int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;

tabView = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |LVS_EDITLABELS |ES_AUTOVSCROLL | WS_VSCROLL, 5, 20, width-180, 400,
hwnd,( HMENU ) TAB2, wincl.hInstance, NULL );

LVCOLUMN lvc;
lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;


std::string s = int_to_string(42);
for(int i=0;i<dane.m;i++){


s=int_to_string(i+1);
s="B"+s;

lvc.iSubItem = i;
lvc.cx = 30;
lvc.pszText = string_to_wchar(s);
ListView_InsertColumn( tabView, i, & lvc );
}
lvc.iSubItem = dane.m;
lvc.cx = 30;
lvc.pszText = "D";
ListView_InsertColumn( tabView, dane.m, & lvc );

LVITEM lvi;
lvi.mask = LVIF_TEXT;



for(int i=0;i<dane.m;i++){

    for(int j=0;j<dane.n;j++){
if(i==0){

    lvi.pszText = string_to_wchar(int_to_string(dane.A[j][i]));
lvi.iItem = j;
lvi.iSubItem = i;
ListView_InsertItem( tabView, & lvi );
}
else{

    ListView_SetItemText( tabView, j, i, string_to_wchar(int_to_string(dane.A[j][i])));
}


    }

}
 for(int j=0;j<dane.n;j++){

    ListView_SetItemText( tabView, j, dane.m, string_to_wchar(int_to_string(D[j])));

 }

fstream restart;
restart.open("restart.txt", ios::in | ios::out);

restart<<dane.n<<" "<<dane.m+1<<endl;
for(int i=0;i<dane.n;i++){

    for(int j=0;j<dane.m+1;j++){

        restart<<dane.A[i][j]<<" ";
    }

    restart<<D[i]<<endl;
}
restart.close();


int czas= float( clock () - begin_time ) /  CLOCKS_PER_SEC;


 }

 void START(){


dane=wczytaj_dane_2("restart.txt");
dane.m--;



DestroyWindow(tabView);



dmax=true;

tabView = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |LVS_EDITLABELS |ES_AUTOVSCROLL | WS_VSCROLL, 5, 20, 620, 400,
hwnd,( HMENU ) TAB2, wincl.hInstance, NULL );

LVCOLUMN lvc;
lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;


std::string s = int_to_string(42);
for(int i=0;i<dane.m;i++){


s=int_to_string(i+1);
s="B"+s;

lvc.iSubItem = i;
lvc.cx = 30;
lvc.pszText = string_to_wchar(s);
ListView_InsertColumn( tabView, i, & lvc );
}
lvc.iSubItem = dane.m;
lvc.cx = 30;
lvc.pszText = "D";
ListView_InsertColumn( tabView, dane.m, & lvc );

LVITEM lvi;
lvi.mask = LVIF_TEXT;



for(int i=0;i<dane.m;i++){

    for(int j=0;j<dane.n;j++){
if(i==0){

    lvi.pszText = string_to_wchar(int_to_string(dane.A[j][i]));
lvi.iItem = j;
lvi.iSubItem = i;
ListView_InsertItem( tabView, & lvi );
}
else{

    ListView_SetItemText( tabView, j, i, string_to_wchar(int_to_string(dane.A[j][i])));
}


    }

}
 for(int j=0;j<dane.n;j++){

    ListView_SetItemText( tabView, j, dane.m, string_to_wchar(int_to_string(D[j])));

 }


 }





 void reguly(){
const clock_t begin_time = clock();

rule r;

 if(wczytano){

D.resize(dane.n);
    for(int i=0;i<dane.n;i++)D[i]=dane.A[i][dane.m-1];
if(ratio_state==1)r=RULE_GEN1(dane.A,dane.n,dane.m);
 if(ratio_state==2)r=RULE_GEN2(dane.A,dane.n,dane.m);
 if(ratio_state==3)r=RULE_GEN3(dane.A,dane.n,dane.m);
 }
 else{

   if(ratio_state==1)r=RULE_GEN1(dane.A,dane.n,dane.m+1);
 if(ratio_state==2)r=RULE_GEN2(dane.A,dane.n,dane.m+1);
 if(ratio_state==3)r=RULE_GEN3(dane.A,dane.n,dane.m+1);
 }
 cout<<"n="<<dane.n<<" m="<<dane.m<<endl;



 if(REDUKT_ERROR==1){
    MessageBox( hwnd, "Tablicja jest zle okreslona", "Info", MB_ICONINFORMATION );
    r.s=0;
 }
 if(REDUKT_ERROR==2){
    MessageBox( hwnd, "Liczba wierszy jest mniejsza od liczby kolumn. Najpierw urzyj DRMAX_RS", "Info", MB_ICONINFORMATION );
    r.s=0;
 }
	string sr;

	int max_v=0;
int czas= float( clock () - begin_time ) /  CLOCKS_PER_SEC;

string czas_s=int_to_string(czas);
czas_s="Czas obliczen "+czas_s+"[s]";
sr+=czas_s+"\r\n";

	for(int i=0;i<r.s;i++)if(max_v<r.R[i].D)max_v=r.R[i].D;

for(int x=0;x<=max_v;x++){



    for(int i=0;i<r.s;i++){
            if(r.R[i].D==x){
        sr+="\r\n";
    sr+="   "+int_to_string(i+1)+".";
	for(int j=0;j<r.R[i].s;j++){
		if(!wczytano)sr+="B"+int_to_string(r.R[i].R[j].index+1)+"("+int_to_string(r.R[i].R[j].value)+")";// wtf wypisuje coœ ca³kiem z dupy ?? dlaczego
		else sr+="A"+int_to_string(r.R[i].R[j].index+1)+"("+int_to_string(r.R[i].R[j].value)+")";
		if(j+1<r.R[i].s)sr+=" AND ";
	}
	sr+="---> D("+int_to_string(r.R[i].D+1)+")";

}
}

}

SetWindowText( hText, string_to_wchar(sr) );

 }


 void zapisz_dane(){

 string name=chang_mark(get_filename_to_save());
 fstream plik1;
 plik1.open(name.c_str(), ios::in | ios::out | ios::trunc);
if(dmax)plik1<<dane.n<<" "<<dane.m+1<<endl;
    else plik1<<dane.n<<" "<<dane.m<<endl;

 for(int i=0;i<dane.n;i++){

    if(dmax){
        for(int j=0;j<dane.m;j++)plik1<<dane.A[i][j]<<" ";
         plik1<<D[i]<<" "<<endl;
    }
    else {
        for(int j=0;j<dane.m;j++)plik1<<dane.A[i][j]<<" ";
    }

 }
TCHAR buff[2048];
GetWindowText(hText, buff, 2048);
plik1<<endl;
plik1<<buff;
plik1.close();
MessageBox( hwnd, "Zapisano!", "Info", MB_ICONINFORMATION );
 }

TCHAR szClassName2[ ] = _T("Redukt");
 void wyswietl_pomoc(){

pomoc_window = CreateWindow( szClassName2, TEXT( "Pomoc" ), WS_POPUP | WS_VISIBLE | WS_CAPTION,
    100, 100, 500, 500, hwnd, NULL, wincl.hInstance, NULL );
 pomoc_ok = CreateWindowEx( 0, "BUTTON", "Ok", WS_CHILD | WS_VISIBLE,
230, 430, 50, 30, pomoc_window, ( HMENU ) ID_PRZYCISK_OK, wincl.hInstance, NULL );
pomoc_text= CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 5, 5, 470, 400, pomoc_window, NULL,wincl.hInstance, NULL );


string linia;
string tekst_pomocy;
    fstream plik;

    plik.open("pomoc.txt", ios::in);
    if(plik.good() == true)
    {
        while(!plik.eof())
        {
            getline(plik, linia);
            tekst_pomocy+="\r\n"+linia;
        }
        plik.close();
    }

    SetWindowText( pomoc_text, string_to_wchar(tekst_pomocy) );


 }

 void resize_window(){


 DestroyWindow( wczytaj );
 DestroyWindow( Generuj_n );
 DestroyWindow( Generuj_m );
 DestroyWindow( Generuj_z1 );
 DestroyWindow( Generuj_z2 );
 DestroyWindow( Generuj );
 DestroyWindow( zapisz );
 DestroyWindow( policz );
 DestroyWindow( drmax );
 DestroyWindow( drmax );
 DestroyWindow( radio_1 );
 DestroyWindow( radio_2 );
 DestroyWindow( radio_2 );
 DestroyWindow( radio_3 );
 DestroyWindow( border_1 );
 DestroyWindow( border_2 );
 DestroyWindow( border_3 );
 DestroyWindow( border_4 );
 DestroyWindow( border_5 );
 DestroyWindow( hText );
 DestroyWindow( pomoc );
GetWindowRect(hwnd, &rect);

  int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;

   wczytaj = CreateWindowEx( 0, "BUTTON", "Wczytaj Tablice", WS_CHILD | WS_VISIBLE,
width-160, 10, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK1, wincl.hInstance, NULL );

Generuj_n = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE ,
width-158, 60, 60, 25, hwnd, NULL,wincl.hInstance, NULL );

Generuj_m = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE ,
width-98, 60, 60, 25, hwnd, NULL,wincl.hInstance, NULL );

Generuj_z1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE ,
width-158, 115, 60, 25, hwnd, NULL,wincl.hInstance, NULL );

Generuj_z2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE ,
width-98, 115, 60, 25, hwnd, NULL,wincl.hInstance, NULL );

   Generuj = CreateWindowEx( 0, "BUTTON", "Generuj", WS_CHILD | WS_VISIBLE,
width-160, 150, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK7, wincl.hInstance, NULL );
zapisz = CreateWindowEx( 0, "BUTTON", "Zapisz Wynik", WS_CHILD | WS_VISIBLE,
width-160, 400, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK2, wincl.hInstance, NULL );
policz = CreateWindowEx( 0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE,
width-160, 360, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK3, wincl.hInstance, NULL );
drmax=CreateWindowEx( 0, "BUTTON", "Redukuj Tablice", WS_CHILD | WS_VISIBLE,
width-160, 190, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK4, wincl.hInstance, NULL );
pomoc = CreateWindowEx( 0, "BUTTON", "Pomoc", WS_CHILD | WS_VISIBLE,
width-160, 500, 130, 30, hwnd, ( HMENU ) ID_PRZYCISK5, wincl.hInstance, NULL );

radio_1 = CreateWindowEx( 0, "BUTTON", "RULE_GEN1", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
width-150, 250, 100, 30, hwnd,( HMENU ) RADIO1, wincl.hInstance, NULL );
radio_2 = CreateWindowEx( 0, "BUTTON", "RULE_GEN2", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
width-150, 280, 100, 30, hwnd, ( HMENU ) RADIO2, wincl.hInstance, NULL );
radio_3 = CreateWindowEx( 0, "BUTTON", "RULE_GEN3", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
width-150, 310, 100, 30, hwnd, ( HMENU ) RADIO3, wincl.hInstance, NULL );



border_1=CreateWindowEx( 0, "button", "Wybor algorytmu", WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
width-165, 220, 140, 175, hwnd, ( HMENU ) FRAME1, wincl.hInstance, NULL );
border_2=CreateWindowEx( 0, "button", "Tablica", WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
1, 5,  width-170, 420, hwnd, ( HMENU ) FRAME1, wincl.hInstance, NULL );
border_3=CreateWindowEx( 0, "button", "Wynik", WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
1, 425, width-160, height-460, hwnd, ( HMENU ) FRAME1, wincl.hInstance, NULL );

 border_4=CreateWindowEx( 0, "button", "Generuj", WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
width-165, 40, 140, 145, hwnd, ( HMENU ) FRAME1, wincl.hInstance, NULL );

border_5=CreateWindowEx( 0, "button", "Maks. wartosc", WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
width-160, 95, 130, 50, hwnd, ( HMENU ) FRAME1, wincl.hInstance, NULL );


hText = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL  , 5, 440, width-170, height-480, hwnd, NULL,wincl.hInstance, NULL );


 }




 void generuj_t(){
TCHAR buff1[2048];
GetWindowText(Generuj_n, buff1, 2048);
TCHAR buff2[2048];
GetWindowText(Generuj_m, buff2, 2048);
TCHAR buff3[2048];
GetWindowText(Generuj_z1, buff3, 2048);
TCHAR buff4[2048];
GetWindowText(Generuj_z2, buff4, 2048);
int n=char_to_int(buff1);
int m=char_to_int(buff2);
int z1=char_to_int(buff3);
int z2=char_to_int(buff4);
if(n!=-1 && m!=-1 && z1!=-1 && z2!=-1){

    dane.n=n;
dane.m=m+1;
dane.A=generuj_tablice(dane.n,dane.m,z1,z2);



DestroyWindow(tabView);

int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;

tabView = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |LVS_EDITLABELS |ES_AUTOVSCROLL | WS_VSCROLL, 5, 20, width-180, 400,
hwnd,( HMENU ) TAB2, wincl.hInstance, NULL );





LVCOLUMN lvc;
lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;


std::string s = int_to_string(42);
for(int i=0;i<dane.m-1;i++){

s="";
s=int_to_string(i+1);
s="A"+s;

lvc.iSubItem = i;
lvc.cx = 30;

lvc.pszText = string_to_wchar(s);
ListView_InsertColumn( tabView, i, & lvc );
}
lvc.iSubItem = dane.m-1;
lvc.cx = 30;
lvc.pszText = "D";
ListView_InsertColumn( tabView, dane.m-1, & lvc );

LVITEM lvi;
lvi.mask = LVIF_TEXT;



for(int i=0;i<dane.m-1;i++){

    for(int j=0;j<dane.n;j++){
if(i==0){

    lvi.pszText = string_to_wchar(int_to_string(dane.A[j][i]));
lvi.iItem = j;
lvi.iSubItem = i;
ListView_InsertItem( tabView, & lvi );
}
else{

    ListView_SetItemText( tabView, j, i, string_to_wchar(int_to_string(dane.A[j][i])));
}


    }

}
 for(int j=0;j<dane.n;j++){

    ListView_SetItemText( tabView, j, dane.m-1, string_to_wchar(int_to_string(dane.A[j][dane.m-1])));

 }

wczytano=true;
dmax=false;

}else{

MessageBox( hwnd, "Wprowadz wymiary i zakresy", "Info", MB_ICONINFORMATION );
}



 }

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Redukt");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    hwnd;  /* This is the handle for our window */
wczytano=false;
dmax=false;
    MSG messages;            /* Here messages to the application are saved */


    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("TWORCA NIE MIAL POMYSLU NA NAZWE"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

srand(time(NULL));


resize_window();


GetClientRect( hwnd, & rcl );


//tabView = CreateWindowEx( 0, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT |LVS_EDITLABELS |ES_AUTOVSCROLL | WS_VSCROLL, 5, 20, 620, 400,
//hwnd,( HMENU ) TAB1, wincl.hInstance, NULL );


CheckRadioButton( hwnd, RADIO1, RADIO3, RADIO1 );
ratio_state=1;
//C:\Users\Stefan\Desktop\redukt\Redukt\tablica.txt
//



    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    //tu jest wszystko o przyciskach

// http://cpp0x.pl/kursy/Kurs-WinAPI-C++/Podstawy/Kontrolki/178

//START();

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);



    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_SIZE:
        resize_window();

        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);

         case WM_COMMAND:
switch( wParam )
{
case ID_PRZYCISK1: //wczytaj

dmax=false;
wczytaj_plik();

 //reguly();
 SetWindowText( hText, "Wczytano tablice!" );


    break;

case ID_PRZYCISK2: //zapisz
    zapisz_dane();
    break;

case ID_PRZYCISK3: //policz

    reguly();

    break;

case ID_PRZYCISK4: //pomoc
    if(wczytano && !dmax){
      DRM();
      SetWindowText( hText, "Zredukowano tablice!" );
      wczytano=false;
      //dmax=true;
    }
    else{
MessageBox( hwnd, "Najpierw wczytaj dane", "Info", MB_ICONINFORMATION );
}
    break;

case ID_PRZYCISK5: //pomoc
    wyswietl_pomoc();
    break;

case RADIO1: //pomoc
    CheckRadioButton( hwnd, RADIO1, RADIO3, RADIO1 );
    ratio_state=1;
    break;

case RADIO2: //pomoc
    CheckRadioButton( hwnd, RADIO1, RADIO3, RADIO2 );
    ratio_state=2;
    break;

case RADIO3: //pomoc
    CheckRadioButton( hwnd, RADIO1, RADIO3, RADIO3 );
    ratio_state=3;
    break;

case ID_PRZYCISK_OK:


CloseWindow(pomoc_window);
    break;

case ID_PRZYCISK7:
    generuj_t();
    SetWindowText( hText, "wygenerowano nowa tablice!" );
    break;

}
break;
break;

    }

    return 0;
}
