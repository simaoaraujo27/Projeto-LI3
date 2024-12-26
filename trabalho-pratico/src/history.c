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
char *getHistoryId(History *hist) { return strdup(hist->id); }

char *getHistoryUserId(History *hist) { return strdup(hist->user_id); }

char *getHistoryMusicId(History *hist) { return strdup(hist->music_id); }

char *getHistoryTimestamp(History *hist) { return strdup(hist->timestamp); }

char *getHistoryDuration(History *hist) { return strdup(hist->duration); }

char *getHistoryPlatform(History *hist) { return strdup(hist->platform); }

// Funções set
void setHistoryId(History *hist, char *id) {
  free(hist->id); // Libera a memória antiga, se necessário
  hist->id = strdup(id);
}

void setHistoryUserId(History *hist, char *user_id) {
  free(hist->user_id);
  hist->user_id = strdup(user_id);
}

void setHistoryMusicId(History *hist, char *music_id) {
  free(hist->music_id);
  hist->music_id = strdup(music_id);
}

void setHistoryTimestamp(History *hist, char *timestamp) {
  free(hist->timestamp);
  hist->timestamp = strdup(timestamp);
}

void setHistoryDuration(History *hist, char *duration) {
  free(hist->duration);
  hist->duration = strdup(duration);
}

void setHistoryPlatform(History *hist, char *platform) {
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

void destroyHistory(History *hist) {
  free(hist->id);
  free(hist->user_id);
  free(hist->music_id);
  free(hist->timestamp);
  free(hist->duration);
  free(hist->platform);
}

// Função que separa dados do history a partir de uma linha do CSV
History *separateHistory(char *line) {
  History *history = initHistory();
  char *token = strdup(strsep(&line, ";"));
  setHistoryId(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setHistoryUserId(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setHistoryMusicId(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setHistoryTimestamp(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setHistoryDuration(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setHistoryPlatform(history, token);
  free(token);
  token = strdup(strsep(&line, ";"));

  return history;
}
