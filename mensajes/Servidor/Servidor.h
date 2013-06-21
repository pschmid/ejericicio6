#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <map>
#include <unistd.h>
using namespace std;

#include "../Common/Mensaje.h"
#include "../Common/Cola.h"
#include "../Common/Util.h"
#include "../Common/Constants.h"
#include "../Common/Protocolo.h"
#include "../Common/Signals/SIGINT_Handler.h"
#include "../Common/Signals/SignalHandler.h"
#include "BaseDeDatos.h"

class Servidor {
	private:
		Cola<mensaje>* cola;
		mensaje peticionRecibida;
		vector<mensaje> respuestas;
		BaseDeDatos bd;
		map<int, Cola<mensaje>*> clientes;
		vector<mensaje> getMensajesDeRespuestaConsulta(vector<Registro> registros);
		void consultarRegistros();
		void insertarRegistro();

	public:
		Servidor ( char* archivo,char letra );
		int recibirPeticion ();
		int procesarPeticion ();
		int responderPeticion (int);
		void iniciar();
		mensaje getPeticionRecibida ();
		vector<mensaje> getRespuesta ();
		mensaje getMensaje(int);
		virtual ~Servidor ();
};

#endif /* SERVIDOR_H_ */
