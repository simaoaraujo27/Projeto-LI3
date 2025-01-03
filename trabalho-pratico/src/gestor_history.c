#include "gestor_history.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "history.h"
#include "query4.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>

struct gestorHistory {
  FILE *errorsFile;
};

gestorHistory *initGestorHistory(const char *errorsFilePath) {
  gestorHistory *gestorHistory = malloc(sizeof(struct gestorHistory));
  if (!gestorHistory)
    return NULL;

  gestorHistory->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorHistory->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorHistory);
    return NULL;
  }

  return gestorHistory;
}

void freeGestorHistory(gestorHistory *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile);
    free(gestor);
  }
}

void parserHistory(History *history, char *line, char *copia,
                   Gestores *gestor) {

  gestorArtists *gestorArtists = pegarGestorArtist(gestor);
  gestorHistory *gestorHistory = pegarGestorHistory(gestor);
  gestorMusics *gestorMusics = pegarGestorMusic(gestor);
  gestorUsers *gestorUsers = pegarGestorUser(gestor);
  FILE *errorsFile = gestorHistory->errorsFile;

  if (validateHistoryLine(copia)) {
    char *id = getHistoryId(history);
    remove_quotes(id);

    char *musicId = getHistoryMusicId(history);
    incrementRecipeArtist(musicId, gestorMusics, gestorArtists);

    // ---- para query5

    char *currentUser = getHistoryUserId(history);
    char *currentUserCopia = currentUser;
    remove_quotes(currentUser);
    gpointer orig_keyUser;
    gpointer valueUser;
    lookUpUsersHashTable(gestorUsers, currentUser, &orig_keyUser, &valueUser);
    gpointer orig_keyMusic;
    gpointer valueMusic;
    lookUpMusicsHashTable(gestorMusics, musicId, &valueMusic, &orig_keyMusic);
    char *musicGenre = getMusicGenre(orig_keyMusic);
    char *artistId = getMusicArtistId(orig_keyMusic);
    char *albumId = getMusicAlbumId(orig_keyMusic);
    remove_quotes(albumId);
    incrementMusicsListening(valueUser, musicGenre);

    //--- para a query4

    remove_quotes(musicId);
    char *timeStamp = getHistoryTimestamp(history);
    char *timeStampCopia = timeStamp;
    remove_quotes(timeStamp);
    int dias = calcularDiasAte_9_9_2024(timeStamp);
    char *durationStr = getHistoryDuration(history);
    remove_quotes(durationStr);
    int durationSeg = converterParaSegundos(durationStr);

    armazenarValores(musicId, durationSeg, dias, gestorMusics, gestorArtists,
                     getGArrayTops10(gestorArtists));

    // query 6

    char *temp = timeStampCopia;
    int year = atoi(timeStampCopia);
    timeStampCopia += 5;
    timeStampCopia[5] = '\0';
    int dia = calculateDiaAno(timeStampCopia) - 1;
    if (isLeapYear(year))
      dia++;
    timeStampCopia += 6;
    int hora = atoi(timeStampCopia);
    char *art = strdup(artistId);
    remove_quotes(art);
    removeFstLast(art);
    gpointer value = NULL;
    gpointer orig_key = NULL;
    gboolean found =
        lookUpQuery6Table(gestorUsers, currentUser, &value, &orig_key);
    int y = 0;
    int val = 0;
    if (found) {
      char *v = (char *)orig_key;
      while (v != NULL && strlen(v) > 3) {
        char *a = strndup(v, 4);
        y = atoi(a);
        free(a);
        if (y == year) {
          val = 1;
          break;
        } else {
          v = v + 4;
        }
      }
    }

    if (found && year <= 2024 && val) {
      updateUserResume(valueUser, year, durationSeg, musicId, art, albumId,
                       musicGenre, dia, hora);
    }

    free(albumId);
    free(artistId);
    free(musicGenre);
    free(musicId);
    free(temp);
    free(durationStr);
    free(art);
    free(id);
    free(currentUserCopia);
  } else {
    fprintf(errorsFile, "%s", line);
  }
  destroyHistory(history);
}

int GestorHistory(Gestores *gestor, char *historyPath) {
  gestorMusics *gestorMusics = pegarGestorMusic(gestor);

  FILE *fp = fopen(historyPath, "r");

  if (fp) {
    char *line = NULL;
    size_t len = 0;
    History *history = NULL;

    assert(getline(&line, &len, fp) != -1);

    while (getline(&line, &len, fp) != -1) {
      if (line != NULL) {
        char *line_copy = strdup(line);
        if (!line_copy) {
          fprintf(stderr, "Erro ao duplicar a linha\n");
          continue;
        }
        history = separateHistory(line_copy);
        char *currentMusic = getHistoryMusicId(history);
        gpointer orig_key;
        gpointer value;
        lookUpMusicsHashTable(gestorMusics, currentMusic, &value, &orig_key);

        char *copia = strdup(line);
        parserHistory(history, line, copia, gestor);
        free(copia);
        free(line_copy);
        free(currentMusic);
        free(line);
        line = NULL;
      }
    }
    free(line);
    fclose(fp);
  } else {
    perror("Error opening history file");
    return 0;
  }
  return 1;
}
