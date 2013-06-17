#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include "../Common/Mensajes.h"
#include "../Common/Cola.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
#include "../Common/MensajeFactory.h"

using namespace std;

class Cliente {

	private:
		Cola<mensaje>* colaEnvios;
		Cola<mensaje>* colaRecibos;

	public:
		Cliente (char* archivo,char letra );
		virtual ~Cliente();
		mensaje enviarPeticion ( mensaje);
		mensaje recibirEntrada();
		mensaje armarHeader(long ,vector<string>);
		void iniciarComunicacion();
};

#endif /* CLIENTE_H_ */
