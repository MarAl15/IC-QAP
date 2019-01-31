#ifndef _AGBL_H
#define _AGBL_H

#include "datos.h"
#include "funciones.h"
#include "AG.h"
#include <iostream>

using namespace std;


/* ESQUEMA ESTACIONARIO */

// Se seleccionarán únicamente dos padres.

// OPERADOR DE SELECCIÓN: Se usará el torneo n-ario, consistente en elegir aleatoriamente n individuos de la población distintos y seleccionar el mejor de ellos.
// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).

// OPERADOR DE MUTACIÓN: Operador de intercambio para representación de orden. Se escogeran aleatoriamente otro gen con el que intercambiar el patrón existente en el gen a mutar.
class AGEBL: public AG{
	private:
		// Vector de permutaciones
		vector<int> solucion; 
		
		// Probabilidad de cruce
		//const float prob_cruce = 1;
		
		// Probabilidad de mutación.
		const float prob_mutacion = 0.75; //0.5
		
		// Probabilidad de mutación (por gen).
		const float prob_mutacion_gen = 0.05; 
		
		// El tamaño de la población será de M cromosomas.
		const unsigned M = 100; 
		
		// Número de generaciones a crear
		const unsigned EPOCAS = 100;
	public:
		// Constructor
		AGEBL( Datos & matrices, int seleccion = ALEATORIO, int mejora=BALDWIDIANA );
		
		// Consultor la solucion
		inline vector <int> & getSolucion(){
			return solucion;
		}		
};


#endif
