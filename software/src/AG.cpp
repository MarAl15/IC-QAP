#include "geneticos.h"
#include "funciones.h"
#include "random.h"
#include <iostream>
#include <tgmath.h>
#include <algorithm>    // std::random_shuffle

//DISTRIBUCION NORMAL
#include <random>


using namespace std;

/* OPERADORES DE CRUCE */

// Operador basado en posición
/*vector <int> Posicion( vector <int> & C1, vector <int> & C2 ){
	vector <int> hijo,
				 resto;
	unsigned k = 0;
	 
	for(unsigned i=0; i<C1.size(); i++){
		if(C1.at(i) == C2.at(i))
			hijo[i] = C1.at(i);
		else
			resto.push_back(C1.at(i));
	}
	
	random_shuffle(resto.begin(), resto.end());
	
	for(unsigned i=0; i<C1.size(); i++){
		if(hijo[i] == NULL){
			hijo[i] = resto.at(k);
			k++;
		}
	}
}*/

void PMX(vector <int> & C1, vector <int> & C2){
	unsigned ini = Randint(0,C1.size()-3), //C1.size()/4,
			 fin = Randint(ini+1,C1.size()-1);//ini+C1.size()/2;
			 
	vector <int> correspondencias1, correspondencias2, AuxC1, AuxC2;
	
	/*cout << ini << " " << fin << endl;
	
	for(unsigned i=0; i<C1.size(); i++)
		//cout << C1.at(i) << " ";
	
	//cout << endl;
	
	for(unsigned i=0; i<C2.size(); i++)
		//cout << C2.at(i) << " ";
	
	//cout << endl;*/
	
	////////////////////
	
	// Inicializamos el vector
	for(unsigned i=0; i<C1.size(); i++){
		correspondencias1.push_back(-1);
		correspondencias2.push_back(-1);
	}
	
	// Almacenamos las correspondencias
	for(unsigned i=ini; i<fin; i++){
		correspondencias1[C1.at(i)] = C2.at(i);
		correspondencias2[C2.at(i)] = C1.at(i);
	}
		
	for(unsigned i=0; i<ini; i++){
		int k = C2.at(i);
		while(correspondencias1.at(k) != -1)
			k = correspondencias1.at(k);
		AuxC1.push_back(k);
		
		k = C1.at(i);
		while(correspondencias2.at(k) != -1)
			k = correspondencias2.at(k);
		AuxC2.push_back(k);
	}
	
	for(unsigned i=fin; i<C1.size(); i++){
		int k = C2.at(i);
		while(correspondencias1.at(k) != -1)
			k = correspondencias1.at(k);
		AuxC1.push_back(k);
		
		k = C1.at(i);
		while(correspondencias2.at(k) != -1)
			k = correspondencias2.at(k);	
		AuxC2.push_back(k);
	}
	
	unsigned j = 0;
	
	for(unsigned i=0; i<ini; i++,j++){
		//cout << i << endl;
		C1[i] = AuxC1.at(j);
		C2[i] = AuxC2.at(j);
	}
	
	for(unsigned i=fin; i<C1.size(); i++,j++){
		//cout << i << endl;
		C1[i] = AuxC1.at(j);
		C2[i] = AuxC2.at(j);	
	}
	
	
	///////////////////
	/*for(unsigned i=0; i<C1.size(); i++)
		//cout << C1.at(i) << " ";
	
	//cout << endl;
	
	for(unsigned i=0; i<C2.size(); i++)
		//cout << C2.at(i) << " ";
	
	//cout << endl << endl;*/
}


///////////////////////

/* ESQUEMA GENERACIONAL CON ELITISMO */

