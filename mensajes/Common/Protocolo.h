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
	bool esMensajeAcaEstoy(mensaje m);
	bool esMensajeConsultar(mensaje m);
	bool esMensajeRespuesta(mensaje m);
	mensaje getMensajePeticion();
	mensaje getMensajeRespuesta();
	virtual ~Protocolo();
private:
	vector<string> entrada;
    void parsearEntrada(mensaje & peticion);
    void parsearEntradaInsertar(mensaje & peticion);
    void parsearEntradaConsultar(mensaje & peticion);
    void parsearEntradaModificar(mensaje & peticion);
	long getMType(const string& cmd);
	int getOp(const string& op);
	bool esComandoInsertar(const string& c);
	bool esComandoConsultar(const string& c);
	bool esComandoBorrar(const string& c);
	bool esComandoModificar(const string& c);
};

#endif /* PROTOCOLO_H_ */
