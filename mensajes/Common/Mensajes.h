#ifndef MENSAJES_H_
#define MENSAJES_H_
#define IDENTIFICACION 0
#define	INSERTAR	1
#define CONSULTAR	2
#define	RESPUESTA	3
#define NOMBRE_SIZE	61
#define DIRECCION_SIZE 120
#define TELEFONO_SIZE 13


typedef struct mensaje {
	long mtype;
	int id;
	char nombre[NOMBRE_SIZE];
	char direccion[DIRECCION_SIZE];
	char telefono[TELEFONO_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
