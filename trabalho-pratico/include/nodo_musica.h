#ifndef _NODO_MUSICA_H_
#define _NODO_MUSICA_H_

typedef struct nodoMusica NodoMusica;

#include <assert.h>
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoMusica *criar_nodo(char *genero, guint idade_max);

void expandir_arrays(NodoMusica *lista, guint nova_idade_max);

NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max);

void liberar_lista(NodoMusica *lista);

char *getGeneroNodoMusic(NodoMusica *l);
GArray *getLikesNodoMusic(NodoMusica *l);
NodoMusica *getProxNodoMusic(NodoMusica *l);

#endif