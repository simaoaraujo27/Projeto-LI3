#include "gestor_musics.h"
#include "gestor_artists.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Definição completa da estrutura gestorMusics, que contém um ficheiro para
// erros e uma tabela hash para músicas
struct gestorMusics {
  FILE *errorsFile;        // Ficheiro para registo de erros
  GHashTable *musicsTable; // Hash table para armazenar músicas
};

// Função para inicializar a estrutura gestorMusics
// Abre o ficheiro de erros e atribui a tabela hash fornecida
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

  // Atribui a tabela hash fornecida
  gestorMusic->musicsTable = musicsTable;
  return gestorMusic;
}

// Função para liberar a estrutura gestorMusics e seus recursos
void freeGestorMusics(gestorMusics *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    free(gestor);              // Liberta a memória da estrutura
  }
}

// Função para processar o ficheiro de músicas usando a estrutura gestorMusics
void parseMusics(FILE *fp, gestorMusics *gestorMusic,
                 gestorArtists *gestorArtist) {
  char *line = NULL; // Ponteiro para armazenar cada linha lida
  size_t len = 0;    // Tamanho da linha
  char *id;          // ID da música
  Musics *music = NULL;

  // Ignora a primeira linha do ficheiro (cabeçalho)
  assert(getline(&line, &len, fp) != -1);

  // Lê o ficheiro linha por linha
  while (getline(&line, &len, fp) != -1) {
    // Cria uma cópia da linha para validação
    char *copia = strdup(line);
    if (validateMusicsLine(copia, gestorArtist)) {
      // Se a linha for válida, separa os campos e cria um objeto Musics
      music = separateMusics(line);

      // Obtém o ID da música e insere na tabela hash usando o ID como chave
      id = getMusicId(music);
      g_hash_table_insert(gestorMusic->musicsTable, id, music);
    } else {
      // Escreve a linha inválida no ficheiro de erros
      fprintf(gestorMusic->errorsFile, "%s", line);
    }
    free(copia); // Liberta a memória alocada para a cópia da linha
  }

  // Liberta a memória alocada para a linha utilizada pelo getline
  free(line);
}

// Função para obter a tabela hash de músicas da estrutura gestorMusics
GHashTable *getMusicsTable(gestorMusics *gestorMusic) {
  return gestorMusic->musicsTable;
}
