#include "argumentos_query5.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_history.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "users.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Define o tamanho máximo para os paths dos arquivos
#define MAX_PATH_SIZE 1024

void libertaPaths(char *p1, char *p2, char *p3, char *p4, char *p5) {
  free(p1);
  free(p2);
  free(p3);
  free(p4);
  free(p5);
}

int GestorParsers(Gestores *gestor, char *path, FILE *fp) {
  // Aloca memória para os paths completos dos arquivos
  char *artistsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *musicsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *usersPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *albunsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *historyPath = malloc(MAX_PATH_SIZE * sizeof(char));

  // Constroi os paths completos para os arquivos CSV
  snprintf(artistsPath, MAX_PATH_SIZE, "%s/%s", path, "artists.csv");
  snprintf(musicsPath, MAX_PATH_SIZE, "%s/%s", path, "musics.csv");
  snprintf(usersPath, MAX_PATH_SIZE, "%s/%s", path, "users.csv");
  snprintf(albunsPath, MAX_PATH_SIZE, "%s/%s", path, "albums.csv");
  snprintf(historyPath, MAX_PATH_SIZE, "%s/%s", path, "history.csv");

  gestorArtists *gestorArtists = getGestorArtist(gestor);
  gestorUsers *gestorUsers = getGestorUser(gestor);

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    setQuery6Table(line, gestorUsers);
  }
  free(line);

  if (!GestorArtists(gestor, artistsPath)) {
    libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
    return 0;
  }

  if (!GestorAlbuns(gestor, albunsPath)) {
    libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
    return 0;
  }

  if (!GestorMusics(gestor, musicsPath)) {
    libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
    return 0;
  }

  CriaListasQuery2(gestorArtists);

  if (!GestorUsers(gestor, usersPath)) {
    libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
    return 0;
  }

  if (!GestorHistory(gestor, historyPath)) {
    libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
    return 0;
  }

  argumentosQuery5 *a = getGestorArgumentosQuery5(gestor);
  alocaMatriz(gestor, a);
  constroiQuery5(gestor, a);

  libertaPaths(artistsPath, musicsPath, usersPath, albunsPath, historyPath);
  return 1;
}