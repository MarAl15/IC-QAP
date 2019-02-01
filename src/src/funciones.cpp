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
int calcularFitness( Datos & matrices, vector <int> & solucion, bool imprimir ){
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

int ajustarFitness( Datos & matrices, vector <int> & solucion_ant, vector <int> & solucion, int coste_ant, unsigned i, unsigned j ){
	unsigned n = matrices.size();
	
	int fitness = coste_ant; 
	for(unsigned k=0; k<n; k++){
	//	for(unsigned j=0; j<n; j++){
		fitness -= (matrices.getFlujo(i,k) * matrices.getDistancia(solucion_ant.at(i), solucion_ant.at(k))
				 + matrices.getFlujo(j,k) * matrices.getDistancia(solucion_ant.at(j), solucion_ant.at(k)));
		fitness += matrices.getFlujo(i,k) * matrices.getDistancia(solucion.at(i), solucion.at(k))
				 + matrices.getFlujo(j,k) * matrices.getDistancia(solucion.at(j), solucion.at(k));
				 
		if (k != i) {
            fitness -= matrices.getFlujo(k,i) * matrices.getDistancia(solucion_ant.at(k), solucion_ant.at(i));
			fitness += matrices.getFlujo(k,i) * matrices.getDistancia(solucion.at(k), solucion.at(i));
		}
		if (k != j) {
            fitness -= matrices.getFlujo(k,j) * matrices.getDistancia(solucion_ant.at(k), solucion_ant.at(j));
			fitness += matrices.getFlujo(k,j) * matrices.getDistancia(solucion.at(k), solucion.at(j));
		}
	}
	
	return fitness;
}


// Suma de las componentes de un vector
int sum(vector <int> v){
	int result = v.at(0);
	
	for(unsigned i=1; i<v.size(); i++)
		result += v.at(i);
		
	return result;
}
