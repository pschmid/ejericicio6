#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Mensajes.h"
#include "Cola.h"
#include "Common/Util.h"
#include "Common/Constants.h"

class Cliente {

	private:
		Cola<mensaje>* cola;

	public:
		Cliente ( char* archivo,char letra );
		virtual ~Cliente();
		mensaje enviarPeticion ( mensaje);
		mensaje recibirEntrada();
		mensaje armarHeader(long ,vector<string>);
};

#endif /* CLIENTE_H_ */
