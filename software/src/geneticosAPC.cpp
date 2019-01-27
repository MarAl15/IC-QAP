#include "geneticos.h"
#include "funciones.h"
#include "random.h"
#include <iostream>
#include <tgmath.h>

//DISTRIBUCION NORMAL
#include <random>


using namespace std;

/* OPERADORES DE CRUCE */

// Operador BLX-alpha (alpha=0,3)
void BLX( vector <float> & C1, vector <float> & C2 ){
	// Hallamos el maximo y el mínimo elemento de los cromosomas.
	float max = C1.at(0), // max = max{c_1i, c_2i}
		  min = C1.at(0), // min = min{c_1i, c_2i}
		  I, a, b, alpha = 0.3;
	
	
	for( unsigned i=0; i<C1.size(); i++ ){
		if( max < C1.at(i) )
			max = C1.at(i);
		
		else if( min > C1.at(i) )
			min = C1.at(i);
	}
	
	for( unsigned i=0; i<C2.size(); i++ ){
		if( max < C2.at(i) )
			max = C2.at(i);
		
		else if( min > C2.at(i) )
			min = C2.at(i);
	}
	
	I = max-min;
	
	// Generamos dos descendientes H_k=(h_k1,.., h_kn), k=1,2, donde h_ki se genera aleatoriamente en el intervalor [min-I·alpha, max+I·alpha]
	a = min-I*alpha;
	b = max+I*alpha; 
	
	for( unsigned i=0; i<C1.size(); i++ ){
		C1[i] = Randfloat(a, b);
		C2[i] = Randfloat(a, b);
		
		// Truncamos
		if( C1[i] > 1 )
			C1[i] = 1;
		else if( C1[i] < 0 )
			C1[i] = 0;
			
		if( C2[i] > 1 )
			C2[i] = 1;
		else if( C2[i] < 0 )
			C2[i] = 0;	
	}
}


///////////////////////

/* ESQUEMA GENERACIONAL CON ELITISMO */

