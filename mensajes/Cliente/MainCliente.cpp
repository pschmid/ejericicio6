/*
 * MainCliente.cpp
 *
 *  Created on: 13/06/2013
 *      Author: pablo
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "Cliente.h"
#include "../Common/Mensajes.h"


#define CANTIDAD_INTERCAMBIOS	3

using namespace std;

void imprimirModoDeUso(){
	cout << endl << "MODO DE USO:" << endl << endl;
	cout << "	./ChanchoVa opciones" << endl <<endl;
	cout << "	Opciones:" << endl;
	cout << "			-n --num-jugadores <cant>: cantidad de jugadores (2 a" << NUM_JUGADORES_MAX << ")" << endl;
	cout << "			-d --debug (opcional): ejecutar en modo debug" << endl;
}

int main(int argc, char* argv[] ) {
//	OptionsParser opParser(argv, argc);
//
//	int cantidadJugadores = atoi(opParser.getOptionValue("-n", "--num-jugadores").c_str());
//	if (cantidadJugadores > NUM_JUGADORES_MAX || cantidadJugadores == 0) {
//		cout << endl << "ERROR: Cantidad de jugadores inválida." << endl;
//		imprimirModoDeUso();
//		return -1;
//	}
//
//	bool debug = opParser.optionExists("-d", "--debug");

	// cliente
	Cliente cliente ( (char *) COLA_SERVIDOR,'a' );

//	cliente.iniciarComunicacion();

	for ( int i=0;i<CANTIDAD_INTERCAMBIOS;i++ ) {

		// se envia el mensaje al servidor
		mensaje rta = cliente.enviarPeticion (cliente.recibirEntrada());
		cout << "Cliente: respuesta recibida = (ID = " << rta.pid << ") - " << rta.nombre << endl;

	}

	wait ( NULL );

	return 0;
}

