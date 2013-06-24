#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include "../Common/Mensaje.h"
#include "../Common/Protocolo.h"
#include "../Common/Cola.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
#include "../Common/Signals/SignalHandler.h"

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
	mensaje leerEntrada();
    void recibirRespuesta();
    bool chequearFinComunicacion();
public:
	Cliente(char* archivo, char letra);
	void iniciar();
	void informarCierre();
	void setSalir(bool salir);
	bool salir();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
