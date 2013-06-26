#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <sys/wait.h>
#include <assert.h>
#include "EventHandler.h"
#include "../../Cliente/Cliente.h"

using namespace std;

class SIGINT_Handler_Cliente : public EventHandler {
	private:
		bool cerrado;
	public:
		SIGINT_Handler_Cliente () {
			this->cerrado = false;
		}

		~SIGINT_Handler_Cliente () {}

		bool servidorCerrado(){
			return this->cerrado;
		}

		void setServidorCerrado(bool cerrado){
			this->cerrado = cerrado;
		}

		virtual int handleSignal ( int signum ) {
			assert( signum == SIGINT );
			this->cerrado = true;
			return 0;
		}
};

#endif /* SIGINT_HANDLER_H_ */
