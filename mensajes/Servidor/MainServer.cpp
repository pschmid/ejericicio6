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

string result(int r){
	return (r == SUCCESS)? "Insertado.": (r == ERR_DUPLICADO)? "Duplicado." : "Faltan campos";
}


int main(int argc, char* argv[] ) {
	Servidor servidor ( (char *) COLA_SERVIDOR,'a' );
	servidor.iniciar();
	wait(NULL);

//	/* Pruebas BD */
//	char nombre[NOMBRE_SIZE], dire[DIRECCION_SIZE], tel[TELEFONO_SIZE];
//	memset(nombre, 0, NOMBRE_SIZE);
//	//strcpy(nombre,"Raul");
//	strcpy(dire,"lala");
//	strcpy(tel, "3214");
//	Registro r1(nombre, dire, tel);
//
//	strcpy(nombre,"Pepe");
//	strcpy(dire,"sad");
//	strcpy(tel, "123");
//	Registro r2(nombre, dire, tel);
//
//	strcpy(nombre,"Pepe");
//	strcpy(dire,"sadsada");
//	strcpy(tel, "5462");
//	Registro r3(nombre, dire, tel);
//
//	strcpy(nombre,"Pepe");
//	strcpy(dire,"lalal");
//	strcpy(tel, "12358");
//	Registro r4(nombre, dire, tel);
//
//	BaseDeDatos bd;
//	cout << "Intentando insertar a: " << r1.getNombre() << ". Resultado: " << result(bd.insertar(r1)) << endl;
//	cout << "Intentando insertar a: " << r2.getNombre() << ". Resultado: " << result(bd.insertar(r2)) << endl;
//	cout << "Intentando insertar a: " << r2.getNombre() << ". Resultado: " << result(bd.insertar(r3)) << endl;
//	cout << "Intentando insertar a: " << r2.getNombre() << ". Resultado: " << result(bd.insertar(r4)) << endl;
//
//	strcpy(nombre,"pe");
//	strcpy(dire,"lala");
//	strcpy(tel, "");
//	Registro aBuscar(nombre, dire, tel);
//
//	vector<Registro> regs = bd.consultar(aBuscar, COMP_OR);
//	vector<Registro>::iterator it;
//	for (it = regs.begin(); it != regs.end(); it++){
//		cout << it->getNombre() << " " << it->getDireccion() << " " << it->getTelefono() << endl;
//	}

	return 0;
}


