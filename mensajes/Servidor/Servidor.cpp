#include "Servidor.h"

Servidor :: Servidor ( char* archivo,char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Servidor :: ~Servidor () {
	delete this->cola;
}

int Servidor :: recibirPeticion () {
	this->peticionRecibida.id = 0;
	this->cola->leer ( INSERTAR,&(this->peticionRecibida) );
	//this->datos.push_back(this->peticionRecibida);
	return 0;
}

int Servidor :: procesarPeticion () {

	char txt_respuesta[100];

	strcpy ( txt_respuesta,"[Respuesta a ");
	strcat ( txt_respuesta,this->peticionRecibida.nombre );
	strcat ( txt_respuesta,"]" );

	this->respuesta.mtype = RESPUESTA;
	this->respuesta.id = this->peticionRecibida.id;
	strcpy ( this->respuesta.nombre,txt_respuesta );

	return 0;
}

int Servidor :: responderPeticion () {
	this->cola->escribir ( this->respuesta );
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
	int pid = fork();
	if ( pid == 0 ) {

		for ( int i=0;i<3;i++ ) {
			cout << "Servidor: esperando peticiones" << endl;
			recibirPeticion ();
			cout << "Servidor: peticion recibida: " << getPeticionRecibida().nombre << endl;
			procesarPeticion ();

			datos.push_back(getPeticionRecibida());
			cout << "Servidor: peticion procesada - enviando respuesta: " << getRespuesta().nombre << endl;
			responderPeticion ();
			cout << "Servidor: respuesta enviada" << endl << endl;


		}

		for(std::vector<mensaje>::size_type i = 0; i != datos.size(); i++) {
			cout << datos[i].nombre;
		}



	}

	int pid2 = fork();
	if (pid2 == 0){

	}
}

