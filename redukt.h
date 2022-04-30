#ifndef REDUKT_H_INCLUDED
#define REDUKT_H_INCLUDED

#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
bool wczytano;
bool dmax;
int REDUKT_ERROR;
string obliczenia;
HWND hText;
vector <int > D;

//obliczanie ilosci permutacji
long long int Newton(int n, int k){

if(k==0 || k==n)return 1;
	else return Newton(n-1,k-1)+Newton(n-1,k);
}


template <typename T> //permutacja dowolnego typu danych ale w sumie tylko int wiêc nie ma znaczenia
void permutacje(const std::vector<T>& v, int k, int n, int** A) // n ilosc permutacji obliczona ze wzoru
{

    assert(k <= v.size());//sprawdzam czy k< n w sumie bez sensu ;/
    std::vector<bool> bitset(k, 1); //towrze sobie wektorek pomocniczy
    bitset.resize(v.size(), 0); // ustawiam wszystko na false
int m=0;
int p=0;
    do {
    	p=0;
        for (int i = 0; i != v.size(); ++i) {
            if (bitset[i]) {
               A[m][p]= v[i];

               p++;
            }
        }
        m++;

    } while (std::prev_permutation(bitset.begin(), bitset.end()));

}


 // macierz D zadeklarowana globalnie dla u³atwienia xD
int mb,nb; // wymiary bazy tez globalnie bo zr¹ba³em funkcjê DRMAX :/
int * alfa(int** A, int n , int m){


	int max=0;

	for(int i=0;i<n;i++){

		for(int j=0;j<m;j++){

			if(max<A[i][j])max=A[i][j];
		}
	}

	int *ret=new int[m];
	for(int i=0;i<m;i++)ret[i]=0;
	bool h1[max+1];
	for(int i=0;i<=max;i++)h1[i]=false;

	for(int i=0;i<m;i++){

		for(int j=0;j<n;j++){

		h1[A[j][i]]=true;
		}
		for(int j=0;j<m;j++){

			if(h1[j]==true){
				h1[j]=false;
				if(ret[i]<max)ret[i]++;
			}

		}
	}

	return ret;
}

int * beta(int** A, int n , int m){

		int max=0;
	   int *ret=new int[m];
	for(int i=0;i<m;i++)ret[i]=0;

	for(int i=0;i<n;i++){

		for(int j=0;j<m;j++){

			if(max<A[i][j])max=A[i][j];
		}
	}


	int tab[max+1];
	for(int i=0;i<max+1;i++)tab[i]=0;


	int max2=0;
	int min=m;

for(int i=0;i<m;i++){
			for(int j=0;j<=max;j++)tab[j]=0;
		for(int j=0;j<n;j++){

		tab[A[j][i]]++;
		}

		for(int j=0;j<=max;j++){


				if(tab[j]>max2)max2=tab[j];
				if(tab[j]<min && tab[j]!=0)min=tab[j];


		}

		ret[i]=max2-min;
		max2=0;
		min=m;
	}
	return ret;
}

int teta(int ** A, int n, int m){//zwraca liczbê ró¿nych wierszy w zadanej tablicy
bool same=true;
	int ret=0;

	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			same=true;
			for(int k=0;k<m;k++){

					if(A[i][k]!=A[j][k]){
			same=false;
			}
		}
if(same){

			i++;
			j=i;
		}
	}

ret++;
}



	return ret;
}


bool dobrze_okreslona(int **B, int n, int m){


	bool same=true;

	for(int i=0;i<n-1;i++){

		for(int j=i+1; j<n ; j++){
				same=true;
		for(int k=0; k<m;k++){//to -1 jest zbedne ale funkcja cos odwala wiec dorzucilem rzeby nie robila przypalu

			if(B[i][k]!=B[j][k]){
			same=false;
			}
		}
		if(same){

			if(D[i]!=D[j])return false;
		}

		}
	}
	return true;


}

int ** add_column(int ** A, int *B, int n, int m){

	int ** ret=new int*[n+1];
	for(int i=0;i<n+1;i++)ret[i]=new int[m];

	for(int i=0;i<n;i++){

		for(int j=0;j<m;j++){

			ret[i][j]=A[i][j];
		}

	}

	for(int i=0;i<n;i++){

		ret[i][m]=B[i];
	}

	return ret;
}


