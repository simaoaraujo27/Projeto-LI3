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

int GestorParsers(Gestores *gestor, char *path) {

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

  if (!GestorArtists(pegarGestorArtist(gestor), artistsPath))
    return 0;

  if (!GestorAlbuns(pegarGestorAlbum(gestor), albunsPath,
                    pegarGestorArtist(gestor)))
    return 0;

  if (!GestorMusics(pegarGestorMusic(gestor), pegarGestorArtist(gestor),
                    pegarGestorAlbum(gestor), musicsPath))
    return 0;

  if (!GestorUsers(pegarGestorUser(gestor), pegarGestorMusic(gestor),
                   usersPath))
    return 0;

  if (!GestorHistory(pegarGestorHistory(gestor), pegarGestorMusic(gestor), pegarGestorArtist(gestor),
                     historyPath))
    return 0;

  return 1;
}