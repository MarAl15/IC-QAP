#include "datos.h"
#include "random.h"
#include <fstream>
#include <iostream>

using namespace std;

Datos::Datos(){}

Datos::Datos( const string & file ){  
	leerFichero( file );
	
	/*cout << n << endl << endl;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	
	cout << endl;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}*/
}

// Se leen los datos de un fichero y se separan
void Datos::leerFichero( const string & file ){
	string chain, aux;
	unsigned j=0; // Columnas
	
	ifstream fe(file);
	
	// Tamaño del problema
	getline(fe, chain);
	n = stoi(chain);
	
	// Reservamos memoria para ambas matrices
	A = new int *[n];
	B = new int *[n];
	
	for(unsigned i=0; i<n; i++){
		A[i] = new int[n];
		B[i] = new int[n];
	}
	
	// Ignoramos la siguiente línea ya que está vacía
	getline(fe, chain);
	
	// Leemos la matriz de flujos			 
	for(unsigned i=0; i<n; i++){
		getline(fe, chain);
		
		for(unsigned k=0; k<chain.size(); k++){
			//cout << chain.at(k);
			if(chain.at(k) == ' ' && !aux.empty()){
				A[i][j] = stoi(aux);
		        
		        j++;
				aux.clear();
			}
			else if(chain.at(k) != ' ')	        
		        aux.push_back(chain.at(k));
		}
		
		A[i][j] = stoi(aux);
		j = 0;
		aux.clear();
	}
	
	// Ignoramos la siguiente línea ya que está vacía
	getline(fe, chain);
	
	// Leemos la matriz de distancias			 
	for(unsigned i=0; i<n; i++){
		getline(fe, chain);
		
		for(unsigned k=0; k<chain.size(); k++){
			//cout << chain.at(k);
			if(chain.at(k) == ' ' && !aux.empty()){
				B[i][j] = stoi(aux);
		        
		        j++;
				aux.clear();
			}
			else if(chain.at(k) != ' ')	        
		        aux.push_back(chain.at(k));
		}
		
		B[i][j] = stoi(aux);
		j = 0;
		aux.clear();
	}
}