// Constructor
AGG::AGG( Datos & matriz, const bool blx ){
	bool sobrevive;
	unsigned evaluaciones = 0,
			 n = matriz.sizeEjemplo(0), // Número de característica
			 p, k, mejor_padre, peor_hijo;
			 
	float num_cruces = 2*roundf( prob_cruce*M/2 ),
		  num_mutaciones = roundf( prob_mutacion*M*n ),
		  mejor, val1, val2;
		  
    default_random_engine generator (Seed);
	normal_distribution<float> distribution (0.0,0.3*0.3);
	
	// Generamos TAM cromosomas
	vector <float> aux, w, // pesos
				   valoraciones, vals; // evaluaciones de la función objetivo entre num_cruces y TAM
	vector < vector <float> > cromosomas, hijos;
	
	
	for( unsigned i=0; i<M; i++ ){
		for( unsigned j=0; j<n; j++ )
			w.push_back( Randfloat( 0.0, 1.0 ) );
			
		cromosomas.push_back( w );
		valoraciones.push_back( funcionObjetivo( matriz, w ) );
		w.clear();
	}
	
	
	while( evaluaciones < MAX ){
		sobrevive = true;

		// Buscamos el mejor padre		
		mejor_padre = 0;
			
		for( unsigned j=1; j<M; j++ ){
			if( valoraciones.at(mejor_padre) < valoraciones.at(j) )	
				mejor_padre = j;
		}
			
		mejor = valoraciones.at(mejor_padre);
		
		if( mejor_padre < num_cruces )
			sobrevive = false;
		
		
		// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos. // Se aplicarán tantos torneos como individuos existan en la población genética, incluyendo los individuos ganadores en la población de padres.			
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
					
				if( j >= num_cruces )
					vals.push_back( val2 );
			}else{
				hijos.push_back( cromosomas.at(k) );
					
				if( j >= num_cruces )
					vals.push_back( val1 );
			}
		}
		
		for( unsigned j=0; j<vals.size(); j++ )
			valoraciones[j+num_cruces] = vals.at(j); 

		

		// OPERADOR DE CRUCE
		if( blx ){ // BLX-alpha
			for( unsigned j=0; j<num_cruces; j+=2 )
				BLX( hijos.at(j), hijos.at(j+1) );
		}else{ // CA
			aux = hijos.at(0);
			for( unsigned j=0; j<num_cruces-1; j++ ){			
				for( unsigned i=0; i<aux.size(); i++ )
					hijos.at(j).at(i) = (hijos.at(j).at(i)+hijos.at(j+1).at(i))/2.0;
			}
			
			for( unsigned i=0; i<aux.size(); i++ )
				hijos.at(num_cruces-1).at(i) = (hijos.at(num_cruces-1).at(i)+aux.at(i))/2.0;
		}
		
		
		// OPERADOR DE MUTACIÓN: Operador de mutación normal para representación real con sigma=0,3.
		for( unsigned j=0; j<num_mutaciones; j++ ){
			p = Randint( 0, M-1 );
			k = Randint( 0, n-1 );
    
    		hijos.at(p).at(k) += distribution(generator);
    		
    		//Truncamos
            if( hijos.at(p).at(k) > 1)
                hijos.at(p).at(k) = 1;
            else if( hijos.at(p).at(k) < 0)
                hijos.at(p).at(k) = 0;
			
			if( p >= num_cruces ){
				valoraciones[p] = funcionObjetivo( matriz, hijos.at(p) );	
				evaluaciones++;
				
				if( sobrevive && (p == mejor_padre) )
					sobrevive = false;
			}
		}
		
		// ESQUEMA DE REEMPLAZAMIENTO: La población de hijos sustituye automáticamente a la actual. Para conservar el elitismo, si la mejor solución de la generación anterior no sobrevive, sustituye directamente a la peor solución de la nueva población.		
		for( unsigned j=0; j<num_cruces; j++ ){
			valoraciones[j] = funcionObjetivo( matriz, hijos.at(j) );
			
			//if( valoraciones.at(peor_hijo) > val1 )	
			//	peor_hijo = j;
			
			evaluaciones++;
		}
		
		if( !sobrevive){
			// Buscamos el peor hijo 
			peor_hijo = 0;
		
			for( unsigned j=1; j<M; j++ ){			
				if( valoraciones.at(peor_hijo) > valoraciones.at(j) )	
					peor_hijo = j;
			}
		
			//if( valoraciones.at(peor_hijo) < mejor ){
			hijos[peor_hijo] = cromosomas[mejor_padre];
			
			valoraciones[peor_hijo] = mejor;
		}
		
		
		// Se sustituye la anterior población por la nueva.
		cromosomas = hijos;		
	}
	
	// Seleccionamos el mejor cromosoma de la población.
	mejor_padre = 0;
	
	for( unsigned j=1; j<M; j++ ){
		if( valoraciones.at(mejor_padre) < valoraciones.at(j) )	
			mejor_padre = j;
	}

	pesos = cromosomas.at( mejor_padre );	
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ESQUEMA ESTACIONARIO */