void delete_column(int ** A,  int n, int m, int p){


	int p1=0;
	for(int i=0;i<m;i++){

	if(i!=p){
		for(int j=0;j<n;j++)A[j][p1]=A[j][i];
		p1++;
		}

	}

	//return A;
}

int ** delete_row(int ** A,  int n, int m, int p){


	int p1=0;
	for(int i=0;i<m;i++){

	if(i!=p){
		for(int j=0;j<n;j++)A[j][p1]=A[j][i];
		p1++;
	}

	}

	return A;
}


int ** add_row(int ** A, int *B, int n, int m){//dzia³a ;)



	for(int i=0;i<m;i++){

		A[n][i]=B[i];
	}
	return A;
}

int * ret_column(int **A, int m, int nb){

	int * ret=new int [m];

	for(int i=0;i<m;i++){
		ret[i]=A[i][nb];
	}
	return ret;
}

int *ret_row(int ** A,  int m , int p){


	int * ret=new int[m];

	for(int i=0;i<m;i++){
        ret[i]=A[p][i];

	}

	return ret;
}


int ** DRMAX_RS(int **A, int n,int m){

int h1[n][m]={0};
int ** T1;// tablica do przechowywania usunietych wektorów

T1=new int*[n];//tu s¹ zapisane usuniete wektory
for(int i=0;i<n;i++)T1[i]=new int[m];
int u=0;//liczba usunietych wektorów
int mu=m; //"szerokosc" usuniêtych wektorów
int T2[m]={0};//wektor pomocniczy
int m1=0; //rozmiar macierzy po uproszczeniu
int n1=0;
bool same=true;
bool same2=true;
//usówanie wierszy

for(int i=0;i<n;i++){

		for(int j=i+1;j<n;j++){
			same=true;
		for(int k=0;k<m;k++){

			if(A[i][k]!=A[j][k]){

			same=false;
			}
		}
		if(same){
			for(int j=0;j<m;j++)T2[j]=A[i][j];

			add_row(T1,T2,u,m);
			u++;
			i++;
			j=i;

		}
	}

			for(int j=0;j<m;j++){

		h1[n1][j]=A[i][j];

	}
	n1++;


}

//tworzenie macierzy D z macierzy h1 (macierzy A po usuniêciu wierszy)
D.resize(n);

for(int i=0;i<n1;i++){

	D[i]=h1[i][m-1];

}
for(int i=n1;i<n;i++)D[i]=T1[i-n1][m-1];
m--;

delete_column(T1,u,mu,mu-1);
mu--;
//usówanie kolumn
 //int h2[n1][m];
int ** h2=new int*[n1];
for(int i=0;i<n1;i++)h2[i]=new int[m];
for(int i=0;i<n1;i++){

	for(int j=0;j<m;j++)h2[i][j]=0;

}


for(int i=0;i<m;i++){


	for(int j=i+1;j<m;j++){
		same=true;
		same2=true;
		for(int k=0;k<n1;k++){

			if(h1[k][i]!=h1[k][j]){
				same=false;
			}

			if(k+1<n1){

				if(h1[k][i]!=h1[k+1][i]){

					same2=false;

				}

			}

		}

			if(i>=m-1){
			same2=true;

		for(int k=0;k<n1;k++){
			if(k+1<n1){

				if(h1[k][m]!=h1[k+1][m]){

					same2=false;

				}

			}
			}

		}



		if(same||same2){
		    delete_column(T1,u,mu,i);
		    mu--;
			i++;

			j=i;
		}
	}






		if(i>=m-1){//dodatkowy warunek dla ostatniej kolumny bo cos sie krzaczy :(
			same2=true;

		for(int k=0;k<n1;k++){
			if(k+1<n1){

				if(h1[k][m]!=h1[k+1][m]){

					same2=false;

				}

			}
			}
			if(!same2){

				for(int j=0;j<n1;j++){
					h2[j][m1]=h1[j][i];
			}
				m1++;
			}
			else{
				delete_column(T1,u,mu,i);
		    mu--;

			}
		}
		else
		{

			for(int j=0;j<n1;j++){
					h2[j][m1]=h1[j][i];
			}
				m1++;
		}




}
//tablica h2 to zredukowana tablica A



//wyznaczanie bazy macierzy
int n2=n1; //wymiary bazy
int m2=0;

int** t1 = new int*[n1];
for(int i=0;i<n1;i++)t1[i]=new int[m1];

for(int i=0;i<n1;i++){

	for(int j=0;j<m1;j++){

		t1[i][j]=h2[i][j];
	}
}

delete h1;
delete h2;

int *a=alfa(t1,n1,m1);
int *b=beta(t1,n1,m1);





//wyznaczanie pirwszego elementu w macierzy

int p1=0;
int p2=a[0]-b[0];

for(int i=0;i<m1;i++){

	if(a[i]-b[i]>p2){
		p2=a[i]-b[i];
		p1=i;
	}
}
// pierwsza kolumna to kolumna o indeksie p1;

int ** ret=new int*[n]; // macierz z baza
	for(int i=0;i<n;i++)ret[i]=new int[m];
int ** ret2=new int*[n]; // mam nadzieje ze sie przyda ;) i nie będzie się już krzaczyć
	for(int i=0;i<n;i++)ret2[i]=new int[m];

for(int i=0;i<n;i++){
	for(int j=0;j<m1;j++)ret[i][j]=0;
}
for(int i=0;i<n;i++){
	for(int j=0;j<m1;j++)ret2[i][j]=0;
}

int rozne_A=teta(t1,n1,m1); //liczba roznych wierszy w macierzy a

for(int i=0;i<n1;i++){ //zapisanie pierwszej kolumny do bazy

	ret[i][0]=t1[i][p1];
}


delete_column(t1,n1,m1,p1);//tablica glowna
delete_column(T1,u,mu,p1);//tablica z usunietymi wektorami
m1--;
mu--;
 m2=1;
 n2=n1;


 rozne_A=teta(t1,n1,m1); //liczba roznych wierszy w macierzy a

p1=0;
p2=teta(ret,n2,m2); //rozne wiersze w bazie
int p3=0;


//wyznaczanie ró¿nych wierszy itp
int p4[m1]={0};
while(rozne_A>p2 || !dobrze_okreslona(ret,n2,m2)){
	p1=0;

for(int i=0;i<m1;i++)	{

	p4[i]=teta(add_column(ret,ret_column(t1,n1,i),n2,m2),n2,m2+1);
	if(p4[i]>p1){

		p1=p4[i];
		p3=i;
}



}


ret=add_column(ret,ret_column(t1,n1,p3),n,m2);//n1 nie n2 zeby nie zmniejszyc dlogosci tablicy, zeby sie dalo potem dodac brakujace wiersze
	m2++;
	delete_column(t1,n1,m1,p3);
	m1--;
	delete_column(T1,u,mu,p3);
	mu--;
	p2=teta(ret,n2,m2);



}
//dodajemy usuniete wiersze do macierzy B

for(int i=0;i<u;i++){
	for(int j=0;j<m2;j++){

		ret[i+n2][j]=T1[i][j];
	}

}


delete[] T1;
delete[] t1;

nb=n;
mb=m2;


return ret;
}


