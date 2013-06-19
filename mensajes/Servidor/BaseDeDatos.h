/*
 * BaseDeDatos.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#define ARCHIVO_BASE "basededatos.bin"

#include <vector>
#include <string>
#include <fstream>
#include "Registro.h"

using namespace std;

class BaseDeDatos {
public:
	BaseDeDatos();
	int insertar(Registro r);
	int borrar(Registro r);
	int modificar(Registro r);
	vector<Registro> consultar(const Registro& aBuscar);
    void cargarBaseDesdeArchivo();
	virtual ~BaseDeDatos();
private:
	vector<Registro> registros;
};

#endif /* BASEDEDATOS_H_ */