// Constructor
AGE::AGE( Datos & matriz, const bool blx ){
	bool reemplazado1 = false,
		 reemplazado2 = false;
	unsigned evaluaciones = 0,
			 n = matriz.sizeEjemplo(0), // Número de característica
			 p, k, m, peor1, peor2, tope = 2;
	
	if( !blx )
		tope = 3; // creamos un hijo más para poder cruzarlo
		
	float num_mutaciones = roundf( prob_mutacion*M*n ), 
		  num = M, mut = num_mutaciones,
		  mejor, val1, val2;
	
    default_random_engine generator (Seed);
	normal_distribution<float> distribution (0.0,0.3*0.3);
	
	
	// Generamos TAM cromosomas
	vector <float> aux, w, // pesos
				   valoraciones; // evaluaciones de la función objetivo entre num_cruces y TAM
	vector < vector <float> > cromosomas, hijos;
	

	for( unsigned i=0; i<M; i++ ){
		for( unsigned j=0; j<n; j++ )
			w.push_back( Randfloat( 0.0, 1.0 ) );
			
		cromosomas.push_back( w );
		w.clear();
	}
	
	for( unsigned j=0; j<M; j++ ){
		valoraciones.push_back( funcionObjetivo( matriz, cromosomas.at(j) ) );
		
		evaluaciones++;
	}
			
			
	while( evaluaciones < MAX ){
		// OPERADOR DE SELECCIÓN: Se usará el torneo binario, consistente en elegir aleatoriamente dos individuos de la población y seleccionar el mejor de ellos. // 
// Se aplicará dos veces el torneo para elegir los dos padres que serán posteriormente recombinados (cruzados).
		hijos.clear();
		
		for( unsigned j=0; j<tope; j++ ){
			p = Randint( 0, M-1 ), // M = cromosomas.size()
			k = Randint( 0, M-1 );
			
			while( p==k )
				k = Randint( 0, M-1 );
				
			if( valoraciones.at(k) < valoraciones.at(p) ){
				hijos.push_back( cromosomas.at(p) );
			}else{
				hijos.push_back( cromosomas.at(k) );			
			}
		}		

		// OPERADOR DE CRUCE -> Se cruza siempre
		if( blx ){
			BLX( hijos.at(0), hijos.at(1) );
		}else{ 
			for( unsigned i=0; i<n; i++ )
				hijos.at(0).at(i) = (hijos.at(0).at(i)+hijos.at(1).at(i))/2.0;
					
			for( unsigned i=0; i<n; i++ )
				hijos.at(1).at(i) = (hijos.at(1).at(i)+hijos.at(2).at(i))/2.0;
		}

		
		
		// OPERADOR DE MUTACIÓN: Operador de mutación normal para representación real con sigma=0,3.
		if( mut > 0 ){
			p = Randint( 0, 1 );
			k = Randint( 0, n-1 );
    
    		hijos.at(p).at(k) += distribution(generator);
    		
    		//Truncamos
            if( hijos.at(p).at(k) > 1)
                hijos.at(p).at(k)=1;
            else if( hijos.at(p).at(k) < 0)
                hijos.at(p).at(k) =0;
			
			mut--;
		}
		else
			mut = num_mutaciones;
		
		// ESQUEMA DE REEMPLAZAMIENTO: Los dos descendientes generados tras el cruce y la mutación (esta última aplicada según una determinada probabilidad) sustituyen a los dos peores de la población actual, en caso de ser mejores que ellos.
		// Buscamos los dos peores padres
		if( valoraciones.at(0) < valoraciones.at(1) ){
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

		val1 = funcionObjetivo( matriz, hijos.at(0) );
		val2 = funcionObjetivo( matriz, hijos.at(1) );
		
		evaluaciones+=2;
		

		// Comparamos con el mejor de los peores
		if( val2 > valoraciones.at(peor2) ){
			cromosomas[peor2] = hijos.at(1);
			valoraciones[peor2] = val2;
			
			reemplazado1 = true;
		}
		else if( val2 > valoraciones.at(peor1) ){
			cromosomas[peor1] = hijos.at(1);
			valoraciones[peor1] = val2;
			
			reemplazado2 = true;
		}
		
		// Comparamos con el peor si no ha sido mejor que el peor de los padres
		if( !reemplazado1 && (val2 > valoraciones.at(peor2)) ){
			cromosomas[peor2] = hijos.at(0);
			valoraciones[peor2] = val1;
		}
		else if( !reemplazado2 && (val2 > valoraciones.at(peor1)) ){
			cromosomas[peor1] = hijos.at(0);
			valoraciones[peor1] = val1;
		}
		
		reemplazado1 = reemplazado2 = false;
	}
	
	m = 0;
			
	for( unsigned j=1; j<M; j++ ){
		if( valoraciones.at(m) < valoraciones.at(j) )	
			m = j;
	}
			
	pesos = cromosomas.at( m );
	
}





