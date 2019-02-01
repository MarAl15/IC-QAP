#ifndef _FUNCIONES_H
#define _FUNCIONES_H

#include "datos.h"

#define ALEATORIO 	0
#define RULETA 	 	1
#define TORNEO 		2

#define SIN_MEJORA 	0
#define BALDWIDIANA 1
#define LAMARCKIANA 2

using namespace std;

int calcularFitness( Datos & matrices, vector <int> & solucion, bool imprimir = false );

int ajustarFitness( Datos & matrices, vector <int> & solucion_ant, vector <int> & solucion, int coste_ant, unsigned i, unsigned j );

int sum(vector <int> v);

#endif
