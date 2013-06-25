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
#include "../Common/Util.h"

using namespace std;

void imprimirModoDeUso(){
	cout << endl << "MODO DE USO:" << endl << endl;
	cout << "	./Servidor opciones" << endl <<endl;
}

string result(int r){
	return (r == SUCCESS)? "Insertado.": (r == ERR_DUPLICADO)? "Duplicado." : "Faltan campos";
}

void mostrarRegistros(vector<Registro>* regs){
	cout << endl;
	if (regs->empty()){
		cout << "No hay nada para mostrar." << endl;
	}
	vector<Registro>::iterator it;
	for (it = regs->begin(); it != regs->end(); it++){
		cout << it->getNombre() << " | " << it->getDireccion() << " | " << it->getTelefono() << endl;
	}
}

int main(int argc, char* argv[] ) {
	Servidor servidor ( (char *) COLA_SERVIDOR,'a' );
	servidor.iniciar();
	wait(NULL);

	/* Pruebas BD */
//	char nombre[NOMBRE_SIZE], dire[DIRECCION_SIZE], tel[TELEFONO_SIZE];
//	memset(nombre, 0, NOMBRE_SIZE);
//	//strcpy(nombre,"Raul");
//	strcpy(dire,"lala");
//	strcpy(tel, "41111111");
//	Registro r1(nombre, dire, tel);
//
//	strcpy(nombre,"Lauro");
//	strcpy(dire,"Calle Falsa 1234");
//	strcpy(tel, "42222222");
//	Registro r2(nombre, dire, tel);
//
//	strcpy(nombre,"Jorge");
//	strcpy(dire,"Calle Falsa 2345");
//	strcpy(tel, "43333333");
//	Registro r3(nombre, dire, tel);
//
//	strcpy(nombre,"Gonza");
//	strcpy(dire,"Calle Falsa 3456");
//	strcpy(tel, "44444444");
//	Registro r4(nombre, dire, tel);
//
//	BaseDeDatos bd;
//	cout << "Intentando insertar a: " << r1.getNombre() << ". Resultado: " << result(bd.insertar(r1)) << endl;
//	cout << "Intentando insertar a: " << r2.getNombre() << ". Resultado: " << result(bd.insertar(r2)) << endl;
//	cout << "Intentando insertar a: " << r3.getNombre() << ". Resultado: " << result(bd.insertar(r3)) << endl;
//	cout << "Intentando insertar a: " << r4.getNombre() << ". Resultado: " << result(bd.insertar(r4)) << endl;
//
//	string n = "gonza          ";
//	strcpy(nombre, Util::trim(n).c_str());
//	strcpy(dire,"");
//	strcpy(tel, "4");
//	Registro aBuscar(nombre, dire, tel);
//	vector<Registro> regs = bd.consultar(aBuscar, COMP_AND);
//	mostrarRegistros(&regs);

//	mostrarRegistros(&bd.bufferRegistros);
//
//	strcpy(nombre,"Jorge Lanata3");
//	strcpy(dire,"Calle laaallalalaal");
//	strcpy(tel, "44444441");
//	Registro nuevo(nombre, dire, tel);
//	bd.modificar(r3, nuevo);
//
//	mostrarRegistros(&bd.bufferRegistros);

	return 0;
}


