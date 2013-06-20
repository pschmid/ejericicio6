#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include "../Common/Mensaje.h"
#include "../Common/Protocolo.h"
#include "../Common/Cola.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
#include "../Common/MensajeFactory.h"

using namespace std;

class Cliente {
private:
	Cola<mensaje>* colaEnvios;
	Cola<mensaje>* colaRecibos;
	bool _salir;
	void imprimirAyuda();
	bool esComandoAyuda(const string& c);
	bool esComandoSalir(const string& c);
	int enviarPeticion(mensaje);
	mensaje recibirEntrada();
public:
	Cliente(char* archivo, char letra);
	void iniciarComunicacion();
	void setSalir(bool salir);
	bool salir();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
