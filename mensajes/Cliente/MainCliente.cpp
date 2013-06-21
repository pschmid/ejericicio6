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

#define CANTIDAD_INTERCAMBIOS	3

using namespace std;

int main(int argc, char* argv[]) {
	Cliente cliente ( (char *) COLA_SERVIDOR,'a' );
	cliente.iniciar();
	wait ( NULL );
	return 0;
}
