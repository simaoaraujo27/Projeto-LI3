#include "erros.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>

struct ficheiroErrosCSV {
  FILE *errorsFileArtists;
  FILE *errorsFileMusics;
  FILE *errorsFileUsers;
  FILE *errorsFileAlbuns;
  FILE *errorsFileHistory;
};

FicheiroErrosCSV *initFicheiroErrosCSV() {
  FicheiroErrosCSV *ficheiroErrosCSV = malloc(sizeof(FicheiroErrosCSV));
  const char *errorsFilePathArtists = "./resultados/artists_errors.csv";
  const char *errorsFilePathMusics = "./resultados/musics_errors.csv";
  const char *errorsFilePathUsers = "./resultados/users_errors.csv";
  const char *errorsFilePathAlbuns = "./resultados/albums_errors.csv";
  const char *errorsFilePathHistory = "./resultados/history_errors.csv";

  ficheiroErrosCSV->errorsFileArtists = fopen(errorsFilePathArtists, "w");
  if (!ficheiroErrosCSV->errorsFileArtists) {
    perror("Erro ao abrir o ficheiro de erros");
    free(ficheiroErrosCSV);
    return NULL;
  }
  ficheiroErrosCSV->errorsFileMusics = fopen(errorsFilePathMusics, "w");
  if (!ficheiroErrosCSV->errorsFileMusics) {
    perror("Erro ao abrir o ficheiro de erros");
    free(ficheiroErrosCSV);
    return NULL;
  }
  ficheiroErrosCSV->errorsFileUsers = fopen(errorsFilePathUsers, "w");
  if (!ficheiroErrosCSV->errorsFileUsers) {
    perror("Erro ao abrir o ficheiro de erros");
    free(ficheiroErrosCSV);
    return NULL;
  }
  ficheiroErrosCSV->errorsFileAlbuns = fopen(errorsFilePathAlbuns, "w");
  if (!ficheiroErrosCSV->errorsFileAlbuns) {
    perror("Erro ao abrir o ficheiro de erros");
    free(ficheiroErrosCSV);
    return NULL;
  }
  ficheiroErrosCSV->errorsFileHistory = fopen(errorsFilePathHistory, "w");
  if (!ficheiroErrosCSV->errorsFileHistory) {
    perror("Erro ao abrir o ficheiro de erros");
    free(ficheiroErrosCSV);
    return NULL;
  }
  return ficheiroErrosCSV;
}

void WriteErrorsFile(FicheiroErrosCSV *ficheiroErrosCSV, char *typeFile,
                     char *line) {
  if (strcmp(typeFile, "artists") == 0) {
    fprintf(ficheiroErrosCSV->errorsFileArtists, "%s", line);
  } else if (strcmp(typeFile, "musics") == 0) {
    fprintf(ficheiroErrosCSV->errorsFileMusics, "%s", line);
  } else if (strcmp(typeFile, "users") == 0) {
    fprintf(ficheiroErrosCSV->errorsFileUsers, "%s", line);
  } else if (strcmp(typeFile, "albuns") == 0) {
    fprintf(ficheiroErrosCSV->errorsFileAlbuns, "%s", line);
  } else if (strcmp(typeFile, "history") == 0) {
    fprintf(ficheiroErrosCSV->errorsFileHistory, "%s", line);
  } else {
    printf("Tipo de file errado!!!");
  }
}

void destroyFicheiroErrosCSV(FicheiroErrosCSV *ficheiroErrosCSV) {
  if (!ficheiroErrosCSV) {
    return; // Evita acessar um ponteiro nulo.
  }

  // Fecha os arquivos, se estiverem abertos.
  if (ficheiroErrosCSV->errorsFileArtists) {
    fclose(ficheiroErrosCSV->errorsFileArtists);
  }

  if (ficheiroErrosCSV->errorsFileMusics) {
    fclose(ficheiroErrosCSV->errorsFileMusics);
  }

  if (ficheiroErrosCSV->errorsFileUsers) {
    fclose(ficheiroErrosCSV->errorsFileUsers);
  }

  if (ficheiroErrosCSV->errorsFileAlbuns) {
    fclose(ficheiroErrosCSV->errorsFileAlbuns);
  }

  if (ficheiroErrosCSV->errorsFileHistory) {
    fclose(ficheiroErrosCSV->errorsFileHistory);
  }

  // Libera a memória alocada para a estrutura.
  free(ficheiroErrosCSV);
}
