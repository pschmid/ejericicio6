/*
 * Registro.cpp
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#include "Registro.h"

Registro::Registro() {
	memset(registro.nombre,0,NOMBRE_SIZE);
	memset(registro.direccion,0,DIRECCION_SIZE);
	memset(registro.telefono,0,TELEFONO_SIZE);
}

Registro::Registro(char nombre[NOMBRE_SIZE], char direccion[DIRECCION_SIZE], char telefono[TELEFONO_SIZE]) {
	strcpy(registro.direccion, direccion);
	strcpy(registro.nombre, nombre);
	strcpy(registro.telefono, telefono);
}

void Registro::crearDesdeMensaje(mensaje m){
	strcpy(registro.direccion, m.direccion);
	strcpy(registro.nombre, m.nombre);
	strcpy(registro.telefono, m.telefono);
}
mensaje Registro :: crearMensajeAsociado() const{
	mensaje m;
	strcpy(m.direccion,registro.direccion);
	strcpy(m.nombre, registro.nombre);
	strcpy(m.telefono,registro.telefono);
	return m;
}

void Registro::crearDesdeRegistro(t_registro r){
	strcpy(registro.direccion, r.direccion);
	strcpy(registro.nombre, r.nombre);
	strcpy(registro.telefono, r.telefono);
}

t_registro Registro::getRegistroASerializar() const{
	return registro;
}

int Registro::getSize(){
	return sizeof(t_registro);
}

string Registro::getDireccion() const
 {
	string d(registro.direccion);
	return d;
 }

string Registro::getNombre() const
{
	string n(registro.nombre);
	return n;
}

string Registro::getTelefono() const
{
	string t(registro.telefono);
	return t;
}
bool Registro::vacio() const{
	return this->getNombre().empty() &&
			this->getDireccion().empty() &&
			this->getTelefono().empty();
}

bool Registro::compararDuplicado(const Registro& r2) const{
	return this->compararPorNombre(r2);
}

bool Registro::compararPorNombre(const Registro& r2) const{
	string lowernom = Util::toLower(this->getNombre());
	return lowernom.compare(Util::toLower(r2.getNombre())) == 0;
}

bool Registro::compararBusqueda(const Registro& r2, int op) const{
	bool foundNom = false, foundDir = false, foundTel = false;

	if(r2.vacio()){
		return true;
	}
	if (!r2.getNombre().empty()){
		string lowernom = Util::toLower(this->getNombre());
		foundNom = (lowernom.find(Util::toLower(r2.getNombre())) != string::npos);
	} else if (op == COMP_AND){
		foundNom = true;
	}

	if (!r2.getDireccion().empty()){
		string lowerdir = Util::toLower(this->getDireccion());
		foundDir = (lowerdir.find(Util::toLower(r2.getDireccion())) != string::npos);
	} else if (op == COMP_AND){
		foundDir = true;
	}

	if (!r2.getTelefono().empty()){
		foundTel = (this->getTelefono().find(r2.getTelefono()) != string::npos);
	} else if (op == COMP_AND){
		foundTel = true;
	}

	if (op == COMP_AND){
		return foundDir && foundTel && foundNom;
	} else {
		return foundDir || foundTel || foundNom;
	}
}

void Registro::llenarVacios(const Registro& reg){
	if (this->getNombre().empty()){
		strcpy(registro.nombre, reg.getNombre().c_str());
	}
	if (this->getDireccion().empty()){
		strcpy(registro.direccion, reg.getDireccion().c_str());
	}
	if (this->getTelefono().empty()){
		strcpy(registro.telefono, reg.getTelefono().c_str());
	}
}

Registro::~Registro() {
}
