#include "busquedaLocal.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>    // std::random_shuffle

#include "random.h"

using namespace std;

// MINERIA DATOS: Utiliza técnicas 

// Constructores
BusquedaLocal::BusquedaLocal(){}
BusquedaLocal::BusquedaLocal( Datos & matrices ){
	unsigned n = matrices.size(); // Número de característica
	vector <int> S;
    
    // Inicialización
	for( unsigned j=0; j<n; j++ ){
		S.push_back(j);
	}
	random_shuffle(S.begin(), S.end());

	// Búsqueda local
	BL(matrices , S, calcularFitness(matrices, S));
	
	calcularFitness( matrices, solucion, true );
	cout << endl;
}

int BusquedaLocal::BL( Datos & matrices, vector <int> & sol, int coste, int mejora ){
	unsigned n = matrices.size(); // Número de característica
	int fitness, costeS=coste,
				 costeT;
	bool distinto;
	vector <int> S=sol,
				 T;
    
	do{
		solucion = S;
		fitness = costeS;
		
		distinto = false;
		for(unsigned i=0; i<n; i++){
			for(unsigned j=i+1; j<n; j++){
				// Intercambiar i con j
				T = S;
				T[i] = S.at(j);
				T[j] = S.at(i);	
				
				//costeT = calcularFitness( matrices,  T);
				costeT = ajustarFitness( matrices,  S,T, costeS, i,j);
				//cout << costeT << endl;
				//cout << calcularFitness( matrices,  T) << endl;
				//cout << endl;
				if(costeT<costeS){
					S = T;
					costeS = costeT;
					
					distinto = true;
				}			
			}
		}		
	//}while(distinto);
	}while(costeT<fitness);
	
	//calcularFitness( matrices, solucion, true );
	//cout << endl;
	//cout << fitness << endl;
	if(mejora == LAMARCKIANA)
		sol = solucion;
		
	return fitness;
}


