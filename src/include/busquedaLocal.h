#ifndef _BUSQUEDA_LOCAL_H
#define _BUSQUEDA_LOCAL_H

#include "datos.h"
#include "funciones.h"

using namespace std;

// Usar como probabilidad sin sutistución, valorar la función del fitness sobre el algoritmo optimizado
class BusquedaLocal{
	private:
		// Vector 
		vector <int> solucion;
		
	public:
		// Constructores
		BusquedaLocal();
		BusquedaLocal( Datos & matrices );
		
		int BL( Datos & matrices, vector <int> & sol, int fitness, int mejora=BALDWIDIANA );
		
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
