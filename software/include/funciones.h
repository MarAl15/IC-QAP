#ifndef _FUNCIONES_H
#define _FUNCIONES_H

#include "datos.h"

using namespace std;

int calcularFitness( Datos & matrices, vector <int> solucion, bool imprimir = false );

void PMX(vector <int> & C1, vector <int> & C2);

unsigned torneo( vector <int> & valoraciones, int M, unsigned n=5 );

#endif
