#ifndef _INDIVIDUO_H
#define _INDIVIDUO_H

#include "datos.h"

using namespace std;


class Individuo{
	private:
		// Solución asociada al individuo
		int *solucion;
		
		// Número de genes del individuo
		int m;
		
		// Fitness asociado
		int fitness;
	public:		
		// Constructor por defecto
		Individuo();
		
		// Constructor por parámetros
		// 	@param Número de genes del individuo
		Individuo( const unsigned int num );
		
		// Calcula el fitness de la solución
		void calcularFitness( Datos & matrices );
		
		// Consultor del fitness del individuo
		inline int getFitness(){
			return fitness;
		}
		
		// Consultor del tamaño del individuo
		inline int size(){
			return m;
		}
		
		// Consultor de la solución asociada al individuo
		inline int* getSolucion(){
			return solucion;
		}
};


#endif
