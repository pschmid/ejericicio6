#ifndef PRODUCTOR_H_
#define PRODUCTOR_H_

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>

#include "Cola.h"
#include "Producto.h"

using namespace std;

class Productor {
	private:
		char* nombre;
		int calcularRandom ();

	public:
		Productor ( char* nombre );
		~Productor ();
		void producir ( Cola<producto>** cola,int cantColas,int vueltas );
};

#endif /* PRODUCTOR_H_ */
