#include "gestor_artists.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Definição completa da estrutura gestorArtists, que contém um ficheiro para
// erros e uma tabela hash para artistas
struct gestorArtists {
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *artistsTable; // Hash table para armazenar os artistas
};

// Função para inicializar a estrutura gestorArtists
// Abre o ficheiro de erros e atribui a tabela hash fornecida
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
void parseArtists(FILE *fp, gestorArtists *gestor) {
  char *line = NULL; // Ponteiro para armazenar cada linha lida
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

      // Extrai informações do artista para validação
      char *idConstituentLine = pegarArtistIdConstituent(artist);
      char *idConstituentCSV = pegarArtistIdConstituent(artist);
      char *type = pegarArtistType(artist);

      // Valida a linha e a lista de constituintes
      if (validateArtistLine(idConstituentLine, type) &&
          validateCSVList(idConstituentCSV)) {

        // Obtém o ID do artista e remove aspas, se presentes
        char *id = getArtistId(artist);
        remove_quotes(id);

        // Verifica se o artista já está presente na tabela hash
        Artists *existing_artist =
            g_hash_table_lookup(gestor->artistsTable, id);
        if (existing_artist != NULL) {
          destroyArtist(existing_artist); // Liberta o artista duplicado
        }

        // Insere o novo artista na tabela hash
        g_hash_table_insert(gestor->artistsTable, id, artist);
      } else {
        // Regista a linha no ficheiro de erros se não for válida
        fprintf(gestor->errorsFile, "%s", line);
        destroyArtist(artist); // Liberta a memória do artista inválido
      }

      // Liberta a memória alocada para a linha duplicada e variáveis auxiliares
      free(line_copy);
      free(idConstituentLine);
      free(idConstituentCSV);
      free(type);
    }
  }
  // Liberta a linha utilizada pelo getline
  free(line);
}

// Função para obter a tabela hash de artistas da estrutura gestorArtists
GHashTable *getArtistTable(gestorArtists *gestorArtist) {
  return gestorArtist->artistsTable;
}
