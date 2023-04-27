// Modulo Entrada/Salida

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inout.h"

// Funcion que imprime los bordes superior e inferior de la caratula

void plano(char caracter, int n)

{
  // Imprime n veces el caracter indicado
  for (int i = 0; i < n; i++)
    fputc(caracter, stdout);

  printf("\n");
}

// Funcion que imprime la linea central de la caratula

void rotulo(char nombre[], char caracter, int n)

{
  int i, espacios;

  // Calculo de cuantos espacios en blanco habra entre los caracteres delimitadores y el nombre
  espacios = (n - strlen(nombre) - 2) / 2;

  // Caracter delimitador izquierdo
  fputc(caracter, stdout);

  // Espacios a la izquierda del nombre
  for (i = 0; i < espacios; i++)
    printf(" ");

  // El nombre
  fputs(nombre, stdout);

  // Espacios a la derecha del nombre
  for (i = 0; i < espacios; i++)
    printf(" ");

  // Caracter delimitador derecho
  fputc(caracter, stdout);

  printf("\n");
}

// Funcion para seleccionar entre una afirmacion o negacion

int confirmar(char mensaje[])

{
  char respuesta[3];
  int i;

  // Bucle que hara la pregunta al usuario mientras no se seleccione una opcion correcta
  do
  {
    i = 0; // Variable de evaluacion del bucle

    // Muestra el mensaje de invitacion
    fputs(mensaje, stdout);
    // Coje la respuesta del usuario y la asigna a una cadena de 2 caracteres + \0
    fgets(respuesta, 3, stdin);
    // Si el segundo caracter es un salto de linea, significa que solo se indrodujo un caracter y el salto
    if (respuesta[1] == '\n')
    {
      // Se pasa el caracter a minuscula
      respuesta[0] = tolower(respuesta[0]);
      // Si el caracter era una S o s, se termina la funcion retornando un 1
      if (respuesta[0] == 's')
        return 1;
      else
        // Si el caracter era una N o n, se termina la funcion retornando un 0
        if (respuesta[0] == 'n')
          return 0;
        // Si el caracter era incorrecto, se repite el bucle
        else
          i = 0;
    }
    // Si el segundo caracter no es un salto de linea, significa que se introdujeron demasiados caracteres, o que solo se introdujo el salto de linea
    else
      // Si solo se introdujo un salto de linea, se repite el bucle
      if (strlen(respuesta) == 1)
        i = 0;
      // Si se introdujeron demasiados caracteres, se limpia el buffer y se repite el bucle
      else
      {
        i = 0;
        while (getc(stdin) != '\n')
          ;
      }
  } while (i == 0);

  return 0;
}

// Funcion que lee una cadena del teclado

void lee_cadena(char *direccion_Cadena, int longitud, char mensaje[])

{
  int correcto = 0, num_Asignaciones; // Variables para comprobar si se hicieron las correctas asignaciones
  char cadena[longitud + 2];          // Cadena leida del teclado, del tamano de la longitud indicada mas dos caracteres (el salto de linea y el fin de cadena)

  // Bucle que pedira una cadena al usuario mientras no se introduzca una cadena correcta
  do
  {
    // Muestra el mensaje de invitacion y el tamano permitido de la cadena
    printf("%s (1-%d car): ", mensaje, longitud);
    // Lee la cadena del teclado
    fgets(cadena, sizeof(cadena), stdin);

    // Si el primer caracter es el salto de linea, significa que no se introdujo ninguna cadena
    if (cadena[0] == '\n')
      printf("\nLongitud nula\n\n");
    else
      // Si el ultimo caracter de la cadena no es el salto de linea, significa que se sobrepaso el tamano maximo permitido
      if (cadena[strlen(cadena) - 1] != '\n')
      {
        printf("\nLongitud excesiva\n\n");
        // Se limpia el buffer
        while (fgetc(stdin) != '\n')
          ;
      }
      // En otro caso, se introdujo una cadena del tamano correcto
      else
      {
        // Se extrae el contenido de la cadena y se le asigna a direccion_Cadena, un puntero a la direccion de memoria donde se guardara la cadena
        num_Asignaciones = sscanf(cadena, "%s", direccion_Cadena);
        // Si se asigno una cadena (lo correcto), se sale del bucle y se termina la funcion
        if (num_Asignaciones == 1)
          correcto = 1;
        // Si no se asigno una cadena, quiere decir que la cadena era espacios en blanco
        else
          printf("Longitud nula\n");
      }

  } while (correcto == 0);
}

