#include "AGE-BL.h"
#include "busquedaLocal.h"
#include "random.h"
#include <iostream>
#include <tgmath.h>
#include <algorithm>    // std::random_shuffle

using namespace std;

AGEBL::AGEBL( Datos & matrices, int seleccion, int mejora ){
	unsigned n = matrices.size(), // Número de característica
			mejor_padre, peor_hijo, mejor_hijo;
	BusquedaLocal bl;	
	
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
	
	for(unsigned epoca = 0; epoca < EPOCAS; epoca++){
		mejor_hijo = peor_hijo = 0;
		hijos.clear();
		vals.clear();
		
		for(unsigned j=0; j < M; j+=2)	{			
			// OPERADOR DE SELECCIÓN
			if(seleccion==TORNEO){
				// Se usará el torneo n-ario, consistente en elegir aleatoriamente n individuos de la población y seleccionar el mejor de ellos. Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).			
				unsigned p = torneo(valoraciones, M);
				hijos.push_back( cromosomas.at(p) );
				
				unsigned k = torneo(valoraciones, M);
				while( p==k )
						k = torneo(valoraciones, M);
				hijos.push_back( cromosomas.at(k) );
			}
			else if(seleccion==RULETA){
				int suma = sum(valoraciones),
					aux = valoraciones.at(0);
				int r = Randint( 0, suma );
				unsigned p=0,
						 k;
				
				while(aux<r){
					p++;
					aux += valoraciones.at(p);
				}
				hijos.push_back( cromosomas.at(p) );
				
				do{
					r = Randint( 0, suma );
					k = 0;
					aux = valoraciones.at(0);
					
					while(aux<r){
						k++;
						aux += valoraciones.at(k);
					}
				}while( p==k );
				hijos.push_back( cromosomas.at(k) );
			}else{
				// Se eligen dos padres aleatoriamente
				unsigned p = Randint( 0, M-1 );
				hijos.push_back( cromosomas.at(p) );
				
				unsigned k = Randint( 0, M-1 );
				while( p==k )
						k = Randint( 0, M-1 );
				hijos.push_back( cromosomas.at(k) );
			}
			
			
			// OPERADOR DE CRUCE -> Se cruza siempre
			PMX(hijos.at(j), hijos.at(j+1));

			
			// OPERADOR DE MUTACIÓN
			for(unsigned p=j; p<=j+1; p++){
				float prob = Randfloat(0,1);
				if(prob <= prob_mutacion){
					for(unsigned i=0; i<n; i++){
						prob = Randfloat(0,1);
						if(prob <= prob_mutacion_gen ){
							unsigned k;		
							do{
								k = Randint( 0, n-1 );
							} while( k==i );

							int valor = hijos.at(p).at(i);
							hijos.at(p).at(i) = hijos.at(p).at(k);
							hijos.at(p).at(k) = valor;
						}
					}
				}
			}
			
			int val1 = calcularFitness(matrices, hijos.at(j));
			int val2 = calcularFitness(matrices, hijos.at(j+1) ); 
			
			val1 = bl.BL(matrices, hijos.at(j), val1, mejora );
			val2 = bl.BL(matrices, hijos.at(j+1), val2, mejora );
			
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
			if( valoraciones.at(mejor_padre)>vals.at(mejor_hijo) )
				mejor_padre = mejor_hijo;
			else
				mejor_padre = peor_hijo;
		}
		
		cromosomas = hijos;
		valoraciones = vals;
		
		if(mejora== BALDWIDIANA && epoca == (EPOCAS-1)){
			bl.BL(matrices, cromosomas.at(mejor_padre), calcularFitness( matrices, cromosomas.at(mejor_padre)), LAMARCKIANA );
		}	
		
		cout << "Generacion " << epoca+1 << endl;
		if(mejora!=BALDWIDIANA){
			/*cout << "	Solucion: "; 
			for(unsigned i=0; i<n; i++)
				cout << cromosomas.at(mejor_padre).at(i) << " ";
			cout << endl;*/
			cout << "	Fitness: " << valoraciones.at(mejor_padre) << endl;
		}else{
			cout << "	Fitness: " << calcularFitness( matrices, cromosomas.at(mejor_padre) ) << endl;
			cout << "	Fitness BL: " << valoraciones.at(mejor_padre) << endl;
		}
		cout << endl;
	}
		
	calcularFitness( matrices, cromosomas.at(mejor_padre), true );
	cout << endl;
			
	solucion = cromosomas.at(mejor_padre);
}




