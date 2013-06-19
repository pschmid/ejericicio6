/*
 * BaseDeDatos.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <vector>
#include <string>
#include "Registro.h"

using namespace std;

class BaseDeDatos {
public:
	BaseDeDatos();
	int insertar();
	vector<Registro> consulta(string cons);
	virtual ~BaseDeDatos();
private:
	vector<Registro> datos;
};

#endif /* BASEDEDATOS_H_ */
