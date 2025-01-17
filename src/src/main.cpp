#include "datos.h"
#include "AGE.h"
#include "busquedaLocal.h"
#include "AGE-BL.h"

#include "random.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	Datos matrices("./datos/tai256c.dat");
	clock_t start_time;
	
	/*cout << "  -> Resultados AGE: " << endl;
	start_time = clock();
	AGE ag( matrices );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;*/
	
	/*cout << endl;
	cout << "  -> Resultados AGE-BALDWIDIANA-TORNEO: " << endl;
	start_time = clock();
	AGE agb( matrices, TORNEO, BALDWIDIANA );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;*/
	
	/*cout << endl;
	cout << "  -> Resultados AGE-LAMARCKIANA-TORNEO: " << endl;
	start_time = clock();
	AGE agl( matrices, TORNEO, LAMARCKIANA );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;*/
	
	
	cout << "  -> Resultados AGE-LAMARCKIANA-TORNEO: " << endl;
	start_time = clock();
	AGEBL agl( matrices, TORNEO, LAMARCKIANA );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
	
	/**/
	
	/*cout << "  -> Resultados AGEBL-BALDWIDIANA-TORNEO: " << endl;
	start_time = clock();
	AGEBL agl( matrices, TORNEO, BALDWIDIANA );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;*/
	
	
	/*cout << "  -> Resultados búsqueda local: " << endl;
	start_time = clock();
	BusquedaLocal BL( matrices );
	cout << "  --> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;*/
	
	
	/*	
	if(argc < 3){
		cout << "./BIN/practica1 <algoritmo> <base de datos> (<iteraciones> (<semilla_iteracion_primera>) )" << endl;
		cout << endl;
		cout << "<algoritmo>:" << endl;
		cout << "  1: Todos" << endl;
		cout << "  2: 1-NN" << endl;
		cout << "  3: Greedy" << endl;
		cout << "  4: Búsqueda local" << endl;
		cout << "  5: AGG-BLX" << endl;
		cout << "  6: AGG-CA" << endl;
		cout << "  7: AGE-BLX" << endl;
		cout << "  8: AGE-CA" << endl;
		cout << "  9: AM-(10,1.0)" << endl;
		cout << "  10: AM-(10,0.1)" << endl;
		cout << "  11: AM-(10,0.1mej)" << endl;
		cout << "  12: ES" << endl;
		cout << "  13: ILS" << endl;
		cout << "  14: DE-rand" << endl;
		cout << "  15: DE-current-to-best" << endl;
		cout << endl;
		cout << "<base de datos>" << endl;
		cout << "  1: Spambase-460" << endl;
		cout << "  2: Sonar" << endl;
		cout << "  3: WBDC" << endl;
		
		return(0);
	}*/
	 
	return 1;
}

/* void elegirAlgoritmo( unsigned alg, Datos & matriz, bool train = false ){
	clock_t start_time;
	
	if( alg == 2 ){ // 1-NN
		cout << "  1-NN:" << endl;
		//start_time = clock();
		cout << "  -> Entrenamiento: " << endl;
		start_time = clock();
		float nn1 = NN( matriz, true );
		// Tiempo de ejecución
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		cout << "  -> Prueba: " << endl;
		start_time = clock();
		float nn2 = NN( matriz, false );
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
	}
	else if( alg == 3 ){
		cout << "  Greedy:" << endl;
		start_time = clock();
		Greedy g( matriz );
		// Tiempo de ejecución
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
	
	
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, g.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, g.getPesos(), false, true );
	}
	else if( alg == 4 ){
		cout << "  Busqueda local:" << endl;
		start_time = clock();
		BusquedaLocal b( matriz );
		// Tiempo de ejecución
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
	
	
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, b.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, b.getPesos(), false, true );
	}
	else if( alg == 5 ){
		start_time = clock();
		AGG gb( matriz );
		// Tiempo de ejecución
		cout << "  AGG-BLX:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, gb.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, gb.getPesos(), false, true );
	}
	else if( alg == 6 ){
		start_time = clock();
		AGG gc( matriz, false );
		// Tiempo de ejecución
		cout << "  AGG-CA:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, gc.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, gc.getPesos(), false, true );
	}
	else if( alg == 7 ){
		start_time = clock();
		AGE eb( matriz );
		// Tiempo de ejecución
		cout << "  AGE-BLX:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, eb.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, eb.getPesos(), false, true );
	}
	else if( alg == 8 ){
		start_time = clock();
		AGE ec( matriz, false );
		// Tiempo de ejecución
		cout << "  AGE-CA:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
	
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, ec.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, ec.getPesos(), false, true );
	}
	else if( alg == 9 ){
		start_time = clock();
		AM a1( matriz );
		// Tiempo de ejecución
		cout << "  AM-(10, 1.0):" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, a1.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, a1.getPesos(), false, true );
	}
	else if( alg == 10 ){
		start_time = clock();
		AM a2( matriz, 2 );
		// Tiempo de ejecución
		cout << "  AM-(10, 0.1):" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, a2.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, a2.getPesos(), false, true );
	}
	else if( alg == 11 ){
		start_time = clock();
		AM a3( matriz, 3 );
		// Tiempo de ejecución
		cout << "  AM-(10, 0.1MEJ):" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, a3.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, a3.getPesos(), false, true );
	}
	else if( alg == 12 ){
		start_time = clock();
		ES es( matriz );
		// Tiempo de ejecución
		cout << "  ES:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, es.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, es.getPesos(), false, true );
	}
	else if( alg == 13 ){
		start_time = clock();
		ILS ils( matriz );
		// Tiempo de ejecución
		cout << "  ILS:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, ils.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, ils.getPesos(), false, true );
	}
	else if( alg == 14 ){
		start_time = clock();
		DE de( matriz );
		// Tiempo de ejecución
		cout << "  DE-rand:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, de.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, de.getPesos(), false, true );
	}
	else if( alg == 15 ){
		start_time = clock();
		DE de( matriz, false );
		// Tiempo de ejecución
		cout << "  DE-current-to-best:" << endl;
		cout << "  -> Tiempo: " << ((clock()- start_time)*1.0)/CLOCKS_PER_SEC << endl;
		
		cout << "  -> Entrenamiento: " << endl;
		funcionObjetivo( matriz, de.getPesos(), true, true );
		
		cout << "  -> Prueba: " << endl;
		funcionObjetivo( matriz, de.getPesos(), false, true );
	}
	
	
}*/
