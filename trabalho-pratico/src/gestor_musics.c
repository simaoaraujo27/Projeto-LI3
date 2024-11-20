#include "gestor_musics.h"
#include "gestor_artists.h"
#include "parsers.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Definição completa da estrutura gestorMusics, que contém um ficheiro para
// erros e uma hashtable para músicas
struct gestorMusics {
  FILE *errorsFile;        // Ficheiro para registo de erros
  GHashTable *musicsTable; // Hashtable para armazenar músicas
};

// Função para inicializar a estrutura gestorMusics
// Abre o ficheiro de erros e atribui a hashtable fornecida
gestorMusics *initGestorMusics(const char *errorsFilePath,
                               GHashTable *musicsTable) {
  // Aloca memória para a estrutura
  gestorMusics *gestorMusic = malloc(sizeof(gestorMusics));
  if (!gestorMusic)
    return NULL;

  // Abre o ficheiro para escrita de erros
  gestorMusic->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorMusic->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorMusic);
    return NULL;
  }

  // Atribui a hashtable fornecida
  gestorMusic->musicsTable = musicsTable;
  return gestorMusic;
}

// Função para libertar a estrutura gestorMusics e os seus recursos
void freeGestorMusics(gestorMusics *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    free(gestor);              // Liberta a memória da estrutura
  }
}

// Função para processar o ficheiro de músicas usando a estrutura gestorMusics
int GestorMusics(FILE *fp, gestorMusics *gestorMusic,
                 gestorArtists *gestorArtist, char *musicsPath) {
  // Abre o arquivo de musicas e carrega os dados
  fp = fopen(musicsPath, "r");
  if (fp) {
    char *line = NULL; // Pointer para armazenar cada linha lida
    size_t len = 0;    // Tamanho da linha
    Musics *music = NULL;

    // Ignora a primeira linha do ficheiro (cabeçalho)
    assert(getline(&line, &len, fp) != -1);

    // Lê o ficheiro linha por linha
    while (getline(&line, &len, fp) != -1) {
      // Cria uma cópia da linha para validação
      char *copia = strdup(line);
      parserMusic(copia, gestorArtist, line, music, gestorMusic->musicsTable,
                  gestorMusic->errorsFile);
      free(copia); // Liberta a memória alocada para a cópia da linha
    }

    // Liberta a memória alocada para a linha utilizada pelo getline
    free(line);

    fclose(fp);
  } else {
    perror("Error opening musics file");
    return 0;
  }
  free(musicsPath); // Liberta a memória do path das musicas
  return 1;
}

// Função para obter a hashtable de músicas da estrutura gestorMusics
GHashTable *getMusicsTable(gestorMusics *gestorMusic) {
  return gestorMusic->musicsTable;
}
