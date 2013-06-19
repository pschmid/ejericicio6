/*
 * Registro.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../Common/Mensaje.h"
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct reg{
	char nombre[NOMBRE_SIZE];
	char direccion[DIRECCION_SIZE];
	char telefono[TELEFONO_SIZE];
} t_registro;

class Registro {
private:
	t_registro registro;
public:
	Registro();
	Registro(char nombre[NOMBRE_SIZE], char direccion[DIRECCION_SIZE], char telefono[TELEFONO_SIZE]);
	void crearDesdeMensaje(mensaje m);
	void crearDesdeRegistro(t_registro r);
	t_registro& getRegistroASerializar();
	int getSize();
	string getDireccion() const;
    string getNombre() const;
    string getTelefono() const;
    static bool compararDuplicado(const Registro& r1, const Registro& r2);
    static bool compararBusqueda(const Registro& r1, const Registro& r2);
	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
