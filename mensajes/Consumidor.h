#ifndef CONSUMIDOR_H_
#define CONSUMIDOR_H_

#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "Cola.h"
#include "Producto.h"

using namespace std;

class Consumidor {
	private:
		char* nombre;

	public:
		Consumidor ( char* nombre );
		~Consumidor ();
		void consumir ( Cola<producto>* cola,int vueltas );
};

#endif /* CONSUMIDOR_H_ */
