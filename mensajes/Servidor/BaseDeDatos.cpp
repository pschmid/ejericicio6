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

int BaseDeDatos::insertar(Registro r){
	this->registros.push_back(r);

	fstream bdfile;
	bdfile.open (ARCHIVO_BASE, ios_base::out | ios_base::binary | ios_base::app);
	t_registro reg = r.getRegistroASerializar();
	bdfile.write((char*)&reg, r.getSize());
	bdfile.close();

	return 0;
}

vector<Registro> BaseDeDatos::consultar(const Registro& aBuscar){
	//vector<Registro> v;
	//vector<Registro>::iterator it = find_if(v.begin(), v.end(), Registro::compararBusqueda);
	return this->registros;
}

BaseDeDatos::~BaseDeDatos() {
}
