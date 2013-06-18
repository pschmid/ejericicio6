/*
 * MensajeFactory.cpp
 *
 *  Created on: 27/11/2012
 *      Author: martin
 */

#include "MensajeFactory.h"

MensajeFactory::MensajeFactory() {

}

mensaje MensajeFactory::crearMensajeAviso(int pid){
	int nuevo = pid;
	mensaje mensaje;
	mensaje.mtype = IDENTIFICACION;
	mensaje.pid = nuevo;

	return mensaje;

}


