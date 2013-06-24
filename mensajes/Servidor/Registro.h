/*
 * Registro.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../Common/Mensaje.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
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
	static int getSize();
	void crearDesdeMensaje(mensaje m);
	void crearDesdeRegistro(t_registro r);
	mensaje crearMensajeAsociado();
	t_registro getRegistroASerializar() const;
	string getDireccion() const;
    string getNombre() const;
    string getTelefono() const;
    bool vacio() const;
    bool compararDuplicado(const Registro& r2) const;
    bool compararBusqueda(const Registro& r2, int op) const;
	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
