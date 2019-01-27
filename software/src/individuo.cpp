#include "individuo.h"
#include <iostream>

using namespace std;

Individuo::Individuo(){
	m = 0;
}

Individuo::Individuo( const unsigned int num ){  
	m = num;
	solucion = new int[m];
	fitness = 0;
}

// Se leen los datos de un fichero y se separan
void Individuo::calcularFitness( Datos & matrices ){
	unsigned n = matrices.size();
	
	fitness = 0; 
	for(unsigned i=0; i<n; i++){
		for(unsigned j=0; j<n; j++){
			fitness += matrices.getFlujo(i,j) * matrices.getDistancia(solucion[i], solucion[j]);
		}
	}
}

