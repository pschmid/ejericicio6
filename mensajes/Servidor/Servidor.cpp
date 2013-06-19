#include "Servidor.h"

Servidor :: Servidor ( char* archivo,char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Servidor :: ~Servidor () {
	this->cola->destruir();
	delete this->cola;
}

int Servidor :: recibirPeticion () {
	this->cola->leer ( IDENTIFICACION, &(this->peticionRecibida) );
	//this->datos.push_back(this->peticionRecibida);
	return 0;
}

int Servidor :: procesarPeticion () {
	Protocolo protocolo;
	int clientPid = -1;

	if (protocolo.esMensajeInsertar(peticionRecibida)){
		Cola<mensaje>* nuevoCliente;

		clientPid = this->peticionRecibida.pid;
		bool encontrado = false;

		for( map<int,Cola<mensaje>*>::iterator ii=clientes.begin(); ii!=clientes.end(); ++ii) {
			if((*ii).first == clientPid){
				cout <<"El usuario ya existe en la base de datos (DEBUG: PID "<< (*ii).first << ")" << endl;
				encontrado = true;
				break;
			}
		}

		if(encontrado == false){
			Registro reg;
			reg.crearDesdeMensaje(peticionRecibida);
			this->bd.insertar(reg);
			cout <<"Se creo un nuevo cliente en la base de datos (DEBUG: PID "<< clientPid << ")"<<endl;
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

	} else if (protocolo.esMensajeConsultar(peticionRecibida)){
		// Consultar a la base
	} else {
		//Devolver respuesta con error
	}



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

mensaje Servidor :: getMensaje(int id){
	mensaje a;
	return a;
}

void Servidor ::iniciar(){
//	SIGINT_Handler sigint_handler;
//	SignalHandler :: getInstance()->registrarHandler( SIGINT, &sigint_handler );
//	while (sigint_handler.getGracefulQuit() == 0) {
	//FIXME crear un handler para sigint y asi salir del servidor limpiamente con Ctrl+C
	for ( int i=0;i<3;i++ ) {
		cout << "Servidor: esperando peticiones" << endl;
		recibirPeticion ();
		cout << "Servidor: peticion recibida: " << endl;
		procesarPeticion ();

		//datos.push_back(getPeticionRecibida());
		cout << "Servidor: peticion procesada - enviando respuesta: " << getRespuesta().nombre << endl;
		responderPeticion (getPeticionRecibida().pid);
		cout << "Servidor: respuesta enviada" << endl;
	}
}

