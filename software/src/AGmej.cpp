#include "AGmej.h"
#include "funciones.h"
#include "random.h"
#include <iostream>
#include <tgmath.h>
#include <algorithm>    // std::random_shuffle

//DISTRIBUCION NORMAL
//#include <random>

using namespace std;

AGmej::AGmej( Datos & matrices ){
	unsigned n = matrices.size(), // Número de característica
			mejor_padre, peor_hijo, mejor_hijo;
	
	
    //default_random_engine generator (Seed);
	//normal_distribution<float> distribution (0.0,0.3*0.3);
	
	
	// Generamos TAM cromosomas
	vector <int> aux, w, // vector de permutaciones
				   valoraciones, vals; // evaluaciones de la función objetivo entre num_cruces y TAM
	vector < vector <int> > cromosomas, hijos;
	

	mejor_padre = 0;
	for( unsigned i=0; i<M; i++ ){
		for( unsigned j=0; j<n; j++ ){
			w.push_back(j);
		}
		
		random_shuffle(w.begin(), w.end());
			
		int val = calcularFitness( matrices, w );
		if( i!=0 && (valoraciones.at(mejor_padre)>val) )
			mejor_padre = i;
		
		cromosomas.push_back( w );	
		valoraciones.push_back( val );
		
		
		w.clear();
	}
	
	for(unsigned POB = 0; POB < NUM_POBLACIONES; POB++){
		mejor_hijo = peor_hijo = 0;
		hijos.clear();
		vals.clear();
		
		for(unsigned j=0; j < M; j+=2)	{			
			// OPERADOR DE SELECCIÓN: Se usará el torneo n-ario, consistente en elegir aleatoriamente n individuos de la población y seleccionar el mejor de ellos. 
			// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).			
			unsigned p = torneo(valoraciones, M);
			hijos.push_back( cromosomas.at(p) );
			
			unsigned k = torneo(valoraciones, M);
			while( p==k )
					k = torneo(valoraciones, M);
			hijos.push_back( cromosomas.at(k) );
			
			
			// OPERADOR DE CRUCE -> Se cruza siempre
			PMX(hijos.at(j), hijos.at(j+1));

			
			// OPERADOR DE MUTACIÓN
			for(unsigned p=j; p<=j+1; p++){
				float prob = Randfloat(0,1);
				if(prob <= prob_mutacion){
					for(unsigned i=0; i<n; i++){
						prob = Randfloat(0,1);
						if(prob <= prob_mutacion_gen ){
							k = Randint( 0, n-1 );
					
							while( k==i )
								k = Randint( 0, n-1 );

							int valor = hijos.at(p).at(i);
							hijos.at(p).at(i) = hijos.at(p).at(k);
							hijos.at(p).at(k) = valor;
						}
					}
				}
			}
			int val1 = calcularFitness(matrices, hijos.at(j));
			int val2 = calcularFitness(matrices, hijos.at(j+1) ); 
			
			vals.push_back( val1 );
			vals.push_back( val2 );
			
			if( j!=0 && vals.at(mejor_hijo)>val1 )
				mejor_hijo = j;
			else if( j!=0 && vals.at(peor_hijo)<val1 )
				peor_hijo = j;
				
			if( vals.at(mejor_hijo)>val2 )
				mejor_hijo = j+1;
			else if( vals.at(peor_hijo)<val2 )
				peor_hijo = j+1;
		}
		
		// Reemplazamos el peor hijo por el mejor padre si tiene mejor fitness
		if( valoraciones.at(mejor_padre)<vals.at(peor_hijo) ){
			hijos[peor_hijo] = cromosomas.at(mejor_padre);
			vals[peor_hijo] = valoraciones.at(mejor_padre);
			
			// Verificamos si el mejor hijo gana al padre
			if( valoraciones.at(mejor_padre)>valoraciones.at(mejor_hijo) )
				mejor_padre = mejor_hijo;
			else
				mejor_padre = peor_hijo;
		}
		
		
		cromosomas = hijos;
		valoraciones = vals;
		
		
		/*cout << "Generacion " << POB+1 << endl; 
		calcularFitness( matrices, cromosomas.at(mejor_padre), true );
		cout << endl;*/
	}
		
	calcularFitness( matrices, cromosomas.at(mejor_padre), true );
	cout << endl;
			
	solucion = cromosomas.at(mejor_padre);
}



