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
		
		cout << "Seleccion" << endl;
		
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

		
		cout << "Cruce" << endl;
		
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
		
		cout << "Reemplazamiento" << endl;
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






























/////////////////////////// Constructor
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
		
		if( mejor_padre < num_cruces )
			sobrevive = false;
		
		cout << "Seleccion" << endl;
		
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

		
		cout << "Cruce" << endl;
		
		// OPERADOR DE CRUCE
		for( unsigned j=0; j<num_cruces; j+=2 )
			PMX(hijos.at(j), hijos.at(j+1));
			//hijos.push_back( Posicion(hijos.at(j), hijos.at(j+1)) );

		cout << "Mutacion" << endl;
		// OPERADOR DE MUTACIÓN: Intercambio
		for( unsigned j=0; j<num_mutaciones; j++ ){
			p = Randint( 0, M-1 );
			k = Randint( 0, n-1 );
    
    		while( l==k )
				l = Randint( 0, n-1 );
				
			int valor = hijos.at(p).at(k);
    		hijos.at(p).at(k) = hijos.at(p).at(l);
    		hijos.at(p).at(l) = valor;
    		
			if( p >= num_cruces ){ //?
				valoraciones[p] = calcularFitness( matrices, hijos.at(p) );	
				evaluaciones++;
				
				if( sobrevive && (p == mejor_padre) )
					sobrevive = false;
			}
		}
		
		cout << "Reemplazamiento" << endl;
		// ESQUEMA DE REEMPLAZAMIENTO: La población de hijos sustituye automáticamente a la actual. Para conservar el elitismo, si la mejor solución de la generación anterior no sobrevive, sustituye directamente a la peor solución de la nueva población.
		//cout << valoraciones.size() << endl;		
		for( unsigned j=0; j<num_cruces; j++ ){
			//cout << "	" << hijos.at(j).size() << endl;
			valoraciones[j] = calcularFitness( matrices, hijos.at(j) );
			
			//if( valoraciones.at(peor_hijo) > val1 )	
			//	peor_hijo = j;
			
			evaluaciones++;
		}
		
		//cout << "Sale" << endl;
		
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

