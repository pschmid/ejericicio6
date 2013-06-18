/*
 * MensajeFactory.h
 *
 *  Created on: 27/11/2012
 *      Author: martin
 */

#ifndef MENSAJEFACTORY_H_
#define MENSAJEFACTORY_H_

#include "Mensajes.h"
#include "Util.h"
#include "unistd.h"
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>


class MensajeFactory {

public:
	MensajeFactory();
	static mensaje crearMensajeAviso();
	static mensaje crearMensajeRespuesta();

};

#endif /* MENSAJEFACTORY_H_ */

