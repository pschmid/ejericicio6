#include "Servidor.h"

Servidor :: Servidor ( char* archivo,char letra ) {
	this->cola = new Cola<mensaje> ( (char*)COLA_SERVIDOR,letra );
}

Servidor :: ~Servidor () {
	delete this->cola;
}

int Servidor :: recibirPeticion () {

	this->cola->leer ( IDENTIFICACION,&(this->peticionRecibida) );
	//this->datos.push_back(this->peticionRecibida);
	return 0;
}

int Servidor :: procesarPeticion () {

	Cola<mensaje>* nuevoCliente;
	int clientPid = this->peticionRecibida.id;
	bool encontrado = false;

	for( map<int,Cola<mensaje>*>::iterator ii=clientes.begin(); ii!=clientes.end(); ++ii)
	   {
		if((*ii).first == clientPid){
	       cout <<"clave y pid del cleinte en mapa"<< (*ii).first <<endl;
	       encontrado = true;
	       break;
	   }
	   }

	if(encontrado == false){
		   cout <<"nuevo cliente con pid "<< clientPid <<endl;
		   nuevoCliente = new Cola<mensaje> ((char *) COLA_CLIENTE ,clientPid);
		   clientes[clientPid] = nuevoCliente;
	}


	char txt_respuesta[100];

	strcpy ( txt_respuesta,"[Respuesta a ");
	strcat ( txt_respuesta,Util().itoa(clientPid).c_str() );
	strcat ( txt_respuesta,"]" );

	this->respuesta.mtype = RESPUESTA;
	this->respuesta.id = getpid();
	strcpy ( this->respuesta.nombre,txt_respuesta );

	return clientPid;
}

int Servidor :: responderPeticion (int pidCliente) {
	clientes[pidCliente]->escribir(this->respuesta);
	return 0;
}

mensaje Servidor :: getPeticionRecibida () {
	return this->peticionRecibida;
}

mensaje Servidor :: getRespuesta () {
	return this->respuesta;
}

mensaje Servidor ::getMensaje(int id){
	mensaje a;
	return a;
}

void Servidor ::iniciar(){
	for ( int i=0;i<3;i++ ) {
		cout << "Servidor: esperando peticiones" << endl;
		recibirPeticion ();
		cout << "Servidor: peticion recibida: " << getPeticionRecibida().nombre << endl;
		procesarPeticion ();

		datos.push_back(getPeticionRecibida());
		cout << "Servidor: peticion procesada - enviando respuesta: " << getRespuesta().nombre << endl;
		responderPeticion (getPeticionRecibida().id);
		cout << "Servidor: respuesta enviada" << endl << endl;

	}

}

