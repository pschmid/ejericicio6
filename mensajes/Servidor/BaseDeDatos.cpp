/*
 * BaseDeDatos.cpp
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#include "BaseDeDatos.h"

void BaseDeDatos::cargarBufferDesdeArchivo(){
    fstream bdfile;
    bdfile.open(ARCHIVO_BASE, ios_base::in | ios_base::binary);
    if (!bdfile.is_open()){
        bdfile.open(ARCHIVO_BASE, ios_base::in| ios_base::binary | ios_base::trunc);
    }
    while(!bdfile.eof() && !this->bufferLleno()) {
        Registro r;
        t_registro tr;
        if(bdfile.read((char*)(&tr), Registro::getSize()) ){
        	r.crearDesdeRegistro(tr);
        	this->bufferRegistros.push_back(r);
        } else {
        	break;
        }
    }
    bdfile.close();
}

void BaseDeDatos::volcarBufferAlArchivo(){
    fstream bdfile;
    bdfile.open(ARCHIVO_BASE, ios_base::in | ios_base::binary);
    if (!bdfile.is_open()){
        bdfile.open(ARCHIVO_BASE, ios_base::in| ios_base::binary | ios_base::trunc);
    }
    // TODO Volcar buffer
    bdfile.close();
}

BaseDeDatos::BaseDeDatos() {
    cargarBufferDesdeArchivo();
}

bool BaseDeDatos::bufferLleno(){
	return false;
}

bool BaseDeDatos::existente(const Registro& r){
	currrentPosition = find_if(this->bufferRegistros.begin(), this->bufferRegistros.end(), CompadorDuplicado(r));
	return currrentPosition != this->bufferRegistros.end();
}

bool BaseDeDatos::datosRequeridos(const Registro& r){
	return r.getNombre().empty();
}

int BaseDeDatos::insertar(const Registro& r){
	if (this->existente(r)){
		return ERR_DUPLICADO;
	}
	if (this->datosRequeridos(r)){
		return ERR_CAMPO_REQUERIDO;
	}

	/* Insertar en cache */
	this->bufferRegistros.push_back(r);

	/* Insertar en archivo */
	fstream bdfile;
	bdfile.open (ARCHIVO_BASE, ios_base::out | ios_base::binary | ios_base::app);
	t_registro reg = r.getRegistroASerializar();
	bdfile.write((char*)&reg, Registro::getSize());
	bdfile.close();

	return SUCCESS;
}

int BaseDeDatos::modificar(const Registro& exist, const Registro& modif){
	if (!this->existente(exist)){
		return ERR_NO_EXISTE;
	}
	vector<Registro>::iterator it = currrentPosition;
	if (this->existente(modif) && !exist.compararPorNombre(modif)){
		return ERR_DUPLICADO;
	}

	Registro nuevo = modif;
	nuevo.llenarVacios(*it);

	/* Modificar en cache */
	it = this->bufferRegistros.insert(it, nuevo);
	if ((it+1) != this->bufferRegistros.end()){
		this->bufferRegistros.erase(it+1);
	}
	currrentPosition = it;

	/* Modificar en el archivo */
	t_registro reg = nuevo.getRegistroASerializar();
	t_registro rbusq;
	Registro busq;
	bool encontrado = false;
	fstream bdfile;
	bdfile.open (ARCHIVO_BASE, ios_base::out | ios_base::in | ios_base::binary);
	while(!bdfile.eof() && !encontrado){
		bdfile.read((char*)&rbusq, Registro::getSize());
		busq.crearDesdeRegistro(rbusq);
		if (exist.compararPorNombre(busq)){
			bdfile.seekp(- Registro::getSize(), ios_base::cur);
			bdfile.write((char*)&reg, Registro::getSize());
			encontrado = true;
		}
	}
	bdfile.close();

	return SUCCESS;
}

vector<Registro> BaseDeDatos::consultar(const Registro& aBuscar, int op){
	vector<Registro> v;
	vector<Registro>::iterator it = this->bufferRegistros.begin();
	while (it != this->bufferRegistros.end()){
		it = find_if(it, this->bufferRegistros.end(), CompadorBusqueda(aBuscar, op));
		if (it != this->bufferRegistros.end()){
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