// czêœæ odpowiedzialna za regu³y ...

struct rule_1{ // struktura zawiera nr kolumny i wartosc, podstruktura dla struktury rule_2

	int index; //index kolumny
	int value; // wartoœc
	rule_1(int _ndex, int _value);
	rule_1();

};

rule_1::rule_1(int _index, int _value){

	index=_index;
	value=_value;

}
rule_1::rule_1(){
	index=0;
	value=0;

}

rule_1	ret(rule_1 _A){

		return _A;
	}

struct rule_2{ //podstruktura dla struktury rule

	int D; // wartosc dla jakiej okreslona jest  regu³a

	rule_1 * R;
	int s; // rozmiar regu³y
	rule_2(int _D, int _s, rule_1 * _R);
	rule_2();

};

rule_2::rule_2(int _D, int _s, rule_1 * _R){

	D=_D;
	s=_s;
	R=new rule_1[_s];

	for(int i=0;i<_s;i++){
		R[i].value=_R[i].value;
		R[i].index=_R[i].index;

	}
}

rule_2::rule_2(){

	D=1;
	s=1;
	R=new rule_1[150];

}
rule_2 ret(rule_2 _A){
	return _A;
	}


struct rule {

	int s; // ilosc regu³
	rule_2 * R; //regu³y
	rule(int _s, rule_2 * _R);
	rule();

};

