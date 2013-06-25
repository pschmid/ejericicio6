/*
 * Protocolo.cpp
 *
 *  Created on: 17/06/2013
 *      Author: gonzalo
 */

#include "Protocolo.h"

void setearNombre(mensaje& m, const string& val){
	strcpy(m.nombre, val.c_str());
}
void setearDire(mensaje& m, const string& val){
	strcpy(m.direccion, val.c_str());
}
void setearTel(mensaje& m, const string& val){
	strcpy(m.telefono, val.c_str());
}
void setearNombreCons(mensaje& m, const string& val){
	strcpy(m.nombreCons, val.c_str());
}
void setearOp(mensaje& m, const string& val){
	m.op = Protocolo::getOp(val);
}

Protocolo::Protocolo() {
	this->params[0] = "-n";
	this->params[1] = "-d";
	this->params[2] = "-t";
	this->params[3] = "-m";
	this->params[4] = "-o";
	this->actions[0] = setearNombre;
	this->actions[1] = setearDire;
	this->actions[2] = setearTel;
	this->actions[3] = setearNombreCons;
	this->actions[4] = setearOp;
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

bool Protocolo::esMensajeModificar(mensaje m) {
	return m.mtype == MODIFICAR;
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
	if (!esComandoInsertar(this->entrada[0]) &&
		!esComandoConsultar(this->entrada[0]) &&
		!esComandoModificar(entrada[0]))
	{
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

int Protocolo::posParametro(const string& s){
	for (int i=0; i < CANT_PARAMS; i++){
		if (s.compare(Protocolo::params[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void Protocolo::completarCampo(mensaje& peticion, int pos, const string& valor){
	this->actions[pos](peticion, valor);
}

void Protocolo::inicializarPeticion(mensaje& peticion){
	peticion.mtype = this->getMType(entrada[0]);
	peticion.pid = getpid();
	memset(peticion.nombre, 0, NOMBRE_SIZE);
	memset(peticion.direccion, 0, DIRECCION_SIZE);
	memset(peticion.telefono, 0, TELEFONO_SIZE);
	memset(peticion.nombreCons, 0, NOMBRE_SIZE);
}

mensaje Protocolo::getMensajePeticion() {
	mensaje peticion;
	inicializarPeticion(peticion);
	for (int i = 1; i < (int)entrada.size(); i++) {
		int pos = posParametro(entrada[i]);
		if(pos != -1){
			unsigned int j = i;
			string valor = "";
			while(j < entrada.size() - 1){
				if (posParametro(entrada[j+1]) != -1){
					break;
				}
				valor += entrada[j+1] + SEPARADOR;
				j++;
			}
			completarCampo(peticion,pos,Util::trim(valor));
		}
	}
	return peticion;
}

Protocolo::~Protocolo() {
}
