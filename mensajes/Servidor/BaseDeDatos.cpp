/*
 * BaseDeDatos.cpp
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#include "BaseDeDatos.h"

void BaseDeDatos::cargarBaseDesdeArchivo(){
    fstream bdfile;
    bdfile.open(ARCHIVO_BASE, ios_base::in | ios_base::binary);
    if (!bdfile.is_open()){
        bdfile.open(ARCHIVO_BASE, ios_base::in| ios_base::binary | ios_base::trunc);
    }
    while(!bdfile.eof()) {
        Registro r;
        t_registro tr;
        if(bdfile.read((char*)(&tr), sizeof (tr)) ){
        	r.crearDesdeRegistro(tr);
        	this->registros.push_back(r);
        } else {
        	break;
        }
    }
    bdfile.close();
}

BaseDeDatos::BaseDeDatos() {
    cargarBaseDesdeArchivo();
}

bool BaseDeDatos::duplicado(const Registro& r){
	vector<Registro>::iterator it;
	it = find_if(this->registros.begin(), this->registros.end(), CompadorDuplicado(r));
	return it != this->registros.end();
}

bool BaseDeDatos::datosRequeridos(const Registro& r){
	return r.getNombre().empty();
}


int BaseDeDatos::insertar(const Registro& r){
	if (this->duplicado(r)){
		return ERR_DUPLICADO;
	}
	if (this->datosRequeridos(r)){
		return ERR_CAMPO_REQUERIDO;
	}

	/* Insertar en cache */
	this->registros.push_back(r);

	/* Insertar en archivo */
	fstream bdfile;
	bdfile.open (ARCHIVO_BASE, ios_base::out | ios_base::binary | ios_base::app);
	t_registro reg = r.getRegistroASerializar();
	bdfile.write((char*)&reg, r.getSize());
	bdfile.close();

	return SUCCESS;
}

vector<Registro> BaseDeDatos::consultar(const Registro& aBuscar, int op){
	vector<Registro> v;
	vector<Registro>::iterator it = this->registros.begin();
	while (it != this->registros.end()){
		it = find_if(it, this->registros.end(), CompadorBusqueda(aBuscar, op));
		if (it != this->registros.end()){
			v.push_back(*it);
			it++;
		}
	}
	return v;
}

BaseDeDatos::~BaseDeDatos() {
//	fstream bdfile;
//	bdfile.open(ARCHIVO_BASE, ios_base::out| ios_base::binary | ios_base::trunc);
//	bdfile.close();
}
