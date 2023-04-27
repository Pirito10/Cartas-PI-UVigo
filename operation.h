// Fichero de cabecera del modulo Gestor de Operaciones

#ifndef OPERATION_H
#define OPERATION_H

#include "inout.h" //Se necesita para usar la declaracion de las estructuras unAbonado y unMensaje

// Declaraciones de las funciones incluidas en operation.c

void fichero_Abonados(struct unAbonado **listaAbonados);
void fichero_Mensajes(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);
void suscribir(struct unAbonado **lista);
void escribir(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);
void listar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);
void borrar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);
void retirar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);
void salir(int *respuesta, struct unAbonado **listaAbonados, struct unMensaje **listaMensajes);

#endif