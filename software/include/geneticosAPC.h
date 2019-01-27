#ifndef _GENETICOS_H
#define _GENETICOS_H

#include "datos.h"
#include <iostream>

using namespace std;

/* OPERADORES DE CRUCE */

// Operador BLX-alpha (alpha=0,3)
void BLX( vector <float> & C1, vector <float> & C2 );

/* VALORES DE LOS PARÁMETROS Y EJECUCIONES */
class AG{
	public:
		// Vector de pesos
		//vector <float> pesos;
		
		// El tamaño de la población será de 30 cromosomas.
		const unsigned M = 30; 

		// Probabilidad de mutación (por gen).
		const float prob_mutacion = 0.001; 

		// Criterio de parada: realizar 15000 evaluaciones de la función objetivo.
		const unsigned MAX = 15000;
};
////////////////////


/* ESQUEMA GENERACIONAL CON ELITISMO */

// Se seleccionará una población de padres del mismo tamaño que la población genética.

// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos.
// Se aplicarán tantos torneos como individuos existan en la población genética, incluyendo los individuos ganadores en la población de padres.

// ESQUEMA DE REEMPLAZAMIENTO: La población de hijos sustituye automáticamente a la actual. Para conservar el elitismo, si la mejor solución de la generación anterior no sobrevive, sustituye directamentela peor solución de la nueva población.

// OPERADOR DE MUTACIÓN: Operador de mutación normal para representación real con sigma=0,3.
class AGG: public AG{
	protected:
		// Vector de pesos
		vector <float> pesos;
		
		// Probabilidad de cruce
		const float prob_cruce = 0.7;
		
	public:
		// Constructor
		AGG( Datos & matriz, const bool blx = true );
		
		// Consultor del número de pesos que hay
		inline unsigned size(){
			return pesos.size();
		}
		
		// Consultor de pesos (W)
		inline vector <float> & getPesos(){
			return pesos;
		}
		
		// Consultor del peso i-ésimo
		inline float getPeso( unsigned i ){
			return pesos.at(i);
		}
};

/* ESQUEMA ESTACIONARIO */

// Se seleccionarán únicamente dos padres.

// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos.
// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).

// ESQUEMA DE REEMPLAZAMIENTO: Los dos descendientes generados tras el cruce y la mutación (esta última aplicada según una determinada probabilidad) sustituyen a los dos peores de la población actual, en caso de ser mejores que ellos.

// OPERADOR DE MUTACIÓN: Operador de mutación normal para representación real con sigma=0,3.
class AGE: public AG{
	private:
		// Vector de pesos
		vector <float> pesos;
		
		// Probabilidad de cruce
		const float prob_cruce = 1;
		
	public:
		// Constructor
		AGE( Datos & matriz, const bool blx = true );
		
		// Consultor del número de pesos que hay
		inline unsigned size(){
			return pesos.size();
		}
		
		// Consultor de pesos (W)
		inline vector <float> & getPesos(){
			return pesos;
		}
		
		// Consultor del peso i-ésimo
		inline float getPeso( unsigned i ){
			return pesos.at(i);
		}
		
};


#endif
