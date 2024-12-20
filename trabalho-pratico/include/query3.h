#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct generoLikes GeneroLikes;

#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "nodo_musica.h"
#include <glib.h>

gint comparar_likes(gconstpointer a, gconstpointer b);

void query3(int minAge, int maxAge, NodoMusica *lista, int i);

NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, Gestores *gestor);

void processUserQuery3(char *liked_musics_id, Gestores *gestor,
                       NodoMusica *lista, int userAge, guint idade_max);

#endif