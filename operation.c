// Modulo Gestor de Operaciones

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "operation.h"
#include "inout.h" //Necesario para usar las funciones incluidas en inout.c y los structs definidos en inout.h

// Funcion que lee la informacion del fichero "abonados.txt"

void fichero_Abonados(struct unAbonado **listaAbonados)
{
  // Se crea un fichero
  FILE *abonados;
  char cadena[100], identidad[5], cuenta[5]; // Variables para guardar la informacion necesaria
  struct unAbonado *nuevoNodo;               // Nuevo nodo que se va a crear
  struct unAbonado *nodoAux;                 // Nodo auxiliar para evitar perder el comienzo de la lista

  // Se abre el fichero llamado "abonados.txt" en modo lectura
  abonados = fopen("abonados.txt", "r");

  // Si el fichero esta vacio, se cierra el fichero y se sale de la funcion
  if (abonados != NULL)
  {
    // En caso contrario, se leera la informacion del fichero, que se ira almacenando en 'cadena', hasta llegar al final
    while (fgets(cadena, sizeof(cadena), abonados) != NULL)
    {
      // Se reserva memoria para el nuevo nodo
      nuevoNodo = (struct unAbonado *)malloc(sizeof(struct unAbonado));
      // Se extrae el contenido de la cadena y se almacena en las respectivas variables del nuevo nodo
      sscanf(cadena, "%s %s %s", identidad, cuenta, nuevoNodo->nombre);
      nuevoNodo->identidad = atoi(identidad);
      nuevoNodo->cuenta = atof(cuenta);
      // El nuevo nodo sera el final de la lista
      nuevoNodo->sig = NULL;

      // Si la lista estaba vacia, el nuevo nodo sera el principio de la lista
      if (*listaAbonados == NULL)
      {
        *listaAbonados = nuevoNodo;
        nodoAux = nuevoNodo;
      }
      // Si la lista no estaba vacia, se coloca el nuevo nodo al final de esta
      else
      {
        nodoAux->sig = nuevoNodo;
        nodoAux = nuevoNodo;
      }
    }
    // Se cierra el fichero y se sale de la funcion
    fclose(abonados);
  }
}

// Funcion que lee la informacion del fichero "mensajes.txt"

void fichero_Mensajes(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)
{
  // Si la lista de abonados esta vacia, la lista de mensajes tambien debe estarlo, por lo que se sale de la funcion y no se lee el fichero
  if (*listaAbonados == NULL)
  {
    return;
  }

  // Se crea un fichero
  FILE *mensajes;
  char cadena[100], emisor[5], destinatario[5]; // Variables para guardar la informacion necesaria
  struct unMensaje *nuevoNodo;                  // Nuevo nodo que se va a crear
  struct unMensaje *nodoAux;                    // Nodo auxiliar para evitar perder el comienzo de la lista

  // Se abre el fichero llamado "mensajes.txt" en modo lectura
  mensajes = fopen("mensajes.txt", "r");

  // Si el fichero esta vacio, se cierra el fichero y se sale de la funcion
  if (mensajes != NULL)
  {
    // En caso contrario, se leera la informacion del fichero, que se ira almacenando en 'cadena', hasta llegar al final
    while (fgets(cadena, sizeof(cadena), mensajes) != NULL)
    {
      // Se reserva memoria para el nuevo nodo
      nuevoNodo = (struct unMensaje *)malloc(sizeof(struct unMensaje));
      // Se extrae el contenido de la cadena y se almacena en las respectivas variables del nuevo nodo
      sscanf(cadena, "%s %s %s", emisor, destinatario, nuevoNodo->texto);
      nuevoNodo->emisor = atoi(emisor);
      nuevoNodo->destinatario = atof(destinatario);
      // El nuevo nodo sera el final de la lista
      nuevoNodo->sig = NULL;

      // Si la lista estaba vacia, el nuevo nodo sera el principio de la lista
      if (*listaMensajes == NULL)
      {
        *listaMensajes = nuevoNodo;
        nodoAux = nuevoNodo;
      }
      // Si la lista no estaba vacia, se coloca el nuevo nodo al final de esta
      else
      {
        nodoAux->sig = nuevoNodo;
        nodoAux = nuevoNodo;
      }
    }
    // Se cierra el fichero y se sale de la funcion
    fclose(mensajes);
  }
}

