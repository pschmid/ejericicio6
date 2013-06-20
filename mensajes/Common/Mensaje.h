#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <sys/types.h>
#include <unistd.h>

#define IDENTIFICACION 0
#define	INSERTAR	1
#define	ELIMINAR	2
#define	MODIFICAR	3
#define CONSULTAR	4
#define	RESPUESTA	5
#define SALIR		-1
#define NOMBRE_SIZE	61
#define DIRECCION_SIZE 120
#define TELEFONO_SIZE 13


typedef struct mensaje {
	long mtype;
	int pid;
	int ttl;
	char nombre[NOMBRE_SIZE];
	char direccion[DIRECCION_SIZE];
	char telefono[TELEFONO_SIZE];
} mensaje;


class Mensaje {
private:
	mensaje msj;
public:
	Mensaje();
	mensaje& getMensaje(){return this->msj;}
	void setMensaje(mensaje msj){this->msj=msj;}
	~Mensaje();
};

#endif /* MENSAJES_H_ */