rule::rule(int _s, rule_2 * _R){

	s=3;
	R=new rule_2(_R->D, _R->s, _R->R );
	R->D=_R->D;
	R->s=_R->s;

	for(int i=0;i<s;i++){

			for(int j=0;j<_R->s;j++){

			R[0].R[j].value=_R[0].R[j].value;
			R[0].R[j].index=_R[0].R[j].index;
		}
	}

}

rule::rule(){

	s=2;
	R=new rule_2[500];// nie wiem czemu tak duzo ale ryckacć, pamięci nie braknie ;p
}





// funkcja do generowania macierzy B'
void gen_B2(int ** B2, int **B, int n, int m, int * A, int na){

	for(int i=0;i<n;i++){

		for(int j=0;j<na;j++){
			B2[i][j]=B[i][A[j]];

		}

	}

}


bool check_rule(int ** B, int n, int m, int p, int v, int ** d){ //sprawdzam czy dana regu³a jest prawdziwa to znaczy czy dla zadanych parametró B'1, B'2, ...., B'n zawsze mamy wartoœæ v, jeœli nie to lipa ;/
	//parametry to macierz B', liczba wierszy, lczba kolumn, pozycja znalezionej liczby, jej vartoœæ, macierz d (zdekomponowana macierz D)

	bool same=true;
	for(int i=0;i<n;i++){


		same=true;
			for(int j=0;j<m;j++){
				if(B[i][j]!=B[p][j]){
					same = false;
				}
			}
			if(same){

				if(d[i][v]!=d[p][v])return false;
			}

	}



	return true;
}


bool sprawdz_reguly(rule r, rule_2 r2){
	bool ret=false;

	for(int i=0;i<r.s;i++){

		if(r.R[i].D==r2.D){
			if(r.R[i].s==r2.s){
				ret=true;
			for(int j=0;j<r2.s;j++){

				if(r.R[i].R[j].index!=r2.R[j].value || r.R[i].R[j].index!=r2.R[j].value){
					ret=false;
				}
			}
			}
		}
		if(ret)return true;
	}

	return false;
}


rule copy_r(rule r, int w){// wykluczona wartosc;

rule ret;
ret.R=new rule_2[100];
ret.s=0;
for(int i=0;i<r.s;i++){/// kopiuje w sumie jeszcze nie wiem po co xD
if(i!=w){


    ret.R[ret.s].D=r.R[i].D;
ret.R[ret.s].s=r.R[i].s;

    for(int j=0;j<ret.R[ret.s].s;j++){

ret.R[ret.s].R[j].index=r.R[i].R[j].index;
ret.R[ret.s].R[j].value=r.R[i].R[j].value;

    }
ret.s++;
}
}
return ret;
}
rule copy_r2(rule &r, int w){// wykluczona wartosc;


int rs=0;
for(int i=0;i<r.s;i++){/// kopiuje w sumie jeszcze nie wiem po co xD
if(i!=w){


    r.R[rs].D=r.R[i].D;
r.R[rs].s=r.R[i].s;

    for(int j=0;j<r.R[rs].s;j++){

r.R[rs].R[j].index=r.R[i].R[j].index;
r.R[rs].R[j].value=r.R[i].R[j].value;

    }
rs++;
}
}
r.s=rs;

}