// Funcion que crea un nuevo abonado

void suscribir(struct unAbonado **lista)
{
  int mayorID = 0;             // Variable para almacenar el mayor ID ya existente
  char cadena[16];             // Variable para almacenar el nombre del nuevo abonado
  struct unAbonado *nuevoNodo; // El nuevo nodo que se va a crear
  // Lista auxiliar para no perder la original
  struct unAbonado *aux;
  aux = *lista;

  // Se reserva memoria para el nuevo nodo
  nuevoNodo = (struct unAbonado *)malloc(sizeof(struct unAbonado));

  // Se informa de la operacion a realizar
  printf("\nSuscribir\n\n");

  // Se pide el nombre del nuevo abonado
  lee_cadena(cadena, 15, "Nombre del abonado");

  // Si la lista no esta vacia...
  if (*lista != NULL)
  {
    // Se recorre toda la lista en busca del mayor ID existente
    do
    {
      // Cuando se encuentra con un ID superior al que anteriormente era el mayor, se guarda este como el mayor
      if (aux->identidad > mayorID)
      {
        mayorID = aux->identidad;
      }
      // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
      aux = aux->sig;
    } while (aux != NULL);
  }
  // En caso contrario, no hay que buscar un ID, ya que el mayor ID ya existente sera el 0

  // Se le da al nuevo nodo un ID superior en una unidad al mayor ya existente
  nuevoNodo->identidad = mayorID + 1;
  // La cuenta de mensajes inicialmente es 0
  nuevoNodo->cuenta = 0;
  // Se le asigna el nombre indicado por el usuario
  strcpy(nuevoNodo->nombre, cadena);
  // El nuevo nodo sera el final de la lista
  nuevoNodo->sig = NULL;

  // Si la lista no esta vacia...
  if (*lista != NULL)
  {
    // Se vuelve a poner la lista auxiliar en el principio
    aux = *lista;
    // Se recorre toda la lista hasta posicionarse el el ultimo nodo que contenga informacion
    while (aux->sig != NULL)
    {
      aux = aux->sig;
    }
    // Se coloca el nuevo nodo a continuacion del que anteriormente era el ultimo
    aux->sig = nuevoNodo;
  }
  // En caso contrario, el primer elemento de la lista sera el nuevo nodo
  else
  {
    *lista = nuevoNodo;
  }

  // Se informa de los cambios realizados
  printf("\nNuevo abonado:\n");
  muestra_abonado(nuevoNodo);
}

// Funcion que crea un nuevo mensaje

void escribir(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)

