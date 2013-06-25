#include "Servidor.h"

Servidor::Servidor(char* archivo, char letra) {
	this->cola = new Cola<mensaje> (archivo, letra);
}

Servidor::~Servidor() {
	this->cola->destruir();
	delete this->cola;
}

int Servidor::recibirPeticion() {
	int result = this->cola->leer(IDENTIFICACION, &(this->peticionRecibida));
	if (result != -1){
		cout << "Peticion recibida" << endl;
	}
	return 0;
}

void Servidor::modificarRegistro() {
	Protocolo protocolo;
	string resp;

	/* Insertar en la base de datos */
	Registro existReg(peticionRecibida.nombre, (char*) "", (char*) "");
	Registro nuevoReg;
	nuevoReg.crearDesdeMensaje(peticionRecibida);

	int result = this->bd.modificar(existReg, nuevoReg);
	if (result == SUCCESS){
		resp = "El registro ha sido insertado con éxito con la siguiente información.";
		resp += "\nNombre: " + nuevoReg.getNombre();
		resp += "\nDirección: " + nuevoReg.getDireccion();
		resp += "\nTeléfono: " + nuevoReg.getTelefono();
		resp += "\n";
	} else if (result == ERR_NO_EXISTE){
		resp = "El registro a modificar no existe. ";
	} else if (result == ERR_DUPLICADO){
		resp = "El registro no se ha modificado con éxito pues está en conflicto con otro existente.";
	} else if (result == ERR_CAMPO_REQUERIDO){
		resp = "El registro no se ha modificado con éxito pues faltan datos requeridos.";
	}

	/* Generar respuesta */
	mensaje respuesta;
	respuesta.ttl = 1;
	respuesta.mtype = RESPUESTA;
	respuesta.pid = getpid();
	strcpy(respuesta.textoRespuesta, resp.c_str());
	this->respuestas.push_back(respuesta);
}

void Servidor::insertarRegistro() {
	Protocolo protocolo;
	string resp;
	/* Insertar en la base de datos */
	Registro reg;
	reg.crearDesdeMensaje(peticionRecibida);
	int result = this->bd.insertar(reg);
	if (result == SUCCESS){
		resp = "El registro ha sido insertado con éxito con la siguiente información.";
		resp += "\nNombre: " + reg.getNombre();
		resp += "\nDirección: " + reg.getDireccion();
		resp += "\nTeléfono: " + reg.getTelefono();
		resp += "\n";
	} else if (result == ERR_DUPLICADO){
		resp = "El registro no se ha insertado con éxito pues está duplicado";
	} else if (result == ERR_CAMPO_REQUERIDO){
		resp = "El registro no se ha insertado con éxito pues faltan datos requeridos.";
	}

	/* Generar respuesta */
	mensaje respuesta;
	respuesta.ttl = 1;
	respuesta.mtype = RESPUESTA;
	respuesta.pid = getpid();
	strcpy(respuesta.textoRespuesta, resp.c_str());
	this->respuestas.push_back(respuesta);
}

int Servidor::procesarPeticion() {
	int clientPid = this->peticionRecibida.pid;
	Protocolo protocolo;
	if (protocolo.esMensajeInsertar(peticionRecibida)) {
		cout << "Procesando insertar registro." << endl;
		this->insertarRegistro();
	} else if (protocolo.esMensajeConsultar(peticionRecibida)) {
		cout << "Procesando consultar registros." << endl;
		this->consultarRegistros();
	} else if (protocolo.esMensajeModificar(peticionRecibida)){
		this->modificarRegistro();
	} else if (protocolo.esMensajeAcaEstoy(peticionRecibida)){
		//nuevo cliente
		Cola<mensaje> *nuevoCliente;
		int pidCliente = peticionRecibida.pid;
		nuevoCliente = new Cola<mensaje> ((char *) COLA_CLIENTE, pidCliente);
		clientes[pidCliente] = nuevoCliente;
		this->respuestas = this->responderAcaEstoy();
	}else{
		//FIXME Responder algún error
	}

	return clientPid;
}

vector<mensaje> Servidor::responderAcaEstoy(){
		mensaje respuesta;
		vector<mensaje> mensajes;
		string resp;
		int ttl = 1;
		resp = "Aca estoy recibido.\n";
		respuesta.mtype = RESPUESTA;
		respuesta.ttl = ttl;
		respuesta.pid = getpid();
		strcpy(respuesta.textoRespuesta, resp.c_str());
		mensajes.push_back(respuesta);
		return mensajes;
}

int Servidor::responderPeticion(int pidCliente) {
	// Seleccionar cola de mensajes en la cual responder
	Cola<mensaje> *nuevoCliente;
	map<int, Cola<mensaje> *>::iterator found = clientes.find(pidCliente);
	if (found == clientes.end()){
		nuevoCliente = new Cola<mensaje> ((char *) COLA_CLIENTE, pidCliente);
		clientes[pidCliente] = nuevoCliente;
	}
	// Responder
	int resultado;
	for (vector<mensaje>::iterator ii = respuestas.begin(); ii	!= respuestas.end(); ii++) {
		resultado = clientes[pidCliente]->escribir((*ii));
	}
	if (resultado != -1){
		cout << "Respuesta enviada." << endl<< endl;
	}
	respuestas.clear();
	return 0;
}

vector<mensaje> Servidor::getMensajesDeRespuestaConsulta(vector<Registro> registros) {
	mensaje respuesta;
	Protocolo protocolo;
	vector<mensaje> mensajes;
	string resp;
	int ttl = registros.size() + 1;

	/* Primer mensaje para mostrar */
	if (!registros.empty()) {
		resp = "Su consulta arrojó los siguientes (";
		resp += Util::itoa(registros.size());
		resp += ") resultados:\n";
	} else {
		resp = "Su consulta no arrojó ningún resultado.\n";
	}
	respuesta.mtype = RESPUESTA;
	respuesta.ttl = ttl--;
	respuesta.pid = getpid();
	strcpy(respuesta.textoRespuesta, resp.c_str());
	mensajes.push_back(respuesta);

	/* Mensajes de respuesta */
	for (vector<Registro>::iterator it = registros.begin(); it != registros.end(); it++) {
		respuesta = (*it).crearMensajeAsociado();
		respuesta.ttl = ttl--;
		respuesta.mtype = RESPUESTA;
		respuesta.pid = getpid();
		mensajes.push_back(respuesta);
	}
	return mensajes;
}

void Servidor::consultarRegistros() {
	Registro registroDeConsulta;
	registroDeConsulta.crearDesdeMensaje(peticionRecibida);
	vector<Registro> resultados = this->bd.consultar(registroDeConsulta, peticionRecibida.op);
	this->respuestas = this->getMensajesDeRespuestaConsulta(resultados);
}

mensaje Servidor::getPeticionRecibida() {
	return this->peticionRecibida;
}

vector<mensaje> Servidor::getRespuesta() {
	return this->respuestas;
}

mensaje Servidor::getMensaje(int id) {
	mensaje a;
	return a;
}

void Servidor::iniciar() {
	SIGINT_Handler sigint_handler(this->cola,&this->clientes);
	SignalHandler::getInstance()->registrarHandler( SIGINT, &sigint_handler );
	while (sigint_handler.getGracefulQuit() == 0) {
		cout << "Esperando peticiones." << endl;
		recibirPeticion();
		procesarPeticion();
		responderPeticion(getPeticionRecibida().pid);
	}
	cout << "El servidor ha dejado de recibir peticiones." << endl;
}

