#include "gestores.h"
#include "gestor_queries.h"
#include "query1.h"
#include "query2.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gestores {
  gestorArtists *gestorArtists;
  gestorMusics *gestorMusics;
  gestorUsers *gestorUsers;
};

Gestores *initgestor(int *flag) {

  // Aloca memória para a estrutura
  Gestores *gestor = malloc(sizeof(Gestores));
  if (!gestor)
    return NULL;

  // Inicializa o gestor de artistas com o arquivo de erros
  gestorArtists *gestorArtists =
      initGestorArtists("./resultados/artists_errors.csv");

  // Verifica se o gestor de artistas foi inicializado corretamente
  if (!gestorArtists) {
    *flag = 1;
    return NULL;
  }

  // Inicializa o gestor de músicas
  gestorMusics *gestorMusics =
      initGestorMusics("./resultados/musics_errors.csv");

  // Verifica se o gestor de musicas foi inicializado corretamente
  if (!gestorMusics) {
    *flag = 1;
    return NULL;
  }
  // Inicializa o gestor de users
  gestorUsers *gestorUsers = initGestorUsers("./resultados/users_errors.csv");

  // Verifica se o gestor de users foi inicializado corretamente
  if (!gestorUsers) {
    *flag = 1;
    return NULL;
  }

  // Atribui os Gestores fornecidos
  gestor->gestorMusics = gestorMusics;
  gestor->gestorArtists = gestorArtists;
  gestor->gestorUsers = gestorUsers;
  return gestor;
}

gestorArtists *pegarGestorArtist(Gestores *gestor) {
  return gestor->gestorArtists;
}

gestorMusics *pegarGestorMusic(Gestores *gestor) {
  return gestor->gestorMusics;
}

gestorUsers *pegarGestorUser(Gestores *gestor) { return gestor->gestorUsers; }

void destroyGestor(Gestores *gestor) {
  freeGestorArtists(gestor->gestorArtists);
  freeGestorMusics(gestor->gestorMusics);
  freeGestorUsers(gestor->gestorUsers);
  free(gestor);
}
