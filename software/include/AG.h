#ifndef _GENETICOS_H
#define _GENETICOS_H

#include "datos.h"
#include <iostream>

using namespace std;

/* OPERADORES DE CRUCE */

// Operador BLX-alpha (alpha=0,3)
//void BLX( vector <float> & C1, vector <float> & C2 );

//  Operación de posición
//vector <int> Posicion( vector <int> & C1, vector <int> & C2 );

// Operador OX

// Operador PMX

/* VALORES DE LOS PARÁMETROS Y EJECUCIONES */
class AG{
	public:
		// Vector de pesos
		//vector <float> pesos;
		
		// El tamaño de la población será de 50 cromosomas.
		const unsigned M = 150; 
		
		// Probabilidad de mutación.
		//const float prob_mutacion = 0.75; 
		
		// Probabilidad de mutación (por gen).
		//const float prob_mutacion = 0.001; 

		// Criterio de parada: realizar  evaluaciones de la función objetivo.
		const unsigned MAX = 50000;
};
////////////////////


/* ESQUEMA GENERACIONAL CON ELITISMO */

// Se seleccionará una población de padres del mismo tamaño que la población genética.

// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos.
// Se aplicarán tantos torneos como individuos existan en la población genética, incluyendo los individuos ganadores en la población de padres.

// ESQUEMA DE REEMPLAZAMIENTO: La población de hijos sustituye automáticamente a la actual. Para conservar el elitismo, si la mejor solución de la generación anterior no sobrevive, sustituye directamente la peor solución de la nueva población.

// OPERADOR DE MUTACIÓN: Operador de intercambio para representación de orden. Se escogeran aleatoriamente otro gen con el que intercambiar el patrón existente en el gen a mutar. - CAMBIA DEL APC :(
class AGG: public AG{
	protected:
		// Vector de permutaciones
		vector<int> solucion; 
		
		// Probabilidad de cruce
		const float prob_cruce = 0.7;
		
		// Probabilidad de mutación (por gen).
		const float prob_mutacion = 0.001; 
		
	public:
		// Constructor
		AGG( Datos & matrices );
		
		// Consultor la solucion
		inline vector <int> & getSolucion(){
			return solucion;
		}
};

/* ESQUEMA ESTACIONARIO */

// Se seleccionarán únicamente dos padres.

// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos.
// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).

// ESQUEMA DE REEMPLAZAMIENTO: Los dos descendientes generados tras el cruce y la mutación (esta última aplicada según una determinada probabilidad) sustituyen a los dos peores de la población actual, en caso de ser mejores que ellos.

// OPERADOR DE MUTACIÓN: Operador de intercambio para representación de orden. Se escogeran aleatoriamente otro gen con el que intercambiar el patrón existente en el gen a mutar. - CAMBIA DEL APC :(
class AGE: public AG{
	private:
		// Vector de permutaciones
		vector<int> solucion; 
		
		// Probabilidad de cruce
		const float prob_cruce = 1;
		
		// Probabilidad de mutación.
		const float prob_mutacion = 0.75; 
		
		// Probabilidad de mutación (por gen).
		const float prob_mutacion_gen = 0.01; 
		
		// Número de generaciones a crear
		const unsigned NUM_POBLACIONES = 500;
	public:
		// Constructor
		AGE( Datos & matrices );
		
		unsigned torneo( vector <int> & valoraciones, unsigned tope );
		
		// Consultor la solucion
		inline vector <int> & getSolucion(){
			return solucion;
		}		
};


#endif
