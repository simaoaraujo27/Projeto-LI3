#include "gestor_artists.h"
#include "parsers.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Definição completa da estrutura gestorArtists, que contém um ficheiro para
// erros e uma hashtable para artistas
struct gestorArtists {
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *artistsTable; // Hashtable para armazenar os artistas
};

// Função para inicializar a estrutura gestorArtists
// Abre o ficheiro de erros e atribui a hashtable fornecida
gestorArtists *initGestorArtists(const char *errorsFilePath,
                                 GHashTable *artistsTable) {
  gestorArtists *gestor =
      malloc(sizeof(gestorArtists)); // Aloca memória para a estrutura
  if (!gestor)
    return NULL;

  // Abre o ficheiro para escrita de erros
  gestor->errorsFile = fopen(errorsFilePath, "w");
  if (!gestor->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestor);
    return NULL;
  }

  // Atribui a tabela hash fornecida
  gestor->artistsTable = artistsTable;
  return gestor;
}

// Função para libertar os recursos da estrutura gestorArtists
void freeGestorArtists(gestorArtists *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile); // Fecha o ficheiro de erros, se aberto
    free(gestor);                 // Liberta a memória da estrutura
  }
}

// Função para processar o ficheiro de artistas utilizando a estrutura
// gestorArtists
int GestorArtists(FILE *fp, gestorArtists *gestor, char *artistsPath) {
  // Abre o arquivo de artistas e carrega os dados
  fp = fopen(artistsPath, "r");
  if (fp) {

    char *line = NULL; // Pointer para armazenar cada linha lida
    size_t len = 0;    // Tamanho da linha
    Artists *artist = NULL;

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

        // Cria um objeto Artists a partir da linha lida
        artist = separateArtists(line_copy);

        parserArtist(gestor->artistsTable, artist, gestor->errorsFile, line);

        // Liberta a memória alocada para a linha duplicada e variáveis
        // auxiliares
        free(line_copy);
      }
    }
    // Liberta a linha utilizada pelo getline
    free(line);

    fclose(fp);
  } else {
    perror("Error opening artists file");
    return 0;
  }
  free(artistsPath); // Liberta a memoria do path dos artistas
  return 1;
}

// Função para obter a hashtable de artistas da estrutura gestorArtists
GHashTable *getArtistTable(gestorArtists *gestorArtist) {
  return gestorArtist->artistsTable;
}
