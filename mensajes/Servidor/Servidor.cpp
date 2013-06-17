#include "Servidor.h"

Servidor :: Servidor ( char* archivo,char letra ) {
	this->cola = new Cola<mensaje> ( (char*)COLA_SERVIDOR,letra );
}

Servidor :: ~Servidor () {
	delete this->cola;
}

int Servidor :: recibirPeticion () {

	mensaje recibido;
	recibido.pid = 0;
	this->cola->leer ( IDENTIFICACION,&recibido );

	cout<<"nombre "<<recibido.nombre<<endl;
	cout<<"tel"<<recibido.telefono<<endl;

	cout<<"dir "<<recibido.direccion<<endl;
	cout<<"pid"<<recibido.pid<<endl;
	cout<<"id"<<recibido.id<<endl;
	//this->datos.push_back(this->peticionRecibida);
	return 0;
}

int Servidor :: procesarPeticion () {

	cout<<"nombre "<<this->peticionRecibida.nombre<<endl;
	cout<<"tel"<<this->peticionRecibida.telefono<<endl;

	cout<<"dir "<<this->peticionRecibida.direccion<<endl;
	cout<<"pid"<<this->peticionRecibida.pid<<endl;

	Cola<mensaje>* nuevoCliente;
	int clientPid = this->peticionRecibida.pid;
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
	this->respuesta.pid = getpid();
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
		responderPeticion (getPeticionRecibida().pid);
		cout << "Servidor: respuesta enviada" << endl << endl;

	}

}

