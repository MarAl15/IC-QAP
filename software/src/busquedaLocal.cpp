#include "busquedaLocal.h"
#include "funciones.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>    // std::random_shuffle

#include "random.h"

using namespace std;

// MINERIA DATOS: Utiliza técnicas 

// Constructor
BusquedaLocal::BusquedaLocal( Datos & matrices ){
	unsigned n = matrices.size(); // Número de característica
	int costeS, costeT;
	bool distinto;
	vector <int> S, T;
    
    // Inicialización
	for( unsigned j=0; j<n; j++ ){
		S.push_back(j);
	}
	random_shuffle(S.begin(), S.end());
	
	costeS = calcularFitness( matrices, S );
	
	do{
		solucion = S;
		
		distinto = false;
		for(unsigned i=0; i<n; i++){
			for(unsigned j=i+1; j<n; j++){
				// Intercambiar i con j
				T = S;
				T[i] = S.at(j);
				T[j] = S.at(i);	
				
				costeT = calcularFitness( matrices,  T);
				if(costeT<costeS){
					S = T;
					costeS = costeT;
					
					distinto = true;
				}			
			}
		}		
	}while(distinto);
	
	calcularFitness( matrices, solucion, true );
	cout << endl;
}