{
  int id, mayorID = 1, idEmisor, idDestino; // Variables para almacenar el ID introducido por el usuario, el mayor ID existente, el ID del emisor y el ID del destinatario
  char elMensaje[101];                      // Variable para almacenar el texto del mensaje
  struct unMensaje *nuevoNodo;              // El nuevo nodo que se va a crear
  // Listas auxiliares para no perder las originales
  struct unAbonado *auxAbonados;
  struct unMensaje *auxMensajes;
  auxAbonados = *listaAbonados;
  auxMensajes = *listaMensajes;

  // Se informa de la operacion a realizar
  printf("\nEscribir\n\n");

  // Si no hay abonados, se informa de ello y se sale de la funcion
  if (*listaAbonados == NULL)
  {
    printf("No hay abonados\n");
    return;
  }

  // Se recorre toda la lista en busca del mayor ID existente
  do
  {
    // Cuando se encuentra con un ID superior al que anteriormente era el mayor, se guarda este como el mayor
    if (auxAbonados->identidad > mayorID)
    {
      mayorID = auxAbonados->identidad;
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se pide la identidad del emisor del mensaje
  id = lee_entero(mayorID, "Identidad del emisor");

  printf("\n");

  // Se vuelve a poner la lista auxiliar en el principio
  auxAbonados = *listaAbonados;

  // Se recorre toda la lista de los abonados en busca de un abonado con la indentidad indicada por el usuario
  do
  {
    // Si se encuentra, se guarda esa identidad y se para de recorrer la lista
    if (id == auxAbonados->identidad)
    {
      idEmisor = id;
      break;
    }
    // Si se llega al final de la lista sin encontrar una identidad que coincida, se indica que no existe tal abonado y se sale de la funcion
    else
    {
      if (auxAbonados->sig == NULL)
      {
        printf("Abonado desconocido\n");
        return;
      }
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se pide la identidad del destinatario del mensaje
  id = lee_entero(mayorID, "Identidad del destino");

  printf("\n");

  // Se vuelve a poner la lista auxiliar en el principio
  auxAbonados = *listaAbonados;

  // Se recorre toda la lista de los abonados en busca de un abonado con la indentidad indicada por el usuario
  do
  {
    // Si se encuentra, se guarda esa identidad y se para de recorrer la lista
    if (id == auxAbonados->identidad)
    {
      idDestino = id;
      break;
    }
    // Si se llega al final de la lista sin encontrar una identidad que coincida, se indica que no existe tal abonado y se sale de la funcion
    else
    {
      if (auxAbonados->sig == NULL)
      {
        printf("Abonado desconocido\n");
        return;
      }
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se pide el texto del mensaje
  lee_cadena(elMensaje, 100, "Texto del mensaje");

  // Se reserva memoria para el nuevo nodo
  nuevoNodo = (struct unMensaje *)malloc(sizeof(struct unMensaje));
  // Se le da al nuevo nodo los ID's correspondientes
  nuevoNodo->emisor = idEmisor;
  nuevoNodo->destinatario = idDestino;
  // Se le asigna el mensaje dado por el usuario
  strcpy(nuevoNodo->texto, elMensaje);
  // El nuevo nodo sera el final de la lista
  nuevoNodo->sig = NULL;

  // Si la lista de mensajes no esta vacia...
  if (*listaMensajes != NULL)
  {
    // Se recorre toda la lista hasta posicionarse el el ultimo nodo que contenga informacion
    while (auxMensajes->sig != NULL)
    {
      auxMensajes = auxMensajes->sig;
    }
    // Se coloca el nuevo nodo a continuacion del que anteriormente era el ultimo
    auxMensajes->sig = nuevoNodo;
  }
  // En caso contrario, el primer elemento de la lista sera el nuevo nodo
  else
  {
    *listaMensajes = nuevoNodo;
  }

  // Se actualiza la cuenta del destinatario (auxAbonados esta en el nodo del destinatario)
  auxAbonados->cuenta++;

  // Se informa de la operacion realizada
  printf("\nAnotado mensaje:\n");
  muestra_extensa(nuevoNodo);
}

// Funcion que muestra los mensajes disponibles para un abonado

void listar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)
{
  char cadena[16]; // Variable para almacenar el nombre del abonado indicado por el usuario
  int id = 0;      // Variable para almacenar el id del abonado indicado por el usuario
  // Listas auxiliares identicas a las originales, usadas para recorrerlas sin perder las originales
  struct unAbonado *auxAbonados;
  struct unMensaje *auxMensajes;
  auxAbonados = *listaAbonados;
  auxMensajes = *listaMensajes;

  // Se informa de la operacion a realizar
  printf("\nListar\n\n");

  // Si no hay abonados, se informa de ello y se sale de la funcion
  if (*listaAbonados == NULL)
  {
    printf("No hay abonados\n");
    return;
  }

  // En caso contrario, se pide el nombre del abonado del que se desea ver los mensajes
  lee_cadena(cadena, 15, "Nombre del destino");

  // Se recorre toda la lista de los abonados en busca de un abonado con el nombre indicado por el usuario
  do
  {
    // Si existe un abonado con el nombre indicado, se obtiene su id y se para de recorrer la lista
    if (strcmp(cadena, auxAbonados->nombre) == 0)
    {
      id = auxAbonados->identidad;
      break;
    }
    // Si se llega al final de la lista, y la variable id no ha cambiado, se indica que no existe tal abonado, y se sale de la funcion
    else if (auxAbonados->sig == NULL && id == 0)
    {
      printf("\nAbonado desconocido\n");
      return;
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Si se encontro el abonado, se muestran sus mensajes disponibles
  printf("\nMensajes para %s:\n", cadena);

  // Si la lista de mensajes no esta vacia...
  if (*listaMensajes != NULL)
  {
    // Se recorre toda la lista de los mensajes en busca de los mensaje cuyo destinatario sea el abonado indicado por el usuario
    do
    {
      // Si el mensaje tiene como id de destinatario el mismo que el id obtenido del abonado indicado por el usuario, se muestra el mensaje
      if (auxMensajes->destinatario == id)
      {
        muestra_corta(auxMensajes);
      }
      // En cada iteracion, se avanza un nodo en la lista, para recorrerla por completo
      auxMensajes = auxMensajes->sig;
    } while (auxMensajes != NULL);
  }
}

// Funcion que elimina un mensaje

void borrar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)
{
  int id = 0, mayorID = 1, idDestino, posicion, i, n = 0; // Variables para almacenar el ID introducido por el usuario, el mayor ID existente, el ID del destinatario y las variable de iteracion de los bucles
  // Listas auxiliares identicas a las originales, usadas para recorrerlas sin perder las originales
  struct unAbonado *auxAbonados;
  struct unMensaje *auxMensajes;
  struct unMensaje *auxMensajes2;
  auxAbonados = *listaAbonados;
  auxMensajes = *listaMensajes;
  auxMensajes2 = *listaMensajes;

  // Se informa de la operacion a realizar
  printf("\nBorrar\n\n");

  // Si no hay abonados, se informa de ello y se sale de la funcion
  if (*listaAbonados == NULL)
  {
    printf("No hay abonados\n");
    return;
  }

  // Se recorre toda la lista en busca del mayor ID existente
  do
  {
    // Cuando se encuentra con un ID superior al que anteriormente era el mayor, se guarda este como el mayor
    if (auxAbonados->identidad > mayorID)
    {
      mayorID = auxAbonados->identidad;
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se pide la identidad del destinatario del mensaje
  id = lee_entero(mayorID, "Identidad del destino");

  printf("\n");

  // Se vuelve a poner la lista auxiliar en el principio
  auxAbonados = *listaAbonados;

  // Se recorre toda la lista de los abonados en busca de un abonado con la indentidad indicada por el usuario
  do
  {
    // Si se encuentra, se guarda esa identidad y se para de recorrer la lista
    if (id == auxAbonados->identidad)
    {
      idDestino = id;
      break;
    }
    // Si se llega al final de la lista sin encontrar una identidad que coincida, se indica que no existe tal abonado y se sale de la funcion
    else
    {
      if (auxAbonados->sig == NULL)
      {
        printf("Abonado desconocido\n");
        return;
      }
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Si el abonado indicado no tiene mensajes disponibles, se informa de ello y se sale de la funcion
  if (auxAbonados->cuenta == 0)
  {
    printf("No hay mensajes\n");
    return;
  }

  // Se pide la posicion del mensaje que se desea borrar
  posicion = lee_entero(auxAbonados->cuenta, "Posicion del mensaje");

  // Se actualiza la cuenta del abonado
  auxAbonados->cuenta--;

  // Si el mensaje que se desea borrar es el primer elemento de la lista...
  if ((*listaMensajes)->destinatario == idDestino)
  {
    // Se coloca como primer elemento de la lista el siguiente al que se desea borrar
    *listaMensajes = (*listaMensajes)->sig;
    // Se libera la memoria del nodo que se desea borrar
    free(auxMensajes);
  }
  // En caso contrario...
  else
  {
    // Se recorren las listas de mensajes auxiliares hasta posicionarse en el lugar adecuado
    for (i = 0; i < posicion; i++)
    {
      // Se recorre toda la lista de mensajes hasta posicionarse en el nodo indicado por el usuario
      while (auxMensajes->destinatario != idDestino)
      {
        // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
        auxMensajes = auxMensajes->sig;
      }
      // Se recorre toda la lista de mensajes hasta posicionarse en el nodo anterior al indicado por el usuario
      while (auxMensajes2->sig->destinatario != idDestino)
      {
        // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
        auxMensajes2 = auxMensajes2->sig;
      }
      // Para evitar que el bucle sea infinito, se avanza un nodo extra cuando todavia no se llego a la posicion deseada
      n++; // Se evalua en que iteracion se encuentra el bucle
      // Si aun no se llego a la posicion deseada, se avanza un nodo extra para evitar que el bucle sea infinito
      if (n < posicion)
      {
        auxMensajes = auxMensajes->sig;
        auxMensajes2 = auxMensajes2->sig;
      }
    }

    // Se enlaza el nodo anterior al que se desea borrar con el posterior al que se desea borrar
    auxMensajes2->sig = auxMensajes->sig;
    // Se libera la memoria del nodo que se desea borrar
    free(auxMensajes);
  }

  // Se informa de la operacion realizada
  printf("\nMensaje borrado\n");
}

// Funcion que elimina un abonado y todos sus mensajes

void retirar(struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)
{
  int id, mayorID = 1, i; // Variables para almacenar el ID introducido por el usuario, el mayor ID existente y la variable de iteracion de los bucles
  // Listas auxiliares identicas a las originales, usadas para recorrerlas sin perder las originales
  struct unAbonado *auxAbonados;
  struct unAbonado *auxAbonados2;
  struct unMensaje *auxMensajes;
  struct unMensaje *auxMensajes2;
  auxAbonados = *listaAbonados;
  auxAbonados2 = *listaAbonados;
  auxMensajes = *listaMensajes;
  auxMensajes2 = *listaMensajes;

  // Se informa de la operacion a realizar
  printf("\nRetirar\n\n");

  // Si no hay abonados, se informa de ello y se sale de la funcion
  if (*listaAbonados == NULL)
  {
    printf("No hay abonados\n");
    return;
  }

  // Se recorre toda la lista en busca del mayor ID existente
  do
  {
    // Cuando se encuentra con un ID superior al que anteriormente era el mayor, se guarda este como el mayor
    if (auxAbonados->identidad > mayorID)
    {
      mayorID = auxAbonados->identidad;
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se pide la identidad del abonado que se desea retirar
  id = lee_entero(mayorID, "Identidad del abonado");

  // Se vuelve a poner la lista auxiliar en el principio
  auxAbonados = *listaAbonados;

  // Se recorre toda la lista de los abonados en busca de un abonado con la indentidad indicada por el usuario
  do
  {
    // Si se encuentra, se para de recorrer la lista
    if (id == auxAbonados->identidad)
    {
      break;
    }
    // Si se llega al final de la lista sin encontrar una identidad que coincida, se indica que no existe tal abonado y se sale de la funcion
    else
    {
      if (auxAbonados->sig == NULL)
      {
        printf("\nAbonado desconocido\n");
        return;
      }
    }
    // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
    auxAbonados = auxAbonados->sig;
  } while (auxAbonados != NULL);

  // Se eliminan todos los mensajes del abonado indicado, uno a uno, y tantas veces como lo indique la cuenta del abonado
  for (i = 0; i < auxAbonados->cuenta; i++)
  {
    // Si el mensaje que se desea borrar es el primer elemento de la lista...
    if ((*listaMensajes)->destinatario == id)
    {
      // Se coloca como primer elemento de la lista el siguiente al que se desea borrar
      *listaMensajes = (*listaMensajes)->sig;
      // Se libera la memoria del nodo que se desea borrar
      free(auxMensajes);
    }
    // En caso contrario...
    else
    {
      // Se recorre toda la lista de mensajes hasta posicionarse en el nodo que se desea borrar
      while (auxMensajes->destinatario != id)
      {
        // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
        auxMensajes = auxMensajes->sig;
      }
      // Se recorre toda la lista de mensajes hasta posicionarse en el nodo anterior al que se desea borrar
      while (auxMensajes2->sig->destinatario != id)
      {
        // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
        auxMensajes2 = auxMensajes2->sig;
      }
      // Se enlaza el nodo anterior al que se desea borrar con el posterior al que se desea borrar
      auxMensajes2->sig = auxMensajes->sig;
      // Se libera la memoria del nodo que se desea borrar
      free(auxMensajes);
    }
  }

  // Si el abonado que se desea borrar es el primer elemento de la lista...
  if ((*listaAbonados)->identidad == id)
  {
    // Se coloca como primer elemento de la lista el siguiente al que se desea borrar
    *listaAbonados = (*listaAbonados)->sig;
    // Se libera la memoria del nodo que se desea borrar
    free(auxAbonados);
  }
  // En caso contrario...
  else
  {
    // Se recorre toda la lista de mensajes hasta posicionarse en el nodo anterior al que se desea borrar
    while (auxAbonados2->sig->identidad != id)
    {
      // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
      auxAbonados2 = auxAbonados2->sig;
    }
    // Se enlaza el nodo anterior al que se desea borrar con el posterior al que se desea borrar
    auxAbonados2->sig = auxAbonados->sig;
    // Se libera la memoria del nodo que se desea borrar
    free(auxAbonados);
  }

  // Se informa de la operacion realizada
  printf("\nAbonado retirado\n");
}

// Funcion que confirma si el usuario desea salir y guarda toda la informacion obtenida durante la ejecucion del programa en caso de respuesta afirmativa

void salir(int *respuesta, struct unAbonado **listaAbonados, struct unMensaje **listaMensajes)
{
  // Se informa de la operacion a realizar
  printf("\nSalir\n\n");

  // Se pide al usuario la confirmacion y se almacena el resultado
  *respuesta = confirmar("Seguro que desea salir del programa? (s/n): \n");

  // Si la respuesta fue afirmativa...
  if (*respuesta == 1)
  {
    // Se crean dos ficheros
    FILE *abonados;
    FILE *mensajes;
    // Se abren en modo escritura
    abonados = fopen("abonados.txt", "w");
    mensajes = fopen("mensajes.txt", "w");

    // Se recorre toda la lista de los abonados y se copia toda la informacion al fichero "abonados.txt"
    while (*listaAbonados != NULL)
    {
      // Se copia la identidad
      fprintf(abonados, "%d ", (*listaAbonados)->identidad);
      // Se copia la cuenta
      fprintf(abonados, "%d ", (*listaAbonados)->cuenta);
      // Se copia el nombre
      fputs((*listaAbonados)->nombre, abonados);
      // Se salta a la siguiente linea para la informacion del posible siguiente abonado
      fprintf(abonados, "\n");
      // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
      *listaAbonados = (*listaAbonados)->sig;
    }

    // Se recorre toda la lista de los mensajes y se copia toda la informacion al fichero "mensajes.txt"
    while (*listaMensajes != NULL)
    {
      // Se copia la identidad del emisor
      fprintf(mensajes, "%d ", (*listaMensajes)->emisor);
      // Se copia la identidad del destinatario
      fprintf(mensajes, "%d ", (*listaMensajes)->destinatario);
      // Se copia el texto del mensaje
      fputs((*listaMensajes)->texto, mensajes);
      // Se salta a la siguiente linea para la informacion del posible siguiente mensaje
      fprintf(mensajes, "\n");
      // En cada iteracion se avanza un nodo en la lista, para recorrerla por completo
      *listaMensajes = (*listaMensajes)->sig;
    }

    // Se cierran los ficheros y se termina el programa
    fclose(abonados);
    fclose(mensajes);
  }
  // Si la respuesta fue negativa, se vuelve al menu principal
  else
  {
    return;
  }
}