#ifndef REDUKT_H_INCLUDED
#define REDUKT_H_INCLUDED

#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
//obliczanie permutacji
int silnia(int n){

	int ret =1;

	for(int i=1;i<=n;i++)ret*=i;
	return ret;

}

template <typename T> //permutacja dowolnego typu danych ale w sumie tylko int wiêc nie ma znaczenia
int ** permutacje(const std::vector<T>& v, int k, int n) // n ilosc permutacji obliczona ze wzoru
{

	int ** ret;
	ret=new int*[n];
	for(int i=0;i<n;i++)ret[i]=new int[k];

    assert(k <= v.size());
    std::vector<bool> bitset(k, 1);
    bitset.resize(v.size(), 0);
int m=0;
int p=0;
    do {
    	p=0;
        for (int i = 0; i != v.size(); ++i) {
            if (bitset[i]) {
               ret[m][p]= v[i];

               p++;
            }
        }
        m++;

    } while (std::prev_permutation(bitset.begin(), bitset.end()));
    return ret;
}


int * D; // macierz D zadeklarowana globalnie dla u³atwienia xD
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


int ** delete_column(int ** A,  int n, int m, int p){


	int p1=0;
	for(int i=0;i<n;i++){

	if(i!=p){
		for(int j=0;j<m;j++)A[j][p1]=A[j][i];
		p1++;
		}

	}

	return A;
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

	for(int i=0;i<m;i++)ret[i]=A[p][i];

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
D=new int[n];

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
	for(int i=0;i<n;i++)ret[i]=new int[m1];

for(int i=0;i<n;i++){
	for(int j=0;j<m1;j++)ret[i][j]=0;
}

int rozne_A=teta(t1,n1,m1); //liczba roznych wierszy w macierzy a

for(int i=0;i<n1;i++){ //zapisanie pierwszej kolumny do bazy

	ret[i][0]=t1[i][p1];
}
delete_column(t1,n1,m1,p1);
delete_column(T1,u,mu,p1);
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
while(rozne_A>p2){
	p1=0;

for(int i=0;i<m1;i++)	{

	p4[i]=teta(add_column(ret,ret_column(t1,n1,i),n2,m2),n2,m2+1);
	if(p4[i]>p1){

		p1=p4[i];
		p3=i;
}



}
ret=add_column(ret,ret_column(t1,n1,p3),n,m2);//n nie n2 zeby nie zmniejszyc dlogosci tablicy, zeby sie dalo potem dodac brakujace wiersze
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
	R=new rule_1[1000];

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
	R=new rule_2[10000];// nie wiem czemu tak duzo ale ryckacć, pamięci nie braknie ;p
}




bool dobrze_okreslona(int **B, int n, int m){


	bool same=true;

	for(int i=0;i<n;i++){

		for(int j=i+1; j<n ; j++){
				same=true;
		for(int k=0; k<m-1;k++){//to -1 jest zbedne ale funkcja cos odwala wiec dorzucilem rzeby nie robila przypalu

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
// funkcja do generowania macierzy B'
int ** gen_B2(int **B, int n, int m, int * A, int na){

	int ** ret;
	ret=new int*[n];
	for(int i=0;i<n;i++)ret[i]=new int[na];


	for(int i=0;i<n;i++){

		for(int j=0;j<na;j++){

			ret[i][j]=B[i][A[j]];

		}

	}
	return ret;
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

rule RULE_GEN1(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywać

	if(!dobrze_okreslona(B,n,m)){

		cout<<"tablica jest zle okreslona"<<endl;
	}
	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}

	int ** d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];

	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}
	//koniec dekompozycji


	int rule_number=0; // ilość dodanych reguł
    bool pokrycie[n][max]; //tablica pomocnicza do wyznaczenia pokrycia xD
    for(int i=0;i<n;i++){

    	for(int j=0;j<max;j++){
    		if(d[i][j]!=0)pokrycie[i][j]=false;
    		else pokrycie[i][j]=true;
		}
	}


    std::vector < int > prm;
   for(int i =0;i<m;i++){
   	prm.push_back(i); //można dać i+1 żeby indeksować od 1 a nie od 0 ale to więcej pierdzielenia się puźniej ;/
   	}
    	int n1;


	int ** B2;
	int ** A;
	rule ret;
	ret.R=new rule_2[1000];
	ret.s=0;
	for(int j=0; j<n ; j++){ // index kolumny macierzy d
	for(int k=1; k<=m;k++){
		n1=prm.size();
	 n1=silnia(n1)/(silnia(k)*silnia(n1-k));
	A= permutacje(prm, k,n1);


		for(int i=0;i<n1;i++){
		B2=gen_B2(B, n,m,ret_row(A,k,i),k);// okej to jest troszkę pojebane xD i pamięciorzerne jak djabli (do optymalizacji jak fiks)
//stare miejsce pętli j


				for(int l=0;l<max;l++){

				if(d[j][l]!=0 && !pokrycie[j][l]){

				if(check_rule(B2,n,k,j,l,d)){

						pokrycie[j][l]=true;
							ret.R[ret.s].D=l;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[j][A[i][x]];


						}




						ret.s++;

					}
				}
				}

			}

		}

	}




	return ret;
}
// koniec RULE_GEN1

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
///ZMIENNE POMOCNICZE DO REDUKOWANIA REGOL
int row_numbers[1000];
int rule_numbers[1000];
int row_numbers_size;
int rule_numbers_size;
/// coś tu jest skopane ;/
int * ret_row_numbers(int **B, int n, int m, rule_2 r){
row_numbers_size=0;
int * ret=new int[1000];

bool p=true;
for(int i=0;i<n;i++){

p=true;
    for(int j=0;j<r.s;j++){
if(B[i][r.R[j].index]!=r.R[j].value)p=false;


    }
    if(p){

        row_numbers[row_numbers_size]=i;

        row_numbers_size++;

    }
}

}

void ret_rule_numbers(rule r,int ** B, int n,int m, int p){// p nr wiersza w macierzy D i B ale w sumie liczy się tylko B

rule_numbers_size=0;

bool p1=true;
for(int i=0;i<r.s;i++){

    for(int j=0;j<r.R[i].s;j++){

        if(B[p][r.R[i].R[j].index]!=r.R[i].R[j].value)p1=false;

    }

if(p1){

   rule_numbers[rule_numbers_size]=i;
   rule_numbers_size++;

}
}


}





rule redukuj_reguly(rule r, int ** B, int n, int m, int ** d , int m2 ){// przekazuje macierz B, wymiary macierzy B, macierz d i jej liczba kolumn,

int t[r.s][2];// tablica pierwsza kolumna zawiera wrtosc ktorą pokrywa a 2 liczbe pokryć



rule ret;
ret.s=0;
bool pokrycie[n][m2];

for(int i=0;i<n;i++){

    for(int j=0;j<m2;j++){

        if(d[i][j]!=0)pokrycie[i][j]=false;
        else pokrycie[i][j]=true;
    }
}




for(int i=0;i<r.s;i++){
ret_row_numbers(B,n,m,r.R[i]);
t[i][0]=r.R[i].D;
t[i][1]=row_numbers_size;
}

int p1=0;//p1 to pozycja maxymalnej wartosci
int p3=-1000; // maxymalna wartosc

for(int i=0;i<n;i++){

  for(int j=0;j<m2;j++){

    if(d[i][j]!=0)pokrycie[i][j]=false;
        else pokrycie[i][j]=true;
 }
}

int i=0;
while(i<m2){
p3=-1;

    for(int j=0;j<r.s;j++){ // wyznaczam regule ktora pokrywa najwiecej wartosci
if(t[j][1]>=p3 && t[j][0]==i){

    p3=t[j][1];
    p1=j;
}
}

    t[p1][1]=-1; // dodaje ta regule i ustawiam jej pokrycie na -1


    ret.R[ret.s].D=r.R[p1].D;
    ret.R[ret.s].s=r.R[p1].s;

    for(int j=0;j<ret.R[ret.s].s;j++){

        ret.R[ret.s].R[j].value=r.R[p1].R[i].value;
        ret.R[ret.s].R[j].index=r.R[p1].R[i].index;
    }


    ret.s++;


 ret_row_numbers(B,n,m,r.R[p1]);



for(int j=0;j<row_numbers_size;j++){
    pokrycie[row_numbers[j]][i]=true;
ret_rule_numbers(r,B,n,m,rule_numbers[j]);

for(int l=0;l<rule_numbers_size;l++){

    //t[rule_numbers[l]][1]--;

}

}


    p1=true;
    for(int j=0;j<n;j++){ //sprawdzam czy wszystkie wartości w d[i] zostaly pokryte

        if(pokrycie[j][i]==false)p1=false;
cout<<pokrycie[j][i]<<" ";
    }
cout<<endl;


if(p1){

    i++;
    cout<<"m="<<m<<" i="<<i<<endl;
}

}



return ret;

}


rule remove_wrong_rule(rule r){
int p=0;
rule ret;
ret.s=0;
bool p1=true;
for(int i=0;i<r.s;i++){
        p1=true;
    for(int j=0;j<r.R[i].s;j++){

        for(int k=0;k<r.R[i].s;k++){

if(k!=j && r.R[i].R[j].index==r.R[i].R[k].index)p1=false;
        }

    }
if(p1){
    ret.R[p].s=r.R[i].s;
    ret.R[p].D=r.R[i].D;
     for(int j=0;j<ret.R[p].s;j++){
    ret.R[p].R[j].value=r.R[i].R[j].value;
    ret.R[p].R[j].index=r.R[i].R[j].index;
    }
p++;
ret.s++;
}


}

return ret;

}


rule RULE_GEN2(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywaæ

	if(!dobrze_okreslona(B,n,m)){

		//cout<<"tablica jest zle okreslona"<<endl;
	}
	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}

	int ** d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];

	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}
	//koniec dekompozycji


	int rule_number=0; // iloœæ dodanych regu³
    //tablica pomocnicza do wyznaczenia pokrycia xD



    std::vector < int > prm;
   for(int i =0;i<m;i++){
   	prm.push_back(i); //mo¿na daæ i+1 ¿eby indeksowaæ od 1 a nie od 0 ale to wiêcej pierdzielenia siê puŸniej ;/
   	}
    	int n1;


	int ** B2;
	int ** A;
	rule ret;
	ret.R=new rule_2[10000];
	ret.s=0;
	rule_2 r2;
	for(int j=0; j<n ; j++){
	for(int k=1; k<=m;k++){
		n1=prm.size();
	 n1=silnia(n1)/(silnia(k)*silnia(n1-k));
	A= permutacje(prm, k,n1);


		for(int i=0;i<n1;i++){
		B2=gen_B2(B, n,m,ret_row(A,k,i),k);// okej to jest troszkê pojebane xD i pamiêciorzerne jak djabli (do optymalizacji jak fiks)



				for(int l=0;l<max;l++){

				if(d[j][l]!=0 ){

				if(check_rule(B2,n,k,j,l,d)){



							r2.D=l;
							r2.s=k;
						for(int x=0;x<k;x++){

							r2.R[x].index=A[i][x];
							r2.R[x].value=B[j][A[i][x]];


						}

					if(!sprawdz_reguly(ret,r2)){//sprawdzam czy regula jest juz w tablicy, jesli nie to ja dodaje
							ret.R[ret.s].D=l;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[j][A[i][x]];


						}




						ret.s++;

					}



					}
				}
				}

			}

		}

	}

