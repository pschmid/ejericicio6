#include "Productor.h"

Productor :: Productor ( char* nombre ) {
	int tamanio = strlen ( nombre ) + 1;
	this->nombre = new char [ tamanio ];
	strcpy ( this->nombre,nombre );
}

Productor :: ~Productor () {
	delete [] this->nombre;
}

void Productor :: producir ( Cola<producto>** cola,int cantColas,int vueltas ) {

	producto prod;
	prod.mtype = TIPO_PRODUCTO;

	for ( int j=0;j<vueltas;j++ ) {
		sleep ( 5 );
		prod.numeroRandom = this->calcularRandom ();
		for ( int i=0;i<cantColas;i++ ) {
			int resultado = cola[i]->escribir ( prod );
			if ( resultado < 0 )
				cout << "Error de escritura en la cola: " << strerror(errno) << endl;
			else
				cout << "El productor [" << this->nombre << "] produce " << prod.numeroRandom << endl;
		}
	}
}

int Productor :: calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % 100;
	return resultado;
}