// Funcion que lee un entero del teclado

int lee_entero(int valor_Max, char mensaje[])

{
  char cadena[5], salto_Linea; // Cadena leida del teclado (permite leer enteros hasta el 999), y caracter correspondiente con el salto de linea
  int entero, correcto = 0;    // Entero introducido por el usuario, que es retornado por la funcion, y variable de comprobacion del bucle

  // Bucle que pedira un entero al usuario mientras no se introduzca un entero correctamente
  do
  {
    // Muestra el mensaje de invitacion y el tamano permitido del entero
    printf("%s [1-%d]: ", mensaje, valor_Max);
    // Lee una cadena del teclado
    fgets(cadena, sizeof(cadena), stdin);

    // Si el ultimo caracter de la cadena no es un salto de linea, significa que se sobrepaso el tamano de la cadena, es decir, se escribieron al menos 4 caracteres y el salto de linea. Por lo tanto, se limpia el buffer y se repite el bucle
    if (cadena[strlen(cadena) - 1] != '\n')
    {
      printf("\nValor incorrecto\n\n");
      while (fgetc(stdin) != '\n')
        ;
    }
    else
    {
      // Si el primer caracter es un espacio, se repite el bucle
      if (cadena[0] == ' ')
        printf("\nValor incorrecto\n\n");
      // En otro caso, se extrae el contenido de la cadena y se le asigna la primera parte a entero y la segunda a salto_Linea
      else
      {
        sscanf(cadena, "%d%c", &entero, &salto_Linea);
        // Si entero no se encuentra entre 1 y valor_Max, o directamente no es un entero, o salto_Linea no se corresponde con un salto de linea, se repite el bucle
        if (entero < 1 || entero > valor_Max || salto_Linea != '\n')
          printf("\nValor incorrecto\n\n");
        // Si la asignacion fue correcta, se sale del bucle y la funcion termina retornando el entero
        else
          correcto = 1;
      }
    }
  } while (correcto == 0);

  return entero;
}

// Funcion que muestra la informacion de un abonado en forma compacta (la identidad y el nombre)

void muestra_abonado(struct unAbonado *elAbonado)
{
  // Imprime la informacion del abonado con el formato "#IDENTIDAD:NOMBRE", con campos de anchura 3 y 15, respectivamente
  printf("#%3d:%15s\n", elAbonado->identidad, elAbonado->nombre);
}

// Funcion que muestra la informacion de un mensaje en forma extensa (emisor, destino y texto)

void muestra_extensa(struct unMensaje *elMensaje)
{
  // Imprime la informacion del mensaje con el formato "> Emisor: ID_Emisor > Destino: ID_Destino > Texto: mensaje" en tres lineas
  printf("> Emisor: %d\n> Destino: %d\n> Texto: %s\n", elMensaje->emisor, elMensaje->destinatario, elMensaje->texto);
}

// Funcion que muestra la informacion de un mensaje en forma corta (emisor, destino y texto)

void muestra_corta(struct unMensaje *elMensaje)
{
  // Imprime la informacion del mensaje con el formato "#ID_Emisor:ID_Destino:Texto", con campos de anchura 3 para las identidades, y hasta 12 caracteres para el texto
  printf("#%3d:%3d:%.12s\n", elMensaje->emisor, elMensaje->destinatario, elMensaje->texto);
}