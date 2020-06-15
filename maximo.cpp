//g++ orden.cpp -std=c++11 -lpthread -o orden.out
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <chrono>
#include <time.h>
#include <bits/stdc++.h>
#include <fstream>
#include <thread>

using namespace std;



void imprimir(vector<int>& arreglo,int longitud){
	for(int i=0;i<longitud;i++){
		cout<<arreglo[i]<<" ";
	}
	cout<<endl;
}

//QUICK SORT
int Particion(vector<int>& arreglo, int inicio, int fin)  
{  
	 int pivote=arreglo[fin];
	 int i=inicio-1;

	 int auxiliar;	 

	 for(int j=inicio;j<fin;j++){
			if(arreglo[j]<=pivote){
				i=i+1;
				auxiliar=arreglo[i];
				arreglo[i]=arreglo[j];
				arreglo[j]=auxiliar;
			}
	 }
	 auxiliar=arreglo[i+1];
	 arreglo[i+1]=arreglo[fin];
	 arreglo[fin]=auxiliar;

	return i+1;
	
}  

void QuickSort(vector<int>& arreglo, int inicio, int fin) 
{  
	if(inicio<fin){
		int medio=Particion(arreglo,inicio,fin);
		QuickSort(arreglo,inicio,medio-1);
		
		QuickSort(arreglo,medio+1,fin);
	}
}

//MERGE SORT
void Intercala(vector<int>& arreglo, int inicio,int medio, int fin){
	vector<int> auxiliar(fin-inicio+1);
	int i;
	int j;
	int k;
	for(i=inicio;i<=medio;i++){
		auxiliar[i-inicio]=arreglo[i];
	}
	for(j=medio+1;j<=fin;j++){
		auxiliar[fin+medio+1-j-inicio]=arreglo[j];
	}
	i=inicio;
	j=fin;
	for(k=inicio;k<=fin;k++){
		if(auxiliar[i-inicio]<=auxiliar[j-inicio]){
			arreglo[k]=auxiliar[i-inicio];
			i=i+1;
		}else{
			arreglo[k]=auxiliar[j-inicio];
			j=j-1;
		}
	}

}

void MergeSort(vector<int>& arreglo, int inicio, int fin){
	if(inicio<fin){
		int medio=floor((inicio+fin)/2);
		MergeSort(arreglo,inicio,medio);
		MergeSort(arreglo,medio+1,fin);
		Intercala(arreglo,inicio,medio,fin);
		
	}	

}

//INSERTION SORT
void InsertionSort(vector<int>& arreglo,int longitud){
	for(int j=1;j<longitud;j++){
		int clave=arreglo[j];
		int i=j-1;
		while(i>=0 && arreglo[i]>clave){
			arreglo[i+1]=arreglo[i];
			i=i-1;
		}
		arreglo[i+1]=clave;
	}

}

//BUBBLE SORT
void BubbleSort(vector<int>& arreglo,int longitud)  
{  
	 int auxiliar;
    for (int i = 0; i < longitud-1; i++){            
	    // Last i elements are already in place  
	    for (int j = 0; j < longitud-i-1; j++){  
	        if (arreglo[j] > arreglo[j+1]){
					 auxiliar=arreglo[j];
					 arreglo[j]=arreglo[j+1];
					 arreglo[j+1]=auxiliar;
				}
		 }
	 }
}

int contador;

//Algoritmo Maximo
int maximo(vector<int>& arreglo,int longitud,int& cont){
	int m=arreglo[0];
	for(int i=1;i<longitud;i++){
		if(arreglo[i]>m){
			m=arreglo[i];
			cont++;
		}
	}

	return m;
}

int main(){

	 int NUM_PUNTOS=13;

    // X, Y valores de los puntos a graficar
	 vector<double> valoresX(NUM_PUNTOS);
	 valoresX.reserve(NUM_PUNTOS);
	 vector<double> valoresY(NUM_PUNTOS);
	 valoresY.reserve(NUM_PUNTOS);
	 vector<double> valoresY2(NUM_PUNTOS);
	 valoresY2.reserve(NUM_PUNTOS);

	 vector<double> registrados(200);
	 valoresY2.reserve(200);

	 srand(time(NULL));
	 contador=0;

	 int maxval;
	 int prom;

	 for(int n=0;n<NUM_PUNTOS;n++){
		 double longitud = pow(2,(n+8));

		 valoresX[n] =longitud;
		 
		 vector<int> arr(longitud);
		 arr.reserve(longitud);

		 prom=0;
		 for(int j=0;j<200;j++){
			 for(int i=1;i<=longitud;i++){
				arr[i-1]=1 + rand() % ( (int)longitud - 1);
			 }
			 maxval=maximo(arr,(int)longitud,contador);
			 registrados[j] =contador;
			 contador=0;
			 prom=prom+registrados[j];
		 }	  	 
		 prom=prom/200;
		 valoresY[n] =prom;
		 prom=0;
		 
		 valoresY2[n]=n+9;
		 
	 }
	 
	 //Lee el archivo puntosGraficar par aguardar los valores
    FILE * archivoPuntos = fopen("Maximo.txt", "w");
    FILE * archivoPuntos2 = fopen("Log(n)+1.txt", "w");
	
    for (int i=0;i<NUM_PUNTOS;i++){
 		 fprintf(archivoPuntos, "%lf %lf \n", valoresX[i], valoresY[i]);
 	 }
	 
    for (int i=0;i<NUM_PUNTOS;i++){
 		 fprintf(archivoPuntos2, "%lf %lf \n", valoresX[i], valoresY2[i]);
 	 }

    fclose(archivoPuntos);
    fclose(archivoPuntos2);

   return 0;

}
