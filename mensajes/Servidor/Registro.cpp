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

void Registro::crearDesdeRegistro(t_registro r){
	strcpy(registro.direccion, r.direccion);
	strcpy(registro.nombre, r.nombre);
	strcpy(registro.telefono, r.telefono);
}

t_registro& Registro::getRegistroASerializar(){
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

 bool Registro::compararDuplicado(const Registro& r1, const Registro& r2){
	 return true;
 }

 bool Registro::compararBusqueda(const Registro& r1, const Registro& r2){
	 return true;
 }

Registro::~Registro() {
}
