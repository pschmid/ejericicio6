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

using namespace std;

#include "Mensajes.h"
#include "Cola.h"
#include "MemoriaCompartida.h"

class Servidor {

	private:
		Cola<mensaje>* cola;
		mensaje peticionRecibida;
		mensaje respuesta;
		vector<mensaje> datos;
		map<int, Cola<mensaje>*> clientes;

	public:
		Servidor ( char* archivo,char letra );
		virtual ~Servidor ();

		int recibirPeticion ();
		int procesarPeticion ();
		int responderPeticion (int);
		void iniciar();

		mensaje getPeticionRecibida ();
		mensaje getRespuesta ();
		mensaje getMensaje(int);

};

#endif /* SERVIDOR_H_ */
