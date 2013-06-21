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

using namespace std;

#include "EventHandler.h"
#include "../Cola.h"

class SIGINT_Handler : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;
		Cola<mensaje>* cola;
	public:

		SIGINT_Handler (Cola<mensaje>* cola) {
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
			return 0;
		}

		sig_atomic_t getGracefulQuit () {
			return this->gracefulQuit;
		}
};

#endif /* SIGINT_HANDLER_H_ */
