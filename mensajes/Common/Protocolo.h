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

#define CANT_PARAMS 5

using namespace std;

class Protocolo {
public:
	Protocolo();
	bool validarEntrada(const string& s);
	bool esMensajeInsertar(mensaje m);
	bool esMensajeAcaEstoy(mensaje m);
	bool esMensajeConsultar(mensaje m);
	bool esMensajeRespuesta(mensaje m);
	bool esMensajeModificar(mensaje m);
	mensaje getMensajePeticion();
	mensaje getMensajeRespuesta();
	static int getOp(const string& op);
	string getAyuda();
	virtual ~Protocolo();
private:
	vector<string> entrada;
	string params[CANT_PARAMS];
	void (*actions[CANT_PARAMS])(mensaje&, const string& val);
 	long getMType(const string& cmd);
	void inicializarPeticion(mensaje& peticion);
	bool esComandoInsertar(const string& c);
	bool esComandoConsultar(const string& c);
	bool esComandoBorrar(const string& c);
	bool esComandoModificar(const string& c);
	int posParametro(const string& s);
	void completarCampo(mensaje& peticion, int pos, const string& valor);
};

#endif /* PROTOCOLO_H_ */
