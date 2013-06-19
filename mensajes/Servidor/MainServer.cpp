/*
 * MainServer.cpp
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
#include "Servidor.h"

#define CANTIDAD_INTERCAMBIOS	3

using namespace std;

void imprimirModoDeUso(){
	cout << endl << "MODO DE USO:" << endl << endl;
	cout << "	./Servidor opciones" << endl <<endl;
}

int main(int argc, char* argv[] ) {
	Servidor servidor ( (char *) COLA_SERVIDOR,'a' );
	servidor.iniciar();
	wait(NULL);

//	BaseDeDatos bd;
	return 0;
}


