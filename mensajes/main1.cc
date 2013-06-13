#ifdef EJEMPLO_1

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "Cola.h"
#include "Productor.h"
#include "Consumidor.h"
#include "Producto.h"

#define CANTIDAD_CONSUMIDORES	3
#define VUELTAS					3


int main () {

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {

		int pid = fork ();

		if ( pid == 0 ) {

			char nombreCons[50];
			char numero[10];
			sprintf ( numero,"%u",i+1 );

			strcpy ( nombreCons,"Consumidor " );
			strcat ( nombreCons,numero );

			Cola<producto> cola ( (char *)"main1.cc",i );

			Consumidor consumidor ( nombreCons );
			consumidor.consumir ( &cola,VUELTAS );
			return 0;
		}
	}


	Cola<producto>* colas[CANTIDAD_CONSUMIDORES];

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {
		colas[i] = new Cola<producto> ( (char *) "main1.cc",i );
	}

	Productor productor ( (char *) "Productor" );
	productor.producir ( colas,CANTIDAD_CONSUMIDORES,VUELTAS );

	for ( int i=0;i<CANTIDAD_CONSUMIDORES;i++ ) {
		int resultado = colas[i]->destruir();

		if ( resultado < 0 )
			perror ( strerror(errno) );

		delete ( colas[i] );
	}

	return 0;
}

#endif
