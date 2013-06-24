#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include "../Constants.h"
#include "../Util.h"
#include "../Mensaje.h"
#include <sys/wait.h>
#include <string>
#include <iostream>
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
			// Mando señal a cada cliente

			// Responder
			mensaje respuesta;
			respuesta.mtype = EXIT;
			respuesta.ttl = 1;
			int resultado;
			for (map<int, Cola<mensaje> *>::iterator ii = clientes->begin() ;ii!= clientes->end(); ii++) {
				(*ii).second->escribir(respuesta);
			}

			cout<<"fin señales a clientes"<<endl;
			return 0;
		}


		sig_atomic_t getGracefulQuit () {
			return this->gracefulQuit;
		}
};

#endif /* SIGINT_HANDLER_H_ */
