#ifndef _DATOS_H
#define _DATOS_H

#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;


class Datos{
	private:
		// Tamaño del problema
		unsigned n;
		
		// Matriz de flujos
		int **A;
		
		// Matriz de distancias
		int **B;
	public:		
		// Constructor por defecto
		Datos();
		
		// Constructor: Se leen los datos de un fichero y se separan
		Datos( const string & file );
		
		void leerFichero( const string & file );
		
		// Consultor del tamaño del problema
		inline unsigned size(){
			return n;
		}
		
		// Consultor de la matriz de flujos
		inline int** getFlujos(){
			return A;
		}
		
		// Elemento de la matriz de flujos
		inline int getFlujo(unsigned i, unsigned j){
			return A[i][j];
		}
		
		
		
		// Consultor de la matriz de distancias
		inline int** getDistancias(){
			return B;
		}
		
		// Elemento de la matriz de distancias
		inline int getDistancia(unsigned i, unsigned j){
			return B[i][j];
		}
};


#endif
