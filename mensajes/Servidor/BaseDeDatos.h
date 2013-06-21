/*
 * BaseDeDatos.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#define ARCHIVO_BASE "basededatos.bin"
#define ERR_DUPLICADO 1
#define ERR_CAMPO_REQUERIDO 2
#define SUCCESS 0

#include <vector>
#include <string>
#include <fstream>
#include "Registro.h"

using namespace std;

class BaseDeDatos {
public:
	BaseDeDatos();
	int insertar(const Registro& r);
	int borrar(const Registro& r);
	int modificar(const Registro& r);
	vector<Registro> consultar(const Registro& aBuscar, int op);
    void cargarBaseDesdeArchivo();
	virtual ~BaseDeDatos();
private:
	vector<Registro> registros;
	bool duplicado(const Registro& r);
	bool datosRequeridos(const Registro& r);
};

struct CompadorBusqueda {
    Registro aBuscar;
    int operacion;
	CompadorBusqueda( Registro r, int op) : aBuscar(r), operacion(op) { }
    bool operator() (const Registro& reg) const {
    	return reg.compararBusqueda(aBuscar, operacion);
    }
};

struct CompadorDuplicado {
    Registro aBuscar;
    CompadorDuplicado(Registro r) : aBuscar(r) { }
    bool operator() (const Registro& reg) const {
    	return reg.compararDuplicado(aBuscar);
    }
};
#endif /* BASEDEDATOS_H_ */
