#include "gestores.h"
#include "erros.h"
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
  gestorAlbuns *gestorAlbuns;
  FicheiroErrosCSV *ficheiroErrosCSV;
};

Gestores *initgestor(int *flag) {

  // Aloca memória para a estrutura
  Gestores *gestor = malloc(sizeof(struct gestores));
  if (!gestor)
    return NULL;

  // Inicializa o gestor de artistas com o arquivo de erros
  gestorArtists *gestorArtists = initGestorArtists();

  // Verifica se o gestor de artistas foi inicializado corretamente
  if (!gestorArtists) {
    *flag = 1;
    return NULL;
  }

  // Inicializa o gestor de músicas
  gestorMusics *gestorMusics = initGestorMusics();

  // Verifica se o gestor de musicas foi inicializado corretamente
  if (!gestorMusics) {
    *flag = 1;
    return NULL;
  }
  // Inicializa o gestor de users
  gestorUsers *gestorUsers = initGestorUsers();

  // Verifica se o gestor de users foi inicializado corretamente
  if (!gestorUsers) {
    *flag = 1;
    return NULL;
  }

  // Inicializa o gestor de álbuns
  gestorAlbuns *gestorAlbuns = initGestorAlbuns();

  // Verifica se o gestor de álbuns foi inicializado corretamente
  if (!gestorAlbuns) {
    *flag = 1;
    return NULL;
  }

  FicheiroErrosCSV *ficheiroErrosCSV = initFicheiroErrosCSV();

  // Atribui os Gestores fornecidos
  gestor->gestorMusics = gestorMusics;
  gestor->gestorArtists = gestorArtists;
  gestor->gestorUsers = gestorUsers;
  gestor->gestorAlbuns = gestorAlbuns;
  gestor->ficheiroErrosCSV = ficheiroErrosCSV;
  return gestor;
}

gestorArtists *getGestorArtist(Gestores *gestor) {
  return gestor->gestorArtists;
}

gestorMusics *getGestorMusic(Gestores *gestor) { return gestor->gestorMusics; }

gestorUsers *getGestorUser(Gestores *gestor) { return gestor->gestorUsers; }

gestorAlbuns *getGestorAlbum(Gestores *gestor) { return gestor->gestorAlbuns; }

FicheiroErrosCSV *getGestorFicheiroErrosCSV(Gestores *gestor) {
  return gestor->ficheiroErrosCSV;
}

void destroyGestor(Gestores *gestor) {
  freeGestorArtists(gestor->gestorArtists);
  freeGestorMusics(gestor->gestorMusics);
  freeGestorUsers(gestor->gestorUsers);
  freeGestorAlbuns(gestor->gestorAlbuns);
  destroyFicheiroErrosCSV(gestor->ficheiroErrosCSV);
  free(gestor);
}
