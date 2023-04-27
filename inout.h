// Fichero de cabecera del modulo Entrada/Salida

#ifndef INOUT_H
#define INOUT_H

// Estructura para almacenar los datos de un abonado

struct unAbonado
{
	int identidad;
	int cuenta;
	char nombre[16];
	struct unAbonado *sig;
};

// Estructura para almacenar los datos de un mensaje

struct unMensaje
{
	int emisor;
	int destinatario;
	char texto[101];
	struct unMensaje *sig;
};

// Declaraciones de las funciones incluidas en inout.c

void plano(char caracter, int n);
void rotulo(char nombre[], char caracter, int n);
int confirmar(char mensaje[]);
void lee_cadena(char *direccion_Cadena, int longitud, char mensaje[]);
int lee_entero(int valor_Max, char mensaje[]);
void muestra_abonado(struct unAbonado *elAbonado);
void muestra_extensa(struct unMensaje *elMensaje);
void muestra_corta(struct unMensaje *elMensaje);

#endif