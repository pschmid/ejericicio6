#ifdef EJEMPLO_2

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "Cliente.h"
#include "Servidor.h"
#include "Mensajes.h"
#include "MemoriaCompartida.h"

#define CANTIDAD_INTERCAMBIOS	3

using namespace std;

int main () {

	int processId = fork ();

	if ( processId == 0 ) {
//		if ( estadoMemoria == SHM_OK ) {
//					// escribe un dato para el hijo
//			memoria.escribir ( random );
//
//					// espera a que termine el hijo
//					int estado = 0;
//					wait ( &estado );
//					// libera la memoria
//					memoria.liberar ();
//		}


		// servidor que escucha inserciones a la base.
		Servidor servidor ( (char *) "main2.cc",'a' );
		servidor.iniciar();
		vector<mensaje> datos;
		wait(NULL);
		return 0;

	} else {

		// cliente
		Cliente cliente ( (char *) "main2.cc",'a' );

		for ( int i=0;i<CANTIDAD_INTERCAMBIOS;i++ ) {

			// se envia el mensaje al servidor
			mensaje rta = cliente.enviarPeticion (cliente.recibirEntrada());
			cout << "Cliente: respuesta recibida = (ID = " << rta.id << ") - " << rta.nombre << endl;

		}

		wait ( NULL );

		return 0;
	}
}

#endif

