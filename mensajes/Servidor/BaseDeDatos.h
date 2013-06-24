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
#define ERR_NO_EXISTE 3
#define SUCCESS 0

#include <vector>
#include <string>
#include <fstream>
#include "Registro.h"

using namespace std;

class BaseDeDatos {
public:
	/* Crea la base de datos, si no existe. Si existe
	 * llena el buffer desde el disco. */
	BaseDeDatos();

	/* Inserta un nuevo registro @r en la base de datos.
	 * Si está duplicado devuelve ERR_DUPLICADO
	 * Si faltan datos devuelve ERR_DATOS_FALTANTES */
	int insertar(const Registro& r);

	/* Busca el registro @exist, si lo encuentra inserta en su lugar el valor de @modif.
	 * Si no lo encuentra devuelve ERR_NO_EXISTE
	 * Si faltan datos en @modif devuelve ERR_DATOS_FALTANTES */
	int modificar(const Registro& exist, const Registro& modif);

	/* Devuelve un vector de registros coincidentes con la búsqueda */
	vector<Registro> consultar(const Registro& aBuscar, int op);

	/* Vuelca el buffer a disco. */
	virtual ~BaseDeDatos();

	vector<Registro> bufferRegistros;
private:
	vector<Registro>::iterator currrentPosition;
	bool existente(const Registro& r);
	bool datosRequeridos(const Registro& r);
	bool bufferLleno();
    void cargarBufferDesdeArchivo();
    void volcarBufferAlArchivo();
};

/* Predicates de comparación */
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