// Constructor
AGG::AGG( Datos & matrices ){
	bool sobrevive;
	unsigned evaluaciones = 0,
			 n = matrices.size(), // Número de característica
			 p, k, l, mejor_padre, peor_hijo;
			 
	float num_cruces = 2*roundf( prob_cruce*M/2 ),
		  num_mutaciones = roundf( prob_mutacion*M*n ),
		  mejor, val1, val2;
		  
    //default_random_engine generator (Seed);
	//normal_distribution<float> distribution (0.0,0.3*0.3);
	
	// Generamos TAM cromosomas
	vector <int> aux, w, // solución
				   valoraciones, vals; // evaluaciones de la función objetivo entre num_cruces y TAM
	vector < vector<int> > cromosomas, hijos;
	
	//cout << "1" << endl;
	for( unsigned i=0; i<M; i++ ){
		for( unsigned j=0; j<n; j++ ){
			//w.push_back( Randfloat( 0.0, 1.0 ) );
			w.push_back(j);
		}
		
		random_shuffle(w.begin(), w.end());
			
		cromosomas.push_back( w );
		valoraciones.push_back( calcularFitness( matrices, w ) );
		w.clear();
	}
	
	//cout << "2" << endl;
	
	while( evaluaciones < MAX ){
		sobrevive = true;

		// Buscamos el mejor padre		
		mejor_padre = 0;
			
		for( unsigned j=1; j<M; j++ ){
			if( valoraciones.at(mejor_padre) < valoraciones.at(j) )	
				mejor_padre = j;
		}
			
		mejor = valoraciones.at(mejor_padre);
		
		//if( mejor_padre < num_cruces )
		//	sobrevive = false;
		
		//cout << "Seleccion" << endl;
		
		// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos. 
		// Se aplicarán tantos torneos como individuos existan en la población genética, incluyendo los individuos ganadores en la población de padres.			
		hijos.clear();
		vals.clear();
			
		for( unsigned j=0; j<M; j++ ){
			p = Randint( 0, M-1 ), // M = cromosomas.size()
			k = Randint( 0, M-1 );
						 
			while( p==k )
				k = Randint( 0, M-1 );
			
			val1 = valoraciones.at(k);
			val2 = valoraciones.at(p);
				
			if( val1 < val2 ){
				hijos.push_back( cromosomas.at(p) );
				
				valoraciones[j] = val2;	
				//if( j >= num_cruces )
					//vals.push_back( val2 );
			}else{
				hijos.push_back( cromosomas.at(k) );
					
				valoraciones[j] = val1;
				//if( j >= num_cruces )
					//vals.push_back( val1 );
			}
		}
		
		//for( unsigned j=0; j<vals.size(); j++ )
			//valoraciones[j+num_cruces] = vals.at(j); 

		
		//cout << "Cruce" << endl;
		
		// OPERADOR DE CRUCE
		//for( unsigned j=0; j<num_cruces; j+=2 ){
		for( unsigned j=0; j<num_cruces; j++ ){
			k = Randint( 0, M-1 );
			l = Randint( 0, M-1 );
		
			while( l==k )
				l = Randint( 0, M-1 );
				
			PMX(hijos.at(k), hijos.at(l));
			
			valoraciones[k] = calcularFitness( matrices, hijos.at(k) );	
			valoraciones[l] = calcularFitness( matrices, hijos.at(l) );
			evaluaciones += 2;
				
			if( k == mejor_padre || l == mejor_padre )
				sobrevive = false;
		}
			//hijos.push_back( Posicion(hijos.at(j), hijos.at(j+1)) );

		//cout << "Mutacion" << endl;
		// OPERADOR DE MUTACIÓN: Intercambio
		for( unsigned j=0; j<num_mutaciones; j++ ){
			//p = Randint( 0, M-1 );
			
			//if( p >= num_mutaciones_gen ){ 
				k = Randint( 0, n-1 );
				l = Randint( 0, n-1 );
		
				while( l==k )
					l = Randint( 0, n-1 );
					
				int valor = hijos.at(p).at(k);
				hijos.at(p).at(k) = hijos.at(p).at(l);
				hijos.at(p).at(l) = valor;
    		
			//if( p >= num_cruces ){ //?
				valoraciones[p] = calcularFitness( matrices, hijos.at(p) );	
				evaluaciones++;
				
				//if( sobrevive && (p == mejor_padre) )
				if( p == mejor_padre )
					sobrevive = false;
			//}
		}
		
		//cout << "Reemplazamiento" << endl;
		// ESQUEMA DE REEMPLAZAMIENTO: La población de hijos sustituye automáticamente a la actual. Para conservar el elitismo, si la mejor solución de la generación anterior no sobrevive, sustituye directamente a la peor solución de la nueva población.
		//cout << valoraciones.size() << endl;		
		/*for( unsigned j=0; j<num_cruces; j++ ){
			//cout << "	" << hijos.at(j).size() << endl;
			valoraciones[j] = calcularFitness( matrices, hijos.at(j) );
			
			//if( valoraciones.at(peor_hijo) > val1 )	
			//	peor_hijo = j;
			
			evaluaciones++;
		}*/
		
		//cout << "Sale" << endl;
		
		if( !sobrevive){
			
			// Buscamos el peor hijo 
			peor_hijo = 0;
		
			for( unsigned j=1; j<M; j++ ){			
				if( valoraciones.at(peor_hijo) > valoraciones.at(j) )	
					peor_hijo = j;
			}
		
			if( valoraciones.at(peor_hijo) > mejor ){
				hijos[peor_hijo] = cromosomas.at(mejor_padre);
				valoraciones[peor_hijo] = mejor;
			}
		}
		
		
		// Se sustituye la anterior población por la nueva.
		cromosomas = hijos;		
	}
	/**/
	// Seleccionamos el mejor cromosoma de la población.
	mejor_padre = 0;
	
	for( unsigned j=1; j<M; j++ ){
		if( valoraciones.at(mejor_padre) < valoraciones.at(j) )	
			mejor_padre = j;
	}

	//cout << cromosomas.size() << endl;
	solucion = cromosomas.at( mejor_padre );/**/	
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ESQUEMA ESTACIONARIO */

unsigned AGE::torneo( vector <int> & valoraciones, unsigned tope=5 ){
	vector <unsigned> participantes;
	unsigned mejor = Randint( 0, M-1 ); // M = cromosomas.size()
	participantes.push_back(mejor);
	
	for( unsigned j=0; j<tope; j++ ){
		unsigned k = Randint( 0, M-1 );
		
		while( find(participantes.begin(), participantes.end(), k)!=participantes.end() )
			k = Randint( 0, M-1 );
		participantes.push_back(k);
		
		if( valoraciones.at(k) < valoraciones.at(mejor) )
			mejor = k;
	}
	
	return mejor;
}

// Constructor
/*AGE::AGE( Datos & matrices ){
	bool reemplazado1 = false,
		 reemplazado2 = false;
	unsigned evaluaciones = 0,
			 n = matrices.size(), // Número de característica
			 p, k, m, l, peor1, peor2;
		
	float num_mutaciones = roundf( prob_mutacion*M*n ), 
		  num = M, mut = num_mutaciones,
		  mejor, val1, val2;
	
    //default_random_engine generator (Seed);
	//normal_distribution<float> distribution (0.0,0.3*0.3);
	
	
	// Generamos TAM cromosomas
	vector <int> aux, w, // vector de permutaciones
				   valoraciones; // evaluaciones de la función objetivo entre num_cruces y TAM
	vector < vector <int> > cromosomas, hijos;
	

	for( unsigned i=0; i<M; i++ ){
		for( unsigned j=0; j<n; j++ ){
			w.push_back(j);
		}
		
		random_shuffle(w.begin(), w.end());
			
		cromosomas.push_back( w );
		valoraciones.push_back( calcularFitness( matrices, w ) );
		w.clear();
	}
			
			
	while( evaluaciones < MAX ){
		//cout << "Seleccion" << endl;
		
		// OPERADOR DE SELECCIÓN: Se usará el torneo n-ario, consistente en elegir aleatoriamente n individuos de la población y seleccionar el mejor de ellos. // 
		// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).
		hijos.clear();
		
		p = torneo(valoraciones);
		hijos.push_back( cromosomas.at(p) );
		
		k = torneo(valoraciones);
		while( p==k )
				k = torneo(valoraciones);
		hijos.push_back( cromosomas.at(k) );
		
		cout << p << " " << k << endl;
*/		
		/*for( unsigned j=0; j<tope; j++ ){
			p = Randint( 0, M-1 ), // M = cromosomas.size()
			k = Randint( 0, M-1 );
			
			while( p==k )
				k = Randint( 0, M-1 );
				
			if( valoraciones.at(k) < valoraciones.at(p) ){
				hijos.push_back( cromosomas.at(p) );
			}else{
				hijos.push_back( cromosomas.at(k) );			
			}
		}*/		

/*		//cout << "Cruce" << endl;
		// OPERADOR DE CRUCE -> Se cruza siempre
		PMX(hijos.at(0), hijos.at(1));

		
		//cout << "Mutacion" << endl;
		// OPERADOR DE MUTACIÓN
		for(unsigned p=0; p<hijos.size(); p++){
			float prob = Randfloat(0,1);
			//if( mut > 0 ){
			if(prob <= prob_mutacion){
				for(unsigned i=0; i<n; i++){
					prob = Randfloat(0,1);
					if(prob <= prob_mutacion_gen ){
						//p = Randint( 0, 1 );
						k = Randint( 0, n-1 );
				
						while( k==i )
							k = Randint( 0, n-1 );
							
						int valor = hijos.at(p).at(i);
						hijos.at(p).at(i) = hijos.at(p).at(k);
						hijos.at(p).at(k) = valor;
					}
				}
				//mut--;
			}
		}
		//else
		//	mut = num_mutaciones;
		
		//cout << "Reemplazamiento" << endl;
		// ESQUEMA DE REEMPLAZAMIENTO: Los dos descendientes generados tras el cruce y la mutación (esta última aplicada según una determinada probabilidad) sustituyen a los dos peores de la población actual, en caso de ser mejores que ellos.
		// Buscamos los dos peores padres
		if( valoraciones.at(0) > valoraciones.at(1) ){
			peor1 = 0;
			peor2 = 1;
		}
		else{
			peor1 = 1;
			peor2 = 0;
		}	
		
		for( unsigned j=2; j<M; j++ ){
			if( valoraciones.at(peor1) > valoraciones.at(j) )	// Comparamos primero con el peor de los peores hasta el momento
				peor1 = j;
			else if( valoraciones.at(peor2) > valoraciones.at(j) )
				peor2 = j;
		}

		val1 = calcularFitness( matrices, hijos.at(0) );
		val2 = calcularFitness( matrices, hijos.at(1) );
		evaluaciones+=2;
		
		reemplazado1 = reemplazado2 = false;
		
		// Comparamos con el mejor
		if( val2 < valoraciones.at(peor2) ){
			cromosomas[peor2] = hijos.at(1);
			valoraciones[peor2] = val2;
			
			reemplazado1 = true;
		}
		else if( val1 < valoraciones.at(peor2) ){
			cromosomas[peor2] = hijos.at(0);
			valoraciones[peor2] = val1;
			
			reemplazado2 = true;
		}
		
		// Comparamos con el peor si no ha sido mejor que el peor de los padres
		if( !reemplazado1 && (val2 < valoraciones.at(peor1)) ){
			cromosomas[peor1] = hijos.at(1);
			valoraciones[peor1] = val2;
		}
		else if( !reemplazado2 && (val1 < valoraciones.at(peor1)) ){
			cromosomas[peor1] = hijos.at(0);
			valoraciones[peor1] = val1;
		}
	}
	
	m = 0;
			
	for( unsigned j=1; j<M; j++ ){
		if( valoraciones.at(m) < valoraciones.at(j) )	
			m = j;
	}
			
	solucion = cromosomas.at( m );
	
}*/

// Constructor
AGE::AGE( Datos & matrices ){
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
			unsigned p = torneo(valoraciones);
			hijos.push_back( cromosomas.at(p) );
			
			unsigned k = torneo(valoraciones);
			while( p==k )
					k = torneo(valoraciones);
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
		
		
		//cout << "Generacion " << POB+1 << endl; 
		//calcularFitness( matrices, cromosomas.at(mejor_padre), true );
		//cout << endl;
	}
		
	calcularFitness( matrices, cromosomas.at(mejor_padre), true );
	cout << endl;
			
	solucion = cromosomas.at(mejor_padre);
}




