/*
 * Registro.h
 *
 *  Created on: 18/06/2013
 *      Author: gonzalo
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include "../Common/Mensaje.h"

class Registro {
private:
	char nombre[61];
	char direccion[120];
	char telefono[13];
public:
	Registro();
	void crearDesdeMensaje();
	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
