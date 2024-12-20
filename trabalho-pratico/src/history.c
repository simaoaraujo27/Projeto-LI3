#include "history.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que armazena informações sobre o history (histórico de músicas
// ouvidas no sistema)
struct history {
  char *id;      // Identificador único do registo
  char *user_id; // Identificador único do utilizador a que o registo se refere
  char *music_id;  // Identificador único da música a que o registo se refere
  char *timestamp; // Data e hora em que a música foi ouvida pelo utilizador
  char *duration; // Tempo de duração da audição da música. E.g., um utilizador
                  // pode ter ouvido apenas 30 segundos de uma música
  char *platform; // Plataforma em que a música foi reproduzida. I.e.,
                  // computador ou dispositivo móvel
};

// Funções get
const char *getHistoryId(const History *hist) { return hist->id; }

const char *getHistoryUserId(const History *hist) { return hist->user_id; }

const char *getHistoryMusicId(const History *hist) { return hist->music_id; }

const char *getHistoryTimestamp(const History *hist) { return hist->timestamp; }

const char *getHistoryDuration(const History *hist) { return hist->duration; }

const char *getHistoryPlatform(const History *hist) { return hist->platform; }

// Funções set
void setHistoryId(History *hist, const char *id) {
  free(hist->id); // Libera a memória antiga, se necessário
  hist->id = strdup(id);
}

void setHistoryUserId(History *hist, const char *user_id) {
  free(hist->user_id);
  hist->user_id = strdup(user_id);
}

void setHistoryMusicId(History *hist, const char *music_id) {
  free(hist->music_id);
  hist->music_id = strdup(music_id);
}

void setHistoryTimestamp(History *hist, const char *timestamp) {
  free(hist->timestamp);
  hist->timestamp = strdup(timestamp);
}

void setHistoryDuration(History *hist, const char *duration) {
  free(hist->duration);
  hist->duration = strdup(duration);
}

void setHistoryPlatform(History *hist, const char *platform) {
  free(hist->platform);
  hist->platform = strdup(platform);
}

History *initHistory() {
  History *hist = malloc(sizeof(struct history));
  if (hist == NULL) {
    printf("Malloc Failed!\n");
    return NULL;
  }

  hist->id = NULL;
  hist->user_id = NULL;
  hist->music_id = NULL;
  hist->timestamp = NULL;
  hist->duration = NULL;
  hist->platform = NULL;

  return hist;
}

void freeHistory(History *hist) {
  free(hist->id);
  free(hist->user_id);
  free(hist->music_id);
  free(hist->timestamp);
  free(hist->duration);
  free(hist->platform);
}
