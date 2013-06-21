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
		cout << "Enviando petición de insertar." << endl;
	} else if (esComandoConsultar(cmd)) {
		mtype = CONSULTAR;
		cout << "Enviando petición de consultar registros." << endl;
	} else if (esComandoBorrar(cmd)){
		mtype = ELIMINAR;
		cout << "Borrar:" << endl;
	} else if (esComandoModificar(cmd)){
		mtype = MODIFICAR;
		cout << "Modificar:" << endl;
	}
	return mtype;
}

void Protocolo::parsearMensajeInsertar(mensaje & peticion) {
	string nombre, telefono, direccion, operacion;
    vector<string>::const_iterator itNom, itTel, itDir, itOp;
    itNom = find(this->entrada.begin(), this->entrada.end(), "-n");
    itTel = find(this->entrada.begin(), this->entrada.end(), "-t");
    itDir = find(this->entrada.begin(), this->entrada.end(), "-d");
    itOp = find(this->entrada.begin(), this->entrada.end(), "-o");
    nombre = (itNom != this->entrada.end()) ? *(itNom + 1) : "";
    telefono = (itTel != this->entrada.end()) ? *(itTel + 1) : "";
    direccion = (itDir != this->entrada.end()) ? *(itDir + 1) : "";
    operacion = (itOp != this->entrada.end()) ? *(itOp + 1) : "";
    strcpy(peticion.nombre, nombre.c_str());
    strcpy(peticion.telefono, telefono.c_str());
    strcpy(peticion.direccion, direccion.c_str());
    peticion.op = getOp(operacion);
}

void Protocolo::parsearMensajeConsultar(mensaje & peticion) {
	string nombre, telefono, direccion, operacion;
    vector<string>::const_iterator itNom, itTel, itDir, itOp;
    itNom = find(this->entrada.begin(), this->entrada.end(), "-n");
    itTel = find(this->entrada.begin(), this->entrada.end(), "-t");
    itDir = find(this->entrada.begin(), this->entrada.end(), "-d");
    itOp = find(this->entrada.begin(), this->entrada.end(), "-o");
    nombre = (itNom != this->entrada.end()) ? *(itNom + 1) : "";
    telefono = (itTel != this->entrada.end()) ? *(itTel + 1) : "";
    direccion = (itDir != this->entrada.end()) ? *(itDir + 1) : "";
    operacion = (itOp != this->entrada.end()) ? *(itOp + 1) : "";
    strcpy(peticion.nombre, nombre.c_str());
    strcpy(peticion.telefono, telefono.c_str());
    strcpy(peticion.direccion, direccion.c_str());
    peticion.op = getOp(operacion);
}

mensaje Protocolo::getMensajePeticion() {
	mensaje peticion;
	peticion.mtype = this->getMType(this->entrada[0]);
	peticion.pid = getpid();

	if (esMensajeInsertar(peticion)){
		parsearMensajeInsertar(peticion);
	} else if (esMensajeConsultar(peticion)){
		parsearMensajeConsultar(peticion);
	}

	cout << "nombre " << peticion.nombre << endl;
	cout << "dir " << peticion.direccion << endl;
	cout << "tel " << peticion.telefono << endl;
	cout << "op " << peticion.op << endl;

	return peticion;
}

Protocolo::~Protocolo() {
}