bool sprawdz_czy_spelnia(int ** d, int n, int m, rule r, int ** B){

bool p[n][m];
bool p1;

for(int i=0;i<n;i++){// ustawiam wartosci w tablicy decyzyjnej

    for(int j=0;j<m;j++){

        if(d[i][j]!=0)p[i][j]=false;
        else p[i][j]=true;
    }
}


for(int i=0;i<r.s;i++){

for(int l=0;l<n;l++){
    p1=true;
    for(int j=0;j<r.R[i].s;j++){


if(B[l][r.R[i].R[j].index]!=r.R[i].R[j].value)p1=false;

            }
if(p1)p[l][r.R[i].D]=true;
    }///l
}
p1=true;

for(int i=0;i<n;i++){// ustawiam wartosci w tablicy decyzyjnej

    for(int j=0;j<m;j++){

        if(p[i][j]==false)p1=false;

    }
}

return p1;
}




rule uprosc(rule r,int **d, int m, int n, int ** B){
rule ret=copy_r(r,-1);
bool p1=true;
bool p2=true;

cout<<"r.s="<<r.s<<endl;

while(p2){

p2=false;
    for(int i=0;i<ret.s;i++){


p1=sprawdz_czy_spelnia(d,n,m,copy_r(ret,i),B);
if(p1){

    copy_r2(ret,i);

    p2=true;
    i=ret.s;

}
}

}

return ret;
}



rule RULE_GEN1(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywać
rule ret;
cout<<n<<"=n m= "<<m<<endl;
REDUKT_ERROR=0;
	if(!dobrze_okreslona(B,n,m)){


		REDUKT_ERROR=1;
		return ret;
		//set some error
	}
if(m-1>n){
    REDUKT_ERROR=2;
    return ret;
    //set some error
}

	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}


	int **d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];


	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}



	//koniec dekompozycji

    bool pokrycie[n][max]; //tablica pomocnicza do wyznaczenia pokrycia xD
    for(int i=0;i<n;i++){

    	for(int j=0;j<max;j++){
    		if(d[i][j]!=0)pokrycie[i][j]=false;
    		else pokrycie[i][j]=true;
		}
	}



    std::vector < int > prm;
   for(int i =0;i<m-1;i++){
   	prm.push_back(i); //można dać i+1 żeby indeksować od 1 a nie od 0 ale to więcej pierdzielenia się puźniej ;/

   	}

    	long long int n1;


	int ** B1=new int*[n+1];
	for(int i=0;i<n;i++)B1[i]=new int[m+1];
	int A_size=0;
	int p1;

	for(int k=1; k<m;k++){
	    p1=Newton(n,k);
	    if(p1>A_size)A_size=p1;
	}

	int ** A=new int*[A_size+1];
	for(int i=0;i<A_size;i++)A[i]=new int[m];
    n1=prm.size();
    int n2=prm.size();
	ret.R=new rule_2[500];
	ret.s=0;
	bool p2=true;
    rule_2 r2;
	for(int j=0; j<max ; j++){ // index kolumny macierzy d
	for(int k=1; k<m;k++){

	 n1=Newton(n2,k);
	 permutacje(prm, k,n1,A);



		for(int i=0;i<n1;i++){
		gen_B2(B1,B, n,m,ret_row(A,k,i),k);// okej to jest troszkę pojebane xD i pamięciorzerne jak djabli (do optymalizacji jak fiks)


				for(int l=0;l<n;l++){

				if(d[l][j]!=0 && !pokrycie[l][j]){

				if(check_rule(B1,n,k,l,j,d)){


                            r2.D=j;
							r2.s=k;
						for(int x=0;x<k;x++){

							r2.R[x].index=A[i][x];
							r2.R[x].value=B[l][A[i][x]];

						}

                        if(!sprawdz_reguly(ret,r2)){







						pokrycie[l][j]=true;
							ret.R[ret.s].D=j;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[l][A[i][x]];

						}


						ret.s++;

						SetWindowText( hText, "Wczytano tablice!" );
                        }
					}
				}
				}
				p2=true;
for(int l=0;l<n;l++){

    if(pokrycie[l][j]==false)p2=false;
}
if(p2){

    i=n1;
    k=m;
}

			}

		}

	}

ret=uprosc(ret,d,max,n,B);

	for(int i=0;i<n;i++){
        delete[] d[i];
        delete[] B1[i];
	}
	delete [] d;
	delete [] B1;



	return ret;
}
// koniec RULE_GEN1


