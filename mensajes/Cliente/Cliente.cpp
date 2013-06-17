#include "Cliente.h"

Cliente :: Cliente ( char* archivo,char letra ) {
	this->colaEnvios = new Cola<mensaje> ((char *) COLA_SERVIDOR,letra );
	this->colaRecibos = new Cola<mensaje> ((char *) COLA_CLIENTE ,getpid());
	this->iniciarComunicacion();
}

Cliente :: ~Cliente() {
	this->colaEnvios->destruir ();
	this->colaRecibos->destruir();
	delete this->colaEnvios;
	delete this->colaRecibos;
}

void Cliente::iniciarComunicacion(){
	mensaje peticion = MensajeFactory().crearMensajeAviso();

	this->colaEnvios->escribir ( peticion );

	cout<<" soy cliente con pid "<< getpid()<<"y "<<peticion.pid<<endl;

}

mensaje Cliente :: recibirEntrada(){

	string input = "";
	long mtype = 1;
	bool leerEntrada = true;
	vector <string> entrada;

	while(leerEntrada){
		input.clear();
		entrada.clear();

		while(input.empty()){
			getline(cin, input);
			cout << "You entered: " << input.size() << endl;
		}


		cout << "You entered: " << input << endl;

		input+= SEPARADOR;

		entrada =  Util().split(input, SEPARADOR);

		if(entrada[0].compare("insertar")==0 || entrada[0].compare("consultar")==0){
			leerEntrada = false;
			cout << "para "<< entrada[0] << endl;
		}
	}
	return this->armarHeader(mtype,entrada);


}

mensaje Cliente :: armarHeader(long mtype,vector<string> entrada){

	mensaje peticion;
	if(entrada[0].compare("insertar")==0){
		mtype = INSERTAR;
		cout << "para insertar" << endl;
	}else if (entrada[0].compare("consultar")==0){
		mtype = CONSULTAR;
		cout << "para consultar" << endl;
	}

	peticion.mtype = mtype;

	for (int i = 1; i < (int)entrada.size(); i++) {

		cout << "valor de entrada " << i << "  "<<entrada[i] <<endl;

		if(entrada[i].compare("-n")==0){
			unsigned int j=i;
			string nombre = "";
			while(j<entrada.size()-1){
				if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-d")==0){
					break;
				}
				nombre+=entrada[j+1]+SEPARADOR;
				j++;
			}

			strcpy(peticion.nombre,nombre.c_str());
		}
		if(entrada[i].compare("-d")==0){
					unsigned int j=i;
					string direccion = "";
					while(j<entrada.size()-1){
						if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-n")==0){
							break;
						}
						direccion+=entrada[j+1]+SEPARADOR;
						j++;
					}
					strcpy(peticion.direccion,direccion.c_str());
				}
		if(entrada[i].compare("-t")==0){
					unsigned int j=i;
					string telefono = "";
					while(j<entrada.size()-1){
						if(entrada[j+1].compare("-t")==0 || entrada[j+1].compare("-d")==0){
							break;
						}
						telefono+=entrada[j+1]+SEPARADOR;
						j++;
					}
					strcpy(peticion.telefono,telefono.c_str());
				}

	}
	cout << "nombre "<< peticion.nombre <<endl;
	cout << "dir "<< peticion.direccion <<endl;
	cout << "tel "<< peticion.telefono <<endl;
	return peticion;

}

mensaje Cliente :: enviarPeticion ( mensaje peticion ) {

	mensaje respuesta;

	this->colaEnvios->escribir ( peticion );
	this->colaRecibos->leer ( RESPUESTA,&respuesta );

	return respuesta;
}
