#include "Cliente.h"

Cliente::Cliente(char* archivo, char letra) {
	this->colaEnvios = new Cola<mensaje> (archivo, letra);
	this->colaRecibos = new Cola<mensaje> ((char *) COLA_CLIENTE, getpid());
}

Cliente::~Cliente() {
	this->colaRecibos->destruir();
	delete this->colaEnvios;
	delete this->colaRecibos;
}

void Cliente::iniciarComunicacion() {
	//	this->colaEnvios->escribir ( MensajeFactory().crearMensajeAviso(getpid()) );
	//	cout<<" soy cliente con pid "<< getpid()<<endl;
	//
	//	mensaje respuesta;
	//	this->colaRecibos->leer ( RESPUESTA,&respuesta );
	//	cout<<"respuesta obtenida"<<endl;
	//
	//	cout << "Cliente: respuesta recibida = (ID = " << respuesta.pid << ") - " << endl;
	cout << "Bienvenido al gestor de Base de Datos v1.0" << endl << endl;
	cout << "Ingrese el comando deseado por favor (help para ayuda)." << endl;

	mensaje peticion = this->recibirEntrada();
	while (!this->salir()) {
		this->enviarPeticion(peticion);
		peticion = this->recibirEntrada();
	}
}

bool Cliente::esComandoSalir(const string& c) {
	return c.compare("salir") == 0 || c.compare("S") == 0;
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

mensaje Cliente::recibirEntrada() {
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
	} while (!val && !sal);

	if (esComandoSalir(entrada)) {
		this->setSalir(true);
		mensaje nulo;
		return nulo;
	}

	return protocolo.getMensajePeticion();
}

int Cliente::enviarPeticion(mensaje peticion) {

	mensaje respuesta;

	this->colaEnvios->escribir(peticion);
	this->colaRecibos->leer(RESPUESTA, &respuesta);
	cout<<" paquete recibido numero "<<respuesta.ttl<<endl;
	cout << "Cliente: respuesta recibida = (ID = " << respuesta.pid << ") - "	<< respuesta.nombre << endl;

	while(respuesta.ttl > 1){
		this->colaRecibos->leer(RESPUESTA, &respuesta);
		cout<<" paquete recibido numero "<<respuesta.ttl<<endl;
		cout << "Cliente: respuesta recibida = (ID = " << respuesta.pid << ") - "	<< respuesta.nombre << endl;
	}

	return 0;
}