///ZMIENNE POMOCNICZE DO REDUKOWANIA

void testuj_regule(int ** B, int n,int m,  rule_2 r,int * ret){///Macierz B, liczba wierszy, badana reguła;

for(int i=0;i<m;i++)ret[i]=-1;
ret[m]=0;

int p=false;
for(int i=0;i<n;i++){
    p=true;
    for(int j=0;j<r.s;j++){

        if(B[i][r.R[j].index]!=r.R[j].value)p=false;

    }
    if(p){
        ret[ret[m]]=i;
        ret[m]++;

    }
}
}
///d,n,j,rule_data,vec_size,vec_p,m
int sprawdz_vektor(int **d, int n, int v, int ** v1, int s, int * v2, int m){

    ///macierz d, liczba wierszy, nr kolumny, vector z danymi o regulacch, jego rozmiar, dane badanej regulu, m to rozmiar macierzy B

bool p[n];
bool p2,p3;




for(int i=0;i<n;i++){

    if(d[i][v]!=0)p[n]=false;
    else p[n]=true;
}

for(int i=0;i<s;i++){

    for(int j=0;j<v1[i][m];j++){
        p[v1[i][j]]=true;
    }
}///ustawiam pokryte już wartości

for(int i=0;i<v2[m];i++){

    if(!p[v2[i]]){

        return -1;

    }
}

///sprawdzam czy nowa reguła zawiera stare i jednocześnie jest od nich większa


p2=false;
p3=false;


for(int i=0;i<s;i++){
p2=true;
    if(v2[m]>v1[i][m]){

        for(int j=0;j<v1[i][m];j++){
p3=false;
            for(int k=0;k<v2[m];k++){

                if(v1[i][j]==v2[k]){
                    p3=true;

                }
            }
            if(p3==true)p2=false;
        }

    }
if(p2){
    return i;

}

}








return -2;
}


rule RULE_GEN2(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywaæ

	rule ret;

	if(!dobrze_okreslona(B,n,m)){

		REDUKT_ERROR=1;
		return ret;
		//set some error
	}
if(m-1>n){
   REDUKT_ERROR=2;
    return ret;
    //set some error
}

	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}


	int **d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];


	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}



	//koniec dekompozycji

    bool pokrycie[n][max]; //tablica pomocnicza do wyznaczenia pokrycia xD
    for(int i=0;i<n;i++){

    	for(int j=0;j<max;j++){
    		if(d[i][j]!=0)pokrycie[i][j]=false;
    		else pokrycie[i][j]=true;
		}
	}



    std::vector < int > prm;
   for(int i =0;i<m-1;i++){
   	prm.push_back(i); //można dać i+1 żeby indeksować od 1 a nie od 0 ale to więcej pierdzielenia się puźniej ;/

   	}

    	long long int n1;


	int ** B1=new int*[n+1];
	for(int i=0;i<n;i++)B1[i]=new int[m+1];
	int A_size=0;
	int p1;

	for(int k=1; k<m;k++){
	    p1=Newton(n,k);
	    if(p1>A_size)A_size=p1;
	}

	int ** A=new int*[A_size+1];
	for(int i=0;i<A_size;i++)A[i]=new int[m];
    n1=prm.size();
    int n2=prm.size();
	ret.R=new rule_2[1000];
	ret.s=0;
	bool p2=true;
    rule_2 r2;

        /// na ostatniej pozycji zapisze sobie "dlogosc wektora" dlatego +1

	int ** rule_data=new int*[2*n];
	for(int i=0;i<2*n;i++)rule_data[i]=new int[2*m];
     int  *vec_p=new int[2*m]; /// wektor pomocniczy
	int vec_size=0; ///liczba dodanych reguł w sumie
	int vec_ret; ///zmienna pomocnicza dla zwracanych wartosci funkcji

	for(int j=0; j<max ; j++){ // index kolumny macierzy d
	for(int k=1; k<m;k++){

	 n1=Newton(n2,k);
	 permutacje(prm, k,n1,A);



		for(int i=0;i<n1;i++){
		gen_B2(B1,B, n,m,ret_row(A,k,i),k);// okej to jest troszkę pojebane xD i pamięciorzerne jak djabli (do optymalizacji jak fiks)


				for(int l=0;l<n;l++){

				if(d[l][j]!=0 ){

				if(check_rule(B1,n,k,l,j,d)){


                            r2.D=j;
							r2.s=k;
						for(int x=0;x<k;x++){

							r2.R[x].index=A[i][x];
							r2.R[x].value=B[l][A[i][x]];

						}

                        if(true){ ///!sprawdz_reguly(ret,r2)




                        ///---------------------------


                        testuj_regule(B,n,m,r2,vec_p);///sprawdzam jakie wartości pokrywa reguła




                        vec_ret=sprawdz_vektor(d,n,j,rule_data,vec_size,vec_p,m);///sprawdzam czy oplaca sie dodac ta regule
                        if(vec_ret!=-2){

                            if(vec_ret==-1){///jeśli reguła pokrywa niepokryty dodta delement

                            for(int x=0;x<m+1;x++){

                                rule_data[vec_size][x]=vec_p[x];

                            }

                                vec_size++;


                          ret.R[ret.s].D=j;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[l][A[i][x]];

						}


						ret.s++;

                            }///end ==-1
else{///jeśli reguła jest lepsza od innej regły w tablicy


     for(int x=0;x<m+1;x++){
                                rule_data[vec_size][x]=vec_p[x];

                            }

                           ret.R[ret.s].D=j;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[l][A[i][x]];

						}


}///end else
                        }///end !=-2

                        ///------------------------------





                        }
					}
				}
				}


			}



			p2=true;

	for(int x=0;x<n;x++){

        if(pokrycie[n][j]==false)p2=false;
	}
