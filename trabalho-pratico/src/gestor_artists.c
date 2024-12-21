#include "gestor_artists.h"
#include "artists.h"
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
gestorArtists *initGestorArtists(const char *errorsFilePath) {

  // Inicializa a hashtable para os artistas
  GHashTable *artistsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);
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
    g_hash_table_destroy(gestor->artistsTable);
    free(gestor); // Liberta a memória da estrutura
  }
}

void parserArtist(GHashTable *ArtistsTable, Artists *artist, FILE *errorsFile,
                  char *line) {
  // Extrai informações do artista para validação
  char *idConstituentLine = pegarArtistIdConstituent(artist);
  char *idConstituentCSV = pegarArtistIdConstituent(artist);
  char *type = pegarArtistType(artist);

  // Valida a linha e a lista de constituintes
  if (validateArtistLine(idConstituentLine, type) &&
      validateCSVList(idConstituentCSV)) {

    // Obtém o ID do artista e remove aspas
    char *id = getArtistId(artist);
    remove_quotes(id);

    // Verifica se o artista já está presente na hashtable
    Artists *existing_artist = g_hash_table_lookup(ArtistsTable, id);
    if (existing_artist != NULL) {
      destroyArtist(existing_artist); // Liberta o artista duplicado
    }

    // Insere o novo artista na tabela hash
    g_hash_table_insert(ArtistsTable, id, artist);
  } else {
    // Regista a linha no ficheiro de erros se não for válida
    fprintf(errorsFile, "%s", line);
    destroyArtist(artist); // Liberta a memória do artista inválido
  }
  free(idConstituentLine);
  free(idConstituentCSV);
  free(type);
}

// Função para processar o ficheiro de artistas utilizando a estrutura
// gestorArtists
int GestorArtists(gestorArtists *gestor, char *artistsPath) {
  // Abre o arquivo de artistas e carrega os dados
  FILE *fp = fopen(artistsPath, "r"); 

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

gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *key,
                                gpointer *value, gpointer *orig_key) {
  // Procura o artist na hashtable usando a chave fornecida (key)
  gboolean found = g_hash_table_lookup_extended(gestorArtist->artistsTable, key,
                                                orig_key, value);
  return found;
}

// Inicializa a discografia de todos os artistas a zero
void colocaZero(gestorArtists *GestorArtists) {
  GHashTableIter iter;
  g_hash_table_iter_init(
      &iter, GestorArtists
                 ->artistsTable); // Inicializa o iterador da tabela de músicas

  gpointer key1;
  gpointer value1;

  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Artists *artist = (Artists *)value1;
    putArtistsDiscografyZero(artist);
  }
}