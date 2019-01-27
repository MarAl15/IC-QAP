#ifndef _AGMEJ_H
#define _AGMEJ_H

#include "datos.h"
#include <iostream>

using namespace std;


/* ESQUEMA ESTACIONARIO */

// Se seleccionarán únicamente dos padres.

// OPERADOR DE SELECCIÓN: Se usará el torneo n-ario, consistente en elegir aleatoriamente n individuos de la población distintos y seleccionar el mejor de ellos.
// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).

// OPERADOR DE MUTACIÓN: Operador de intercambio para representación de orden. Se escogeran aleatoriamente otro gen con el que intercambiar el patrón existente en el gen a mutar.
class AGmej{
	private:
		// Vector de permutaciones
		vector<int> solucion; 
		
		// Probabilidad de cruce
		//const float prob_cruce = 1;
		
		// Probabilidad de mutación.
		const float prob_mutacion = 0.75; 
		
		// Probabilidad de mutación (por gen).
		const float prob_mutacion_gen = 0.001; 
		
		// El tamaño de la población será de M cromosomas.
		const unsigned M = 150; 
		
		// Número de generaciones a crear
		const unsigned NUM_POBLACIONES = 500;
	public:
		// Constructor
		AGmej( Datos & matrices );
		
		// Consultor la solucion
		inline vector <int> & getSolucion(){
			return solucion;
		}		
};


#endif
