#include "funciones.h"
#include "random.h"
#include <iostream>
#include <algorithm>
//#include <math.h>
//#include <limits>

//DISTRIBUCION NORMAL
//#include <random>

using namespace std;


// 
int calcularFitness( Datos & matrices, vector <int> solucion, bool imprimir ){
	unsigned n = matrices.size();
	
	int fitness = 0; 
	for(unsigned i=0; i<n; i++){
		for(unsigned j=0; j<n; j++){
			fitness += matrices.getFlujo(i,j) * matrices.getDistancia(solucion.at(i), solucion.at(j));
		}
	}
	
	if(imprimir){
		cout << "	Solucion: ";
		for(unsigned i=0; i<solucion.size(); i++)
			cout << solucion.at(i) << " ";
		cout << endl;
		
		cout << "	Fitness: " << fitness << endl;
	}
	
	return fitness;
}

/* OPERADORES DE CRUCE */

// PMX
void PMX(vector <int> & C1, vector <int> & C2){
	unsigned ini = Randint(0,C1.size()-3), //C1.size()/4,
			 fin = Randint(ini+1,C1.size()-1);//ini+C1.size()/2;
			 
	vector <int> correspondencias1, correspondencias2, AuxC1, AuxC2;
	
	// Inicializamos el vector
	for(unsigned i=0; i<C1.size(); i++){
		correspondencias1.push_back(-1);
		correspondencias2.push_back(-1);
	}
	
	// Almacenamos las correspondencias
	for(unsigned i=ini; i<fin; i++){
		correspondencias1[C1.at(i)] = C2.at(i);
		correspondencias2[C2.at(i)] = C1.at(i);
	}
		
	for(unsigned i=0; i<ini; i++){
		int k = C2.at(i);
		while(correspondencias1.at(k) != -1)
			k = correspondencias1.at(k);
		AuxC1.push_back(k);
		
		k = C1.at(i);
		while(correspondencias2.at(k) != -1)
			k = correspondencias2.at(k);
		AuxC2.push_back(k);
	}
	
	for(unsigned i=fin; i<C1.size(); i++){
		int k = C2.at(i);
		while(correspondencias1.at(k) != -1)
			k = correspondencias1.at(k);
		AuxC1.push_back(k);
		
		k = C1.at(i);
		while(correspondencias2.at(k) != -1)
			k = correspondencias2.at(k);	
		AuxC2.push_back(k);
	}
	
	unsigned j = 0;
	
	for(unsigned i=0; i<ini; i++,j++){
		//cout << i << endl;
		C1[i] = AuxC1.at(j);
		C2[i] = AuxC2.at(j);
	}
	
	for(unsigned i=fin; i<C1.size(); i++,j++){
		//cout << i << endl;
		C1[i] = AuxC1.at(j);
		C2[i] = AuxC2.at(j);	
	}
}

/* TORNEO */
unsigned torneo( vector <int> & valoraciones, int M, unsigned n ){
	vector <unsigned> participantes;
	unsigned mejor = Randint( 0, M-1 ); // M = cromosomas.size()
	participantes.push_back(mejor);
	
	for( unsigned j=0; j<n; j++ ){
		unsigned k = Randint( 0, M-1 );
		
		while( find(participantes.begin(), participantes.end(), k)!=participantes.end() )
			k = Randint( 0, M-1 );
		participantes.push_back(k);
		
		if( valoraciones.at(k) < valoraciones.at(mejor) )
			mejor = k;
	}
	
	return mejor;
}

