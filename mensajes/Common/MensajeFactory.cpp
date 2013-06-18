/*
 * MensajeFactory.cpp
 *
 *  Created on: 27/11/2012
 *      Author: martin
 */

#include "MensajeFactory.h"

MensajeFactory::MensajeFactory() {

}

mensaje MensajeFactory::crearMensajeAviso(){
	mensaje mensaje;
	mensaje.mtype = IDENTIFICACION;
	strcpy(mensaje.pid,Util().itoa(getpid()).c_str());

	return mensaje;

}


