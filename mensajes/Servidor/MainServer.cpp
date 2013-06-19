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

	/* Pruebas BD */
//	char nombre[NOMBRE_SIZE], dire[DIRECCION_SIZE], tel[TELEFONO_SIZE];
//	strcpy(nombre,"Raul");
//	strcpy(dire,"lala");
//	strcpy(tel, "3214");
//	Registro r1(nombre, dire, tel);
//
//	strcpy(nombre,"Ernestina");
//	strcpy(dire,"asdsa");
//	strcpy(tel, "6648498");
//	Registro r2(nombre, dire, tel);
//
//	strcpy(nombre,"Pepe");
//	strcpy(dire,"sadsada");
//	strcpy(tel, "12154");
//	Registro r3(nombre, dire, tel);
//
//	BaseDeDatos bd;
//	bd.insertar(r1);
//	bd.insertar(r2);
//	bd.insertar(r3);
//
//	vector<Registro> regs = bd.consultar(r1);
//	vector<Registro>::iterator it;
//	for (it = regs.begin(); it != regs.end(); it++){
//		cout << it->getNombre() << " " << it->getDireccion() << " " << it->getTelefono() << endl;
//	}

	return 0;
}


