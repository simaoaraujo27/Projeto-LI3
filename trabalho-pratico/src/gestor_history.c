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
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *historyTable; // Hashtable para armazenar o history
};

// Função para inicializar a estrutura gestorHistory
gestorHistory *initGestorHistory(const char *errorsFilePath) {

  GHashTable *gestorTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyHistory);

  // Aloca memória para a estrutura
  gestorHistory *gestorHistory = malloc(sizeof(struct gestorHistory));
  if (!gestorHistory)
    return NULL;

  // Abre o ficheiro para escrita de erros
  gestorHistory->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorHistory->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorHistory);
    return NULL;
  }

  // Atribui a hashtable fornecida
  gestorHistory->historyTable = gestorTable;
  return gestorHistory;
}

// Função para libertar a estrutura gestorHistory e os seus recursos
void freeGestorHistory(gestorHistory *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    g_hash_table_destroy(gestor->historyTable);
    free(gestor); // Liberta a memória da estrutura
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
    // Obtém o ID do history e remove aspas
    char *id = getHistoryId(history);
    remove_quotes(id);

    char *musicId = getHistoryMusicId(history);
    incrementMusicRep(musicId, gestorMusics, gestorArtists);

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
    free(currentUserCopia);
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
    int year = atoi(timeStampCopia);
    timeStampCopia += 5;
    timeStampCopia[5] = '\0';
    int dia = calculateDiaAno(timeStampCopia) - 1;
    timeStampCopia += 6;
    int hora = atoi(timeStampCopia);
    // if (year && dia && hora){}
    char *art = strdup(artistId);
    remove_quotes(art);
    removeFstLast(art);
    if (year && dia && hora) {
    }
    // printf("%d %d %s %s %s %s %d %d\n\n", year, durationSeg, musicId, art,
    // albumId, musicGenre, dia, hora);
    //updateUserResume(valueUser, year, durationSeg, musicId, art, albumId,
    //                 musicGenre, dia, hora);
    free(albumId);
    free(artistId);
    free(musicGenre);
    //

    free(musicId);
    // free(timeStampCopia);
    free(durationStr);
  } else {
    // Escreve a linha inválida no ficheiro de erros
    fprintf(errorsFile, "%s", line);
  }
  destroyHistory(history);
}

// Função para processar o ficheiro de history utilizando a estrutura
// gestorHistory
int GestorHistory(Gestores *gestor, char *historyPath) {
  gestorMusics *gestorMusics = pegarGestorMusic(gestor);

  // Abre o arquivo de history e carrega os dados
  FILE *fp = fopen(historyPath, "r");

  if (fp) {
    char *line = NULL; // Pointer para armazenar cada linha lida
    size_t len = 0;    // Tamanho da linha
    History *history = NULL;

    // Ignora a primeira linha do ficheiro (cabeçalho)
    assert(getline(&line, &len, fp) != -1);

    // Lê o ficheiro linha por linha
    while (getline(&line, &len, fp) != -1) {
      if (line != NULL) {
        // Duplicação segura da linha para processamento
        char *line_copy = strdup(line);
        if (!line_copy) {
          fprintf(stderr, "Erro ao duplicar a linha\n");
          continue; // Se falhar, passa à próxima linha
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
    // Liberta a linha utilizada pelo getline
    free(line);
    fclose(fp);
  } else {
    perror("Error opening history file");
    return 0;
  }

  return 1;
}

/*
Pegar no id do user
Pegar todas as vezes que ele aparece na ht do history
*/