// Modulo principal

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inout.h"
#include "operation.h"

// Funcion que muestra el menu y realiza todas las llamadas a las demas funciones del programa
int main()
{
	int respuesta;	   // Variable para controlar la finalizacion del programa
	char cadena[3], c; // Variables para controlar el menu

	// Lista de los registros de los abonados
	struct unAbonado *listaAbonados;
	// Lista de los registros de los mensajes
	struct unMensaje *listaMensajes;

	// En un principio, las listas estan vacias
	listaAbonados = NULL;
	listaMensajes = NULL;

	// Se leen los ficheros de textos proporcionados y se copia, si existe, su informacion a las respectivas listas
	fichero_Abonados(&listaAbonados);
	fichero_Mensajes(&listaAbonados, &listaMensajes);

	// Se imprime la caratula, de tamaño 60, nombre "CARTAS" y con el borde formado por el caracter '+'
	plano('+', 60);
	rotulo("CARTAS", '+', 60);
	plano('+', 60);

	// Se muestra el menu principal
	do
	{
		printf("\nA) Dar de alta a un abonado\nE) Escribir un mensaje\nL) Listar los mensajes para un abonado\nB) Borrar un mensaje\nJ) Dar de baja a un abonado\n\nS) Salir del programa\n\nElige una opcion: ");

		// Se pide al usuario la opcion que desea ejecutar, y se asigna a una cadena de dos caracteres mas el '\0'
		fgets(cadena, 3, stdin);

		// Si el ultimo elemento de la cadena, sin incluir el '\0', es un salto de linea, se introdujo una entrada correcta
		if (cadena[1] == '\n')
		{
			// Se pasa a minuscula el primer caracter (la letra) introducido
			c = tolower(cadena[0]);
		}
		// En caso contrario
		else
		{
			// Si el primer elemento es un salto de linea, quiere decir que no se introdujo nada, por lo que simplemente no hay que hacer nada
			if (cadena[0] == '\n')
				;
			// En caso contrario, es decir, se introdujeron demasiados caracteres, se limpia el buffer
			else
			{
				while (getc(stdin) != '\n')
					;
			}
		}

		// Se llama a la funcion indicada por el caracter introducido por el usuario
		switch (c)
		{
		// Si se introdujo 'A' o 'a', se llama a la funcion suscribir()
		case 'a':
			suscribir(&listaAbonados);
			break;

		// Si se introdujo 'E' o 'e', se llama a la funcion escribir()
		case 'e':
			escribir(&listaAbonados, &listaMensajes);
			break;

		// Si se introdujo 'L' o 'l', se llama a la funcion listar()
		case 'l':
			listar(&listaAbonados, &listaMensajes);
			break;

		// Si se introdujo 'B' o 'b', se llama a la funcion borrar()
		case 'b':
			borrar(&listaAbonados, &listaMensajes);
			break;

		// Si se introdujo 'J' o 'j', se llama a la funcion retirar()
		case 'j':
			retirar(&listaAbonados, &listaMensajes);
			break;

		// Si se introdujo 'S' o 's', se llama a la funcion salir()
		case 's':
			salir(&respuesta, &listaAbonados, &listaMensajes);
			// Si la respuesta del usuario fue afirmativa, se termina el programa
			if (respuesta == 1)
			{
				return 0;
			}
			break;

		// Si no se introdujo una entrada correcta, se informa de ello y se vuelve a pedir una opcion correcta
		default:
			printf("\nHas elegido una opcion invalida\n");
			break;
		}
	} while (1);

	return 0;
}