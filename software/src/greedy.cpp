#include "greedy.h"
#include <math.h>
#include <limits>
#include <iostream>

using namespace std;


// Constructor
Greedy::Greedy( Datos & matriz ){
	vector<unsigned> cercano;
	float max;
	
	// Se inicializan la solución a cero
	//for( unsigned i=0; i<matriz.size(); i++ )
	for( unsigned i=0; i<matrices.size(); i++ )
		solucion.push_back(0);
		

	// Para cada ejemplo del conjunto de entrenamiento, se identifica el enemigo y amigo más cercano. W se actualiza sumándole la distancia existente entre el ejemplo y su enemigo más cercano (considerando todas las características, suma componente a componente). Después, W se actualiza restándole la distancia existente entre el ejemplo y su amigo más cercano.
	for( unsigned i=0; i<matriz.size(); i++ ){
		cercano = identificarCercanos( matriz, i );
		
		for( unsigned j=0; j<pesos.size(); j++ ){
			pesos[j] += abs( matriz.get( cercano[1], j ) - matriz.get( i, j ) )
					- abs( matriz.get( cercano[0], j ) - matriz.get( i, j ) );
		}
	}

	// Una vez hecho lo anterior para todos los ejemplos, W puede tener componentes negativas o que no estén en [0,1]. Los valores negativos de W se truncarán a cero. El resto de valores se normalizarán dividiéndolo por el valor máximo encontrado en W.
	
	// 1) Hallamos el máximo
	max = pesos.at(0);
	
	for( unsigned i=1; i<pesos.size(); i++ ){
		if( max < pesos.at(i) )
			max = pesos.at(i);
	}

	// 2) Truncamos los valores negativos y normalizamos el resto
	for( unsigned i=0; i<pesos.size(); i++ ){
		if( pesos.at(i) <= 0 )
			pesos[i] = 0;
		else
			pesos[i] = pesos.at(i)/max;
	}

}

// Función que calcula la distancia entre dos ejemplos
float Greedy::calcularDistancia( Instancia ejemplo1, Instancia ejemplo2 ){
	float suma = 0;
	
	for( unsigned i=0; i<ejemplo1.size(); i++ )
		suma += pow( ejemplo1.get(i)-ejemplo2.get(i),2 );
	
	return sqrt(suma);
}

// Índice del amigo y el enemigo más cercano al ejemplo j-ésimo
vector <unsigned> Greedy::identificarCercanos( Datos & datos, const unsigned j ){	
	vector <unsigned> cercano = {j, j};
	float dist;

	vector <float> dist_cercano = { numeric_limits<float>::max(), numeric_limits<float>::max() }; // cercano[0] = dist_amigo, cercano[1] = dist_enemigo
		
	for( unsigned i=0; i<datos.size(); i++ ){
		if( j!=i ){
			dist = calcularDistancia( datos.getEjemplo(i), datos.getEjemplo(j) );
			if( datos.getClase(i) == datos.getClase(j) ){
				if( dist < dist_cercano[0] ){
					dist_cercano[0] = dist;
					cercano[0] = i;
				}
			}
			else{
				if( dist < dist_cercano[1] ){
					dist_cercano[1] = dist;
					cercano[1] = i;
				}
			}
		}
	}
	
	return cercano;
}



