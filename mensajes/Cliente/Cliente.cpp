#include "Cliente.h"

Cliente::Cliente(char* archivo, char letra) {
	this->colaEnvios = new Cola<mensaje> (archivo, letra);
	this->colaRecibos = new Cola<mensaje> ((char *) COLA_CLIENTE, getpid());
	this->setSalir(false);
	this->setServidorCerrado(false);
}

Cliente::~Cliente() {
	this->colaRecibos->destruir();
	delete this->colaEnvios;
	delete this->colaRecibos;
}

void Cliente::enviarMensajeAnuncio(){
	mensaje acaEstoy;
	acaEstoy.mtype = ACA_ESTOY;
	acaEstoy.pid = getpid();
	acaEstoy.ttl =1;
	this->enviarPeticion(acaEstoy);
	this->recibirRespuesta();
}

void Cliente::registrarCierreServidor(){
	SignalHandler::getInstance()->registrarHandler( SIGINT, &sigint_handler );
}

void Cliente::iniciar() {
	this->enviarMensajeAnuncio();
	pid_t pid = fork ();
	if ( pid == 0 ) {
		this->chequearFinComunicacion();
		exit ( 0 );
	}else{
		this->registrarCierreServidor();

		cout << "Bienvenido al gestor de Base de Datos v1.0" << endl << endl;
		cout << "Ingrese el comando deseado por favor (help para ayuda)." << endl;
		mensaje peticion = this->leerEntrada();

		while (!this->salir()) {
			this->enviarPeticion(peticion);
			this->recibirRespuesta();
			peticion = this->leerEntrada();
		}

		cout<<"Fin aplicación cliente."<<endl;
		int estado;
		wait ( (void*) &estado );
	}
}

bool Cliente::chequearFinComunicacion(){
	mensaje respuesta;
	Protocolo protocolo;
	this->colaRecibos->leer(EXIT, &respuesta);
	if(respuesta.pid != getppid()){
		cout << "La comunicacion con el servidor se cerró. Ingrese cualquier tecla para salir." << endl;
		cin.get();
	}
	return true;
}

bool Cliente::esComandoAyuda(const string& c) {
	return c.compare("help") == 0 || c.compare("H") == 0;
}

bool Cliente::esComandoSalir(const string& c) {
	return c.compare("salir") == 0 || c.compare("S") == 0;
}

void Cliente::imprimirAyuda() {
	Protocolo protocolo;
	cout << protocolo.getAyuda();
}

void Cliente::setServidorCerrado(bool cerrado){
	this->sigint_handler.setServidorCerrado(cerrado);
}

bool Cliente::servidorCerrado(){
	return this->sigint_handler.servidorCerrado();
}

void Cliente::setSalir(bool salir) {
	this->_salir = salir;
}

bool Cliente::salir() {
	return this->_salir;
}

void Cliente::informarCierre(){
	mensaje respuesta;
	respuesta.mtype = EXIT;
	respuesta.ttl = 1;
	respuesta.pid = getpid();
	this->colaRecibos->escribir(respuesta);
}

mensaje Cliente::leerEntrada() {
	Protocolo protocolo;
	string entrada = "";
	do {
		cout << "> ";
		getline(cin, entrada);
		if(servidorCerrado()){
			break;
		}
		if (esComandoAyuda(entrada)) {
			this->imprimirAyuda();
		}
	} while (!protocolo.validarEntrada(entrada) && !esComandoSalir(entrada));

	if(esComandoSalir(entrada) || servidorCerrado()){
		this->informarCierre();
		this->setSalir(true);
		mensaje nulo;
		return nulo;
	}

	return protocolo.getMensajePeticion();
}

void Cliente::recibirRespuesta() {
	mensaje respuesta;
	Protocolo protocolo;
	bool quedanMensajes = true;
	while(quedanMensajes){
		this->colaRecibos->leer(RESPUESTA, &respuesta);
		if(strlen(respuesta.textoRespuesta) > 0){
			cout << respuesta.textoRespuesta << endl;
		} else {
			cout << "-----------------------------------------------------" << endl;
			cout << "Nombre: " << respuesta.nombre << endl;
			cout << "Direccion: " << respuesta.direccion << endl;
			cout << "Telefono: " << respuesta.telefono << endl;
			cout << "-----------------------------------------------------" << endl;
		}
		quedanMensajes = ( respuesta.ttl > 1 );
	}
}

int Cliente::enviarPeticion(mensaje peticion) {
	this->colaEnvios->escribir(peticion);
	return 0;
}
