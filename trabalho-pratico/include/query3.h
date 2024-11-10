#ifndef _QUERY3_H_
#define _QUERY3_H_

#include <glib.h>
#include "gestor_musics.h"
#include "gestor_users.h"

typedef struct nodoMusica NodoMusica;

NodoMusica *criar_nodo(char *genero, guint idade_max);

void expandir_arrays(NodoMusica *lista, guint nova_idade_max);

NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max);

void liberar_lista(NodoMusica *lista);

typedef struct generoLikes GeneroLikes;

gint comparar_likes(gconstpointer a, gconstpointer b);

void query3(int minAge, int maxAge, NodoMusica *lista, int i);

NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, guint idade_max,
                             gestorMusics *gestorMusics,
                             gestorUsers *gestorUsers);

#endif