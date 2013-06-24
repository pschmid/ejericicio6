#include "Cliente.h"

Cliente::Cliente(char* archivo, char letra) {
	this->colaEnvios = new Cola<mensaje> (archivo, letra);
	this->colaRecibos = new Cola<mensaje> ((char *) COLA_CLIENTE, getpid());
	this->_salir = false;
	mensaje acaEstoy;
	acaEstoy.mtype = ACA_ESTOY;
	acaEstoy.pid = getpid();
	acaEstoy.ttl =1;
	this->colaEnvios->escribir(acaEstoy);
	this->recibirRespuesta();

}

Cliente::~Cliente() {
	this->colaRecibos->destruir();
	delete this->colaEnvios;
	delete this->colaRecibos;
}

void Cliente::iniciar() {
//	SIGINT_Client_Handler sigint_client_handler(this->colaRecibos);
//	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_client_handler );
	int salida = 0;
	pid_t pid = fork ();


	if ( pid == 0 ) {
		this->chequearFinComunicacion();
		exit ( 0 );
	}else{

	cout << "Bienvenido al gestor de Base de Datos v1.0" << endl << endl;
	cout << "Ingrese el comando deseado por favor (help para ayuda)." << endl;
	mensaje peticion = this->leerEntrada();
	while (!this->salir()) {
			this->enviarPeticion(peticion);
			this->recibirRespuesta();
			peticion = this->leerEntrada();
	}
	cout<<"termino cliente"<<endl;
	int estado;
	wait ( (void*) &estado );
	}
}








bool Cliente::esComandoSalir(const string& c) {
	return c.compare("salir") == 0 || c.compare("S") == 0;
}

bool Cliente::chequearFinComunicacion(){

	mensaje respuesta;
	Protocolo protocolo;
	bool quedanMensajes = true;
    while(quedanMensajes){
		this->colaRecibos->leer(EXIT, &respuesta);
		cout << "La comunicacion con el servidor se cerró" << endl;
		cout << "para finalizar ingrese 'salir'" << endl;
		quedanMensajes = ( respuesta.ttl > 1 );
	}

    return true;

}

bool Cliente::esComandoAyuda(const string& c) {
	return c.compare("help") == 0 || c.compare("H") == 0;
}

void Cliente::imprimirAyuda() {
	cout << "Comandos disponibles" << endl;
	cout << "- insertar(I) " << endl;
	cout << "	Sintaxis: insertar/I -t <telefono> -n <nombre> -d <direccion> (orden indistinto)" << endl << endl;
	cout << "- consultar(C)" << endl;
	cout << "	Sintaxis: consultar/C -n <nombre>" << endl << endl;
	cout << "- salir(S)" << endl;
	cout << "- help(H)" << endl << endl;
}

void Cliente::setSalir(bool salir) {
	this->_salir = salir;
}

bool Cliente::salir() {
	return this->_salir;
}

mensaje Cliente::leerEntrada() {
	Protocolo protocolo;
	string entrada = "";
	bool val, sal;
	do {
		cout << "> ";
		getline(cin, entrada);

		if (esComandoAyuda(entrada)) {
			this->imprimirAyuda();
		}
		val = protocolo.validarEntrada(entrada);
		sal = esComandoSalir(entrada);
		if(this->_salir==true)
			sal=true;
		cout<<"salir = "<< this->salir()<<endl;

	} while (!val && !sal);

	if (esComandoSalir(entrada) || this->_salir==true) {
		if(esComandoSalir(entrada)){
			// Responder mensaje de cierre dummy
			mensaje respuesta;
			respuesta.mtype = EXIT;
			respuesta.ttl = 1;
			this->colaRecibos->escribir(respuesta);
		}

		this->setSalir(true);
		mensaje nulo;
		return nulo;
	}
	return protocolo.getMensajePeticion();
}

void Cliente::recibirRespuesta()
{
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
