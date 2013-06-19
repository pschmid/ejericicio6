/*
 * Protocolo.h
 *
 *  Created on: 17/06/2013
 *      Author: gonzalo
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include "Mensaje.h"
#include "Util.h"
#include "Constants.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Protocolo {
public:
	Protocolo();
	bool validarEntrada(const string& s);
	bool esMensajeInsertar(mensaje m);
	bool esMensajeConsultar(mensaje m);
	mensaje getMensajePeticion();
	mensaje getMensajeRespuesta();
	virtual ~Protocolo();
private:
	vector<string> entrada;
	long getMType(const string& cmd);
	bool esComandoInsertar(const string& c);
	bool esComandoConsultar(const string& c);
};

#endif /* PROTOCOLO_H_ */
