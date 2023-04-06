#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;

void zamien(int* a, int* b)
{
	int* temp = a;
	a = b;
	b = temp;
	return;
}

void sortowaniePrzezWstawianie(int arr[], int* begin, int* end)
{
	int lewy = begin - arr;
	int prawy = end - arr;

	for (int i = lewy + 1; i <= prawy; i++) {
		int key = arr[i];
		int j = i - 1;

		while (j >= lewy && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}

	return;
}

int* podzial(int arr[], int low, int high)
{
	int srodek = arr[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= srodek) {
			i++;

			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (arr + i + 1);
}

int* ktoraWieksza(int* a, int* b, int* c)
{
	if (*a < *b && *b < *c)
		return (b);

	if (*a < *c && *c <= *b)
		return (c);

	if (*b <= *a && *a < *c)
		return (a);

	if (*b < *c && *c <= *a)
		return (c);

	if (*c <= *a && *a < *b)
		return (a);

	if (*c <= *b && *b <= *a)
		return (b);

    return a; // żeby pozbyć się warninga przy kompilacji
}


void IntrosortUtil(int arr[], int* begin, int* end,
				int depthLimit)
{
	int size = end - begin;

	if (size < 16) {
		sortowaniePrzezWstawianie(arr, begin, end);
		return;
	}

	if (depthLimit == 0) {
		make_heap(begin, end + 1);
		sort_heap(begin, end + 1);
		return;
	}

	int* srodek
		= ktoraWieksza(begin, begin + size / 2, end);

	zamien(srodek, end);

	int* partitionPoint
		= podzial(arr, begin - arr, end - arr);
	IntrosortUtil(arr, begin, partitionPoint - 1,
				depthLimit - 1);
	IntrosortUtil(arr, partitionPoint + 1, end,
				depthLimit - 1);

	return;
}

void sortowanieIntrospektywne(int arr[], int* begin, int* end)
{
	int depthLimit = 2 * log(end - begin);

	IntrosortUtil(arr, begin, end, depthLimit);

	return;
}

bool czyPosortowanaRosnaco(int *tab, int n){

    for(int i = 0; i < n-1; i++){
        if (tab[i] > tab[i+1]) return false;
    }

    return true;
}

bool czyPosortowanaMalejaco(int *tab, int n){

    for(int i = 1; i < n-1; i++){
        if (tab[i] < tab[i+1]) return false;
    }

    return true;
}

void wypiszElementy(int *tab, int n){
    std::cout << "\n"; 
    for(int i=0; i<n; i++){
        std::cout << tab[i] << " ";
    }
}

void generujTablice(int *tab, int n, int typ, double procent){

switch(typ){
    case 0:
        for (int i = 0; i <= n; i++){
            tab[i] = rand() % (n+1) ;
        }
    break;
    case 1:
        {
        int posortowane = n*procent;
        for (int i = 0; i<posortowane; i++){
            tab[i]=i;
        }

        for(int i = posortowane; i <= n; i++){
            tab[i] = i + (rand() % n);
        }
        }
    break;
    case 2:
        for (int i = 0; i <= n ; i++){
            tab[i] = n-i;
        }
    break;

    default:
        std:cout << "Błąd! Zły typ tablicy do wygenerowania!\n";
        exit(0);

    }
}

void zbiorTablic(std::vector<int*> &tablice,int n, int typ, double procent){
    for(int i = 0; i <= 99; i++){
        tablice.push_back(new int[n]);
    }

    for(int i = 0; i <= 99; i++){
        generujTablice(tablice[i],n,typ,procent);
    }
}



int *pom; //tablica pomocnicza do scalania

void scal(int *tab, int lewy, int srodek, int prawy) 
{
	int i = lewy, j = srodek + 1;
 
  for(int i = lewy;i<=prawy; i++) 
    pom[i] = tab[i];  
  

  for(int k=lewy;k<=prawy;k++) 
  if(i<=srodek)
    if(j <= prawy)
         if(pom[j]<pom[i])
             tab[k] = pom[j++];
         else
             tab[k] = pom[i++];
    else
        tab[k] = pom[i++];
  else
      tab[k] = pom[j++];
}

void sortowaniePrzezScalanie(int *tab,int lewy, int prawy)
{
	if(prawy<=lewy) return; 
	
	int srodek = (prawy+lewy)/2;
	
	sortowaniePrzezScalanie(tab, lewy, srodek); 
	sortowaniePrzezScalanie(tab, srodek+1, prawy);
	
	scal(tab, lewy, srodek, prawy);
}





void quickSort(int *tab, int lewy, int prawy){

    if (prawy <= lewy) return;

    int i = lewy -1, j = prawy +1, srodek = tab[(lewy+prawy)/2];

        while(1){
            while(srodek>tab[++i]);

            while(srodek<tab[--j]);

            if (i<=j){
                std::swap(tab[i],tab[j]);
            }else{
                break;
            }
        }
    if(j>lewy){
        quickSort(tab,lewy,j);
    }
    if(i<prawy){
        quickSort(tab,i,prawy);
    }
}
    void sortujTablice(std::vector<int*> &tablice,int typ, int n){
        switch(typ){
            case 1:
            for(int i = 0;i < 99; i++){
                quickSort(tablice[i],0, n-1);
            }
            break;
              case 2:
            for(int i = 0;i < 99; i++){
                sortowaniePrzezScalanie(tablice[i],0, n-1);
            }
            break;
              case 3:
            for(int i = 0;i < 99; i++){
                sortowanieIntrospektywne(tablice[i],tablice[i], tablice[i] + n -1);
            }
            break;


        }
    }

    void obrocTablice(int * tablica, int n){
        for(int i = 0; i <= n; i++){
            pom[i] = tablica[i];
        }

        for(int i = 0; i <= n; i++){
            tablica[i] = pom[n-i];
        }
    }



int main(){
    int n, *tab;
    int rozmiar = 10000;
    std::vector<int*> tablice;

    zbiorTablic(tablice, rozmiar, 0,0);
    pom = new int[rozmiar];

    auto start = std::chrono::high_resolution_clock::now();
    sortujTablice(tablice,1,rozmiar);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << czyPosortowanaRosnaco(tablice[57],rozmiar);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end- start);

    return 0;
}