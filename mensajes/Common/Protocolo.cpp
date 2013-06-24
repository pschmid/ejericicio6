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

bool Protocolo::esMensajeRespuesta(mensaje m) {
	return m.mtype == RESPUESTA;
}

bool Protocolo::esMensajeAcaEstoy(mensaje m) {
	return m.mtype == ACA_ESTOY;
}

bool Protocolo::esComandoInsertar(const string& c) {
	return c.compare("insertar") == 0 || c.compare("I") == 0;
}

bool Protocolo::esComandoModificar(const string& c) {
	return c.compare("modificar") == 0 || c.compare("M") == 0;
}

bool Protocolo::esComandoBorrar(const string& c) {
	return c.compare("borrar") == 0 || c.compare("B") == 0;
}

bool Protocolo::esComandoConsultar(const string& c) {
	return c.compare("consultar") == 0 || c.compare("C") == 0;
}

bool Protocolo::validarEntrada(const string& ent) {
	if (ent.empty()) {
		return false;
	}
	this->entrada = Util::split(ent, SEPARADOR);
	if (!esComandoInsertar(this->entrada[0]) && !esComandoConsultar(this->entrada[0])) {
		return false;
	}
	return true;
}

int Protocolo::getOp(const string& operacion){
	if (Util::toLower(operacion) == "and"){
		return COMP_AND;
	} else if (Util::toLower(operacion) == "or") {
		return COMP_OR;
	}
	return COMP_OR;
}

mensaje Protocolo::getMensajeRespuesta() {
	mensaje m;
	return m;
}

// FIXME sacar este horrible if else if y hacer un map o algo como la gente
long Protocolo::getMType(const string& cmd) {
	long mtype = 0;
	if (esComandoInsertar(cmd)) {
		mtype = INSERTAR;
	} else if (esComandoConsultar(cmd)) {
		mtype = CONSULTAR;
	} else if (esComandoBorrar(cmd)){
		mtype = ELIMINAR;
	} else if (esComandoModificar(cmd)){
		mtype = MODIFICAR;
	}
	return mtype;
}

void Protocolo::parsearEntradaConsultar(mensaje & peticion) {
	parsearEntrada(peticion);
}

void Protocolo::parsearEntradaInsertar(mensaje & peticion) {
	parsearEntrada(peticion);
}

void Protocolo::parsearEntradaModificar(mensaje & peticion) {
}

void Protocolo::parsearEntrada(mensaje & peticion) {
	peticion.mtype = this->getMType(entrada[0]);
	peticion.mtype = this->getMType(this->entrada[0]);
	peticion.pid = getpid();
	memset(peticion.nombre, 0, NOMBRE_SIZE);
	memset(peticion.direccion, 0, DIRECCION_SIZE);
	memset(peticion.telefono, 0, TELEFONO_SIZE);
	for (int i = 1; i < (int)entrada.size(); i++) {
		if(entrada[i].compare("-n")==0){
			unsigned int j=i;
			string nombre = "";
			while(j<entrada.size()-1){
				if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-d")==0){
					break;
				}
				nombre+=entrada[j+1]+SEPARADOR;
				j++;
			}

			strcpy(peticion.nombre,nombre.c_str());
		}
		if(entrada[i].compare("-d")==0){
			unsigned int j=i;
			string direccion = "";
			while(j<entrada.size()-1){
				if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-n")==0){
					break;
				}
				direccion+=entrada[j+1]+SEPARADOR;
				j++;
			}
			strcpy(peticion.direccion,direccion.c_str());
		}
		if(entrada[i].compare("-t")==0){
			unsigned int j=i;
			string telefono = "";
			while(j<entrada.size()-1){
				if(entrada[j+1].compare("-n")==0 || entrada[j+1].compare("-d")==0){
					break;
				}
				telefono+=entrada[j+1]+SEPARADOR;
				j++;
			}
			strcpy(peticion.telefono,telefono.c_str());
		}
	}
}

mensaje Protocolo::getMensajePeticion() {
	mensaje peticion;
	if (esComandoInsertar(entrada[0])){
		cout << "Enviando petición de insertar registro." << endl;
		parsearEntradaInsertar(peticion);
	} else if(esComandoConsultar(entrada[0])){
		cout << "Enviando petición de consultar registros." << endl;
		parsearEntradaConsultar(peticion);
	} else if (esComandoModificar(entrada[0])){
		cout << "Enviando petición de modificar registro." << endl;
		parsearEntradaModificar(peticion);
	}
	return peticion;
}

Protocolo::~Protocolo() {
}
