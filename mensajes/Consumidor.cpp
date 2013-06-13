#include "Consumidor.h"

Consumidor :: Consumidor ( char* nombre ) {
	int tamanio = strlen ( nombre ) + 1;
	this->nombre = new char [ tamanio ];
	strcpy ( this->nombre,nombre );

	cout << "Consumidor [" << this->nombre << "] creado con process id = " << getpid () << endl;
}

Consumidor :: ~Consumidor () {
	delete [] this->nombre;
}

void Consumidor :: consumir ( Cola<producto>* cola,int vueltas ) {

	for ( int i=0;i<vueltas;i++ ) {
		sleep ( 1 );

		// se lee el producto de la cola
		producto prod;
		int resultado = cola->leer ( TIPO_PRODUCTO,&prod );

		if ( resultado < 0 )
			cout << "Error de lectura en la cola: " << strerror(errno) << endl;
		else
			cout << "El consumidor [" << this->nombre << "] lee el producto " << prod.numeroRandom << endl;
	}

}
