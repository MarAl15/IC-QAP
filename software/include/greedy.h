#ifndef _GREEDY_H
#define _GREEDY_H

#include "datos.h"

using namespace std;


class Greedy{
	private:
		// Vector de pesos
		vector <int> solucion;
		
	public:
		// Constructor
		Greedy( Datos & matrices );
		
		// Consultor del número de pesos que hay
		inline unsigned size(){
			return solucion.size();
		}
		
		// Consultor de la solución
		inline vector <int> & getSolucion(){
			return pesos;
		}
		
		// Función que calcula la distancia entre dos instancias
		float calcularDistancia( Instancia ejemplo1, Instancia ejemplo2 );
		
		// Distancia del amigo y el enemigo más cercano al ejemplo j-ésimo
		vector <unsigned> identificarCercanos( Datos & datos, const unsigned j );
		
};


#endif
