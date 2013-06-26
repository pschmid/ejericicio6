#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "../Common/Mensaje.h"
#include "../Common/Protocolo.h"
#include "../Common/Cola.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
#include "../Common/Signals/SignalHandler.h"
#include "../Common/Signals/SIGINT_Handler_Cliente.h"

using namespace std;

class Cliente {
private:
	Cola<mensaje>* colaEnvios;
	Cola<mensaje>* colaRecibos;
	SIGINT_Handler_Cliente sigint_handler;
	bool _salir;
	bool _servidorCerrado;
	void imprimirAyuda();
	bool esComandoAyuda(const string& c);
	bool esComandoSalir(const string& c);
	int enviarPeticion(mensaje);
	mensaje leerEntrada();
    void recibirRespuesta();
    bool chequearFinComunicacion();
	void registrarCierreServidor();
	void enviarMensajeAnuncio();
	void informarCierre();
	void registrarCierre();
	void setServidorCerrado(bool cerrado);
	bool servidorCerrado();
	void setSalir(bool salir);
	bool salir();
public:
	Cliente(char* archivo, char letra);
	void iniciar();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
