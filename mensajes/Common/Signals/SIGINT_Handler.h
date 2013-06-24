#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include "../Constants.h"
#include "../Util.h"
#include "../Mensaje.h"
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>
#include <string.h>
#include <map>

using namespace std;

#include "EventHandler.h"
#include "../Cola.h"

class SIGINT_Handler : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;
		Cola<mensaje>* cola;
		map<int, Cola<mensaje>*> *clientes;
	public:

		SIGINT_Handler (Cola<mensaje>* cola,map<int, Cola<mensaje>*> *clientes) {
			this->clientes = clientes;
			this->cola = cola;
			this->gracefulQuit = 0;
		}

		~SIGINT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			cout << endl << "Cerrando servidor..." << endl;
			this->gracefulQuit = 1;
			this->cola->destruir();

			cout<<"Informando a clientes..."<<endl;
			// Responder
			mensaje respuesta;
			respuesta.mtype = EXIT;
			strcpy(respuesta.textoRespuesta, "La comunicacion con el servidor se cerró. Para finalizar ingrese 'salir' o 'S'.");
			respuesta.ttl = 1;
			for (map<int, Cola<mensaje> *>::iterator ii = clientes->begin() ;ii!= clientes->end(); ii++) {
				(*ii).second->escribir(respuesta);
			}
			return 0;
		}

		sig_atomic_t getGracefulQuit () {
			return this->gracefulQuit;
		}
};

#endif /* SIGINT_HANDLER_H_ */
