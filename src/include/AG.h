#ifndef _AG_H
#define _AG_H

#include <vector>

using namespace std;


class AG{
	public:
		// Torneo
		unsigned torneo( vector <int> & valoraciones, int M, unsigned n=7 );
		// Operador de cruce PMX
		void PMX(vector <int> & C1, vector <int> & C2);
};

#endif