if(p2){
    k=m;
}


		}




	}
ret=uprosc(ret,d,max,n,B);
	for(int i=0;i<n;i++){
        delete[] d[i];
        delete[] B1[i];
	}
	delete [] d;
	delete [] B1;



	return ret;
}
//koniec RULE_GEN2

bool sprawdz_regule(rule_2 r){



for(int i=0;i<r.s;i++){

    for(int j=0;j<r.s;j++){

        if(i!=j){

            if(r.R[i].index==r.R[j].index)return false;

        }
    }
}
return true;
}

rule RULE_GEN3(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywaæ

rule ret;

	if(!dobrze_okreslona(B,n,m)){

		REDUKT_ERROR=1;
		return ret;
		//set some error
	}
if(m-1>n){
    REDUKT_ERROR=2;
    return ret;
    //set some error
}

	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}


	int **d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];


	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}



	//koniec dekompozycji

    bool pokrycie[n][max]; //tablica pomocnicza do wyznaczenia pokrycia xD
    for(int i=0;i<n;i++){

    	for(int j=0;j<max;j++){
    		if(d[i][j]!=0)pokrycie[i][j]=false;
    		else pokrycie[i][j]=true;
		}
	}



    std::vector < int > prm;
   for(int i =0;i<m-1;i++){
   	prm.push_back(i); //można dać i+1 żeby indeksować od 1 a nie od 0 ale to więcej pierdzielenia się puźniej ;/

   	}

    	long long int n1;


	int ** B1=new int*[n+1];
	for(int i=0;i<n;i++)B1[i]=new int[m+1];
	int A_size=0;
	int p1;

	for(int k=1; k<m;k++){
	    p1=Newton(n,k);
	    if(p1>A_size)A_size=p1;
	}

	int ** A=new int*[A_size+1];
	for(int i=0;i<A_size;i++)A[i]=new int[m];
    n1=prm.size();
    int n2=prm.size();
	ret.R=new rule_2[1000];
	ret.s=0;
	bool p2=true;
    rule_2 r2;

	for(int k=1; k<m;k++){

	 n1=Newton(n2,k);
	 permutacje(prm, k,n1,A);



		for(int i=0;i<n1;i++){
        for(int j=0; j<max ; j++){ // index kolumny macierzy d
		gen_B2(B1,B, n,m,ret_row(A,k,i),k);// okej to jest troszkę pojebane xD i pamięciorzerne jak djabli (do optymalizacji jak fiks)


				for(int l=0;l<n;l++){

				if(d[l][j]!=0 && !pokrycie[l][j]){

				if(check_rule(B1,n,k,l,j,d)){


                            r2.D=j;
							r2.s=k;
						for(int x=0;x<k;x++){

							r2.R[x].index=A[i][x];
							r2.R[x].value=B[l][A[i][x]];

						}

                        if(!sprawdz_reguly(ret,r2) && sprawdz_regule(r2)){







						pokrycie[l][j]=true;
							ret.R[ret.s].D=j;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[l][A[i][x]];

						}


						ret.s++;
                        }
					}
				}
				}
				p2=true;
for(int l=0;l<n;l++){
for(int x=0;x<max;x++)if(pokrycie[l][x]==false)p2=false;
}
if(p2){

    k=m;
}

			}

		}

	}