ret=remove_wrong_rule(ret);
ret=redukuj_reguly(ret,B,n,m,d,max);

	return ret;
}
//koniec RULE_GEN2

rule RULE_GEN3(int ** B, int n, int m){// D jest zadeklarowane globalnie wiec nie ma po co jej przekazywaæ

	if(!dobrze_okreslona(B,n,m)){

		cout<<"tablica jest zle okreslona"<<endl;
	}
	//dekompozycja macierzy D
	int max=0;

	for(int i=0;i<n;i++){
		if(D[i]>max)max=D[i];
	}

	int ** d=new int*[n];
	for(int i=0;i<n;i++)d[i]=new int[max];

	for(int i=0;i<n;i++){

		for(int j=0;j<max;j++){

			if(D[i]==j+1)d[i][j]=j+1;
			else d[i][j]=0;

		}

	}
	//koniec dekompozycji


	int rule_number=0; // iloœæ dodanych regu³
    bool pokrycie[n][max]; //tablica pomocnicza do wyznaczenia pokrycia xD
    for(int i=0;i<n;i++){

    	for(int j=0;j<max;j++){
    		if(d[i][j]!=0)pokrycie[i][j]=false;
    		else pokrycie[i][j]=true;
		}
	}


    std::vector < int > prm;
   for(int i =0;i<m;i++){
   	prm.push_back(i); //mo¿na daæ i+1 ¿eby indeksowaæ od 1 a nie od 0 ale to wiêcej pierdzielenia siê puŸniej ;/
   	}
    	int n1;


	int ** B2;
	int ** A;
	rule ret;
	ret.R=new rule_2[200];
	ret.s=0;
	rule_2 r2;
	for(int k=1; k<=m;k++){
		n1=prm.size();
	 n1=silnia(n1)/(silnia(k)*silnia(n1-k));
	A= permutacje(prm, k,n1);


		for(int i=0;i<n1;i++){
		B2=gen_B2(B, n,m,ret_row(A,k,i),k);// okej to jest troszkê pojebane xD i pamiêciorzerne jak djabli (do optymalizacji jak fiks)

			for(int j=0; j<n ; j++){

				for(int l=0;l<max;l++){

				if(d[j][l]!=0 && !pokrycie[j][l]){

				if(check_rule(B2,n,k,j,l,d)){



							r2.D=l;
							r2.s=k;
						for(int x=0;x<k;x++){

							r2.R[x].index=A[i][x];
							r2.R[x].value=B[j][A[i][x]];


						}

					if(!sprawdz_reguly(ret,r2)){//sprawdzam czy regula jest juz w tablicy, jesli nie to ja dodaje
							pokrycie[j][l]=true;
							ret.R[ret.s].D=l;
							ret.R[ret.s].s=k;
						for(int x=0;x<k;x++){

							ret.R[ret.s].R[x].index=A[i][x];
							ret.R[ret.s].R[x].value=B[j][A[i][x]];


						}




						ret.s++;

					}



					}
				}
				}

			}

		}

	}



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
#endif // REDUKT_H_INCLUDED
