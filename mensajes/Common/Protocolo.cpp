/*
 * Protocolo.cpp
 *
 *  Created on: 17/06/2013
 *      Author: gonzalo
 */

#include "Protocolo.h"

Protocolo::Protocolo() {
}

bool Protocolo::esMensajeInsertar(mensaje m) {
	return m.mtype == INSERTAR;
}

bool Protocolo::esMensajeConsultar(mensaje m) {
	return m.mtype == CONSULTAR;
}

bool Protocolo::esComandoInsertar(const string& c) {
	return c.compare("insertar") == 0 || c.compare("I") == 0;
}

bool Protocolo::esComandoConsultar(const string& c) {
	return c.compare("consultar") == 0 || c.compare("C") == 0;
}

bool Protocolo::validarEntrada(const string& ent) {
	if (ent.empty()) {
		return false;
	}
	this->entrada = Util::split(ent, SEPARADOR);
	if (!esComandoInsertar(this->entrada[0]) && !esComandoConsultar(
			this->entrada[0])) {
		return false;
	}
	return true;
}

mensaje Protocolo::getMensajeRespuesta() {
	mensaje m;
	return m;
}

long Protocolo::getMType(const string& cmd) {
	long mtype;
	if (esComandoInsertar(cmd)) {
		mtype = INSERTAR;
		cout << "Insertar:" << endl;
	} else if (esComandoConsultar(cmd)) {
		mtype = CONSULTAR;
		cout << "Consultar:" << endl;
	}
	return mtype;
}

mensaje Protocolo::getMensajePeticion() {
	mensaje peticion;
	string nombre, telefono, direccion;
	peticion.mtype = this->getMType(this->entrada[0]);
	peticion.pid = getpid();

	vector<string>::const_iterator it = find(this->entrada.begin(),	this->entrada.end(), "-n");
	nombre = (it != this->entrada.end()) ? *(it + 1) : "";
	it = find(this->entrada.begin(), this->entrada.end(), "-t");
	telefono = (it != this->entrada.end()) ? *(it + 1) : "";
	it = find(this->entrada.begin(), this->entrada.end(), "-d");
	direccion = (it != this->entrada.end()) ? *(it + 1) : "";

	strcpy(peticion.nombre, nombre .c_str());
	strcpy(peticion.telefono, telefono.c_str());
	strcpy(peticion.direccion, direccion.c_str());

	cout << "nombre " << peticion.nombre << endl;
	cout << "dir " << peticion.direccion << endl;
	cout << "tel " << peticion.telefono << endl;

	return peticion;
}

//mensaje Cliente :: getMensajePeticion(){
//
//	mensaje peticion;
//	if(entrada[0].compare("insertar")==0){
//		mtype = INSERTAR;
//		cout << "para insertar" << endl;
//	}else if (entrada[0].compare("consultar")==0){
//		mtype = CONSULTAR;
//		cout << "para consultar" << endl;
//	}
//
//	peticion.mtype = mtype;
//	peticion.pid = getpid();
//
//	for (int i = 1; i < (int)entrada.size(); i++) {
//
//		cout << "valor de entrada " << i << "  "<<entrada[i] <<endl;
//
//		if(entrada[i].compare("-n")==0){
//			unsigned int j=i;
//			string nombre = "";
//			while(j<entrada.size()-1){
//				if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-d")==0){
//					break;
//				}
//				nombre+=entrada[j+1]+SEPARADOR;
//				j++;
//			}
//
//			strcpy(peticion.nombre,nombre.c_str());
//		}
//		if(entrada[i].compare("-d")==0){
//					unsigned int j=i;
//					string direccion = "";
//					while(j<entrada.size()-1){
//						if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-n")==0){
//							break;
//						}
//						direccion+=entrada[j+1]+SEPARADOR;
//						j++;
//					}
//					strcpy(peticion.direccion,direccion.c_str());
//				}
//		if(entrada[i].compare("-t")==0){
//					unsigned int j=i;
//					string telefono = "";
//					while(j<entrada.size()-1){
//						if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-d")==0){
//							break;
//						}
//						telefono+=entrada[j+1]+SEPARADOR;
//						j++;
//					}
//					strcpy(peticion.telefono,telefono.c_str());
//				}
//
//	}
//	cout << "nombre "<< peticion.nombre <<endl;
//	cout << "dir "<< peticion.direccion <<endl;
//	cout << "tel "<< peticion.telefono <<endl;
//	return peticion;
//
//}


Protocolo::~Protocolo() {
}
