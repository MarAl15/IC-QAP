#ifndef _BUSQUEDA_LOCAL_H
#define _BUSQUEDA_LOCAL_H

#include "datos.h"

using namespace std;

// Usar como probabilidad sin sutistución, valorar la función del fitness sobre el algoritmo optimizado
class BusquedaLocal{
	private:
		// Vector 
		vector <int> solucion;
		
	public:
		// Constructor
		BusquedaLocal( Datos & matrices );
		
		// Consultor del número de pesos que hay
		inline unsigned size(){
			return solucion.size();
		}
		
		// Consultor
		inline vector <int> & getSolucion(){
			return solucion;
		}	
};


#endif