ret=uprosc(ret,d,max,n,B);
	for(int i=0;i<n;i++){
        delete[] d[i];
        delete[] B1[i];
	}
	delete [] d;
	delete [] B1;



	return ret;
}
//koniec RULE_GEN3

struct tablica{

int ** A;
int n;
int m;

};

tablica wczytaj_dane(string name){

tablica ret;

fstream tab1;
tab1.open(name.c_str(), ios::in | ios::out);



tab1>>ret.n;//liczba kolumn
tab1>>ret.m;//liczba wierszy


ret.A=new int*[ret.n];
for(int i=0;i<ret.n;i++)ret.A[i]=new int[ret.m];

	for(int i=0;i<ret.n;i++){

		for(int j=0;j<ret.m;j++){
			tab1>>ret.A[i][j];

		}


	}
	tab1.close();
return ret;
}


tablica wczytaj_dane_2(string name){

tablica ret;

fstream tab1;
tab1.open(name.c_str(), ios::in | ios::out);



tab1>>ret.n;//liczba kolumn
tab1>>ret.m;//liczba wierszy
D.resize(ret.n);

ret.A=new int*[ret.n];
for(int i=0;i<ret.n;i++)ret.A[i]=new int[ret.m];

	for(int i=0;i<ret.n;i++){

		for(int j=0;j<ret.m;j++){
			tab1>>ret.A[i][j];

		}

tab1>>D[i];

	}
	tab1.close();
return ret;
}





string int_to_string(int a){

string ret;

int l=0;


do{
l++;
    ret+=char(a%10+int('0'));

    a=a/10;
}while(a>0);

string ret2;

for(int i=l-1;i>=0;i--){

	ret2+=ret[i];
}
return ret2;
}

 char*  string_to_wchar(string a){
int l=a.length();

char * ret=new char[l];

for(int i=0;i<l;i++){

    ret[i]=a[i];
}
ret[l]='\0';
return ret;
}

string chang_mark(string a){
int l=a.length();

for(int i=0;i<l;i++){


    if(int(a[i])==92)a[i]='/';

}

return a;
}


int ** generuj_tablice(int n,int m,int z1,int z2){
wczytano=true;
dmax=false;
int ** ret;
ret=new int*[n];
for(int i=0;i<n;i++)ret[i]=new int[m];


for(int i=0;i<n;i++){

    for(int j=0;j<m-1;j++){

        ret[i][j]=(rand()%z1)+1;
    }
    ret[i][m-1]=(rand()%z2)+1;
}
bool p=true;
for(int i=0;i<n;i++){

    for(int j=i+1;j<n;j++){
p=true;
        for(int k=0;k<m-1;k++){
if(ret[i][k]!=ret[j][k])p=false;

        }
        if(p)ret[j][m-1]=ret[i][m-1];
    }

}

return ret;
}

int char_to_int(char *a){
int ret=0;
int p;
int s=0;

while(a[s]!='\0')s++;
if(s==0)return -1;
for(int i=0;i<s;i++)
{
    p=int(a[i])-int('0');
for(int j=0;j<s-i-1;j++)p*=10;
ret+=p;
}
return ret;
}

#endif // REDUKT_H_INCLUDED
