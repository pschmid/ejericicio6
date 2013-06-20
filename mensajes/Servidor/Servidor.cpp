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
			cout <<"Se creo un nuevo cliente en la base de datos (DEBUG: PID "<< clientPid << ")"<<endl;
			nuevoCliente = new Cola<mensaje> ((char *) COLA_CLIENTE ,clientPid);
			clientes[clientPid] = nuevoCliente;
		}

		Registro reg;
		reg.crearDesdeMensaje(peticionRecibida);
		this->bd.insertar(reg);

		char txt_respuesta[100];

		strcpy ( txt_respuesta,"[Respuesta a ");
		strcat ( txt_respuesta,Util().itoa(clientPid).c_str() );
		strcat ( txt_respuesta,"]" );

		mensaje respuesta;

		respuesta.ttl=1;
		respuesta.mtype = RESPUESTA;
		respuesta.pid = getpid();
		strcpy ( respuesta.nombre,txt_respuesta );
		this->respuesta.push_back(respuesta);

	} else if (protocolo.esMensajeConsultar(peticionRecibida)){
		Registro reg;
		reg.crearDesdeMensaje(peticionRecibida);
		this->consultarLaBase(reg);
		// Consultar a la base
	} else {
		//Devolver respuesta con error
	}



	return clientPid;
}

int Servidor :: responderPeticion (int pidCliente) {

	for( vector<mensaje>::iterator ii=respuesta.begin(); ii!=respuesta.end(); ii++) {
		clientes[pidCliente]->escribir((*ii));
	}
	respuesta.clear();
	return 0;
}
//este metodo debe crear los mensajes con los registros y en ttl(time to leave)
//debe poner la cantidad de registros que faltan enviar.
//ej: si debo enviar 3 mensajes de respuesta, el primero poner ttl=3, el segundo ttl=2
// y el tercero ttl=1. de esta manera el cleitne cuando lee el de ttl=1 deja de leer.
vector<mensaje> Servidor :: getMensajesFromRegisters(vector<Registro> registros){
	mensaje msg;
	vector<mensaje> mensajes;
	int cantRegs = registros.size();
	cout << "cantidad de registros en la base "<<cantRegs;
	for(vector<Registro>::iterator it=registros.begin(); it!=registros.end();it++){
		msg = (*it).crearMensajeAsociado();
		msg.ttl = cantRegs--;
		msg.mtype = RESPUESTA;
		msg.pid = getpid();
		mensajes.push_back(msg);
	}
	return mensajes;
}

void Servidor :: consultarLaBase(Registro registro){

	vector<Registro> resultado = this->bd.consultar(registro);
	this->respuesta = this->getMensajesFromRegisters(resultado);

}

mensaje Servidor :: getPeticionRecibida () {
	return this->peticionRecibida;
}

vector<mensaje> Servidor :: getRespuesta () {
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
	for ( int i=0;i<10;i++ ) {
		cout << "Servidor: esperando peticiones" << endl;
		recibirPeticion ();
		cout << "Servidor: peticion recibida: " << endl;
		procesarPeticion ();

		//datos.push_back(getPeticionRecibida());
		cout << "Servidor: peticion procesada - enviando respuesta: " << endl;
		responderPeticion (getPeticionRecibida().pid);
		cout << "Servidor: respuesta enviada" << endl;
	}
}

