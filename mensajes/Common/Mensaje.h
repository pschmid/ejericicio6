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
#define EXIT		6
#define ACA_ESTOY    7
#define SALIR		-1
#define NOMBRE_SIZE	61
#define DIRECCION_SIZE 120
#define TELEFONO_SIZE 13
#define RESPUESTA_SIZE 120

typedef struct _mensaje {
	long mtype;
	int pid;
	int ttl;
	int op;
	char textoRespuesta[RESPUESTA_SIZE];
	char nombre[NOMBRE_SIZE];
	char direccion[DIRECCION_SIZE];
	char telefono[TELEFONO_SIZE];
	char nombreCons[NOMBRE_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
