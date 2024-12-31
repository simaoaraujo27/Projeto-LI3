#include "gestor_artists.h"
#include "artists.h"
#include "minHeap.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>

// Definição completa da estrutura gestorArtists, que contém um ficheiro para
// erros e uma hashtable para artistas
struct gestorArtists {
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *artistsTable; // Hashtable para armazenar os artistas
  GArray *Tops10;           // tops 10 artistas por semana
};

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
  GArray *Tops10 = g_array_new(FALSE, FALSE, sizeof(MinHeap *));
  g_array_set_size(Tops10, 329);
  for (int i = 0; i < (int)Tops10->len; i++) {
    g_array_index(Tops10, MinHeap *, i) =
        NULL; // Inicializa cada posição com NULL
  }

  gestor->Tops10 = Tops10;

  // Atribui a tabela hash fornecida
  gestor->artistsTable = artistsTable;
  return gestor;
}

void freeGArrayQuery4(GArray *Tops10) {
  for (int i = 0; i < (int)Tops10->len; i++) {
    MinHeap *heap = g_array_index(Tops10, MinHeap *, i);
    if (heap != NULL) {
      freeMinHeap(heap);
    }
  }
  g_array_free(Tops10, false);
}
void freeGestorArtists(struct gestorArtists *gestor) {
  if (gestor != NULL) {
    // Feche o arquivo de erros, se aberto
    if (gestor->errorsFile != NULL) {
      fclose(gestor->errorsFile);
    }

    // Libere a tabela hash
    if (gestor->artistsTable != NULL) {
      // Supondo que as chaves e valores precisam ser liberados
      g_hash_table_destroy(gestor->artistsTable);
    }

    // Libere o array GArray
    if (gestor->Tops10 != NULL) {
      // Para cada elemento na GArray (supondo que seja ponteiros para algo que
      // precisa ser liberado)
      for (guint i = 0; i < gestor->Tops10->len; i++) {
        gpointer elem = g_array_index(gestor->Tops10, gpointer, i);
        if (elem != NULL) {
          g_free(elem); // Libere o elemento se necessário
        }
      }
      g_array_free(gestor->Tops10, TRUE);
    }

    // Finalmente, libere a estrutura principal
    free(gestor);
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
  return 1;
}

// Função para obter a hashtable de artistas da estrutura gestorArtists
GHashTable *getArtistTable(gestorArtists *gestorArtist) {
  return gestorArtist->artistsTable;
}

GArray *getGArrayTops10(gestorArtists *gestorArtists) {
  return gestorArtists->Tops10;
}

gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *key,
                                gpointer *value, gpointer *orig_key) {
  // Procura o artist na hashtable usando a chave fornecida (key)
  gboolean found = g_hash_table_lookup_extended(gestorArtist->artistsTable, key,
                                                orig_key, value);
  return found;
}

void incrementArtistsNumAlbuns(char *artistId, gestorArtists *gestorArtist) {
  gpointer value;
  gpointer orig_key;
  int num = 0;
  gboolean found =
      lookUpArtistsHashTable(gestorArtist, artistId, &orig_key, &value);
  if (found) { // encontra sempre
    num = getArtistNumAlbunsIndividual(orig_key);
    num++;
    alterarArtistNumAlbunsIndividual(orig_key, num);
  }
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

// Inicializa a discografia de todos os artistas a zero
void colocaZeroVezesTop10(gestorArtists *GestorArtists) {
  GHashTableIter iter;
  g_hash_table_iter_init(
      &iter, GestorArtists
                 ->artistsTable); // Inicializa o iterador da tabela de músicas

  gpointer key1;
  gpointer value1;

  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Artists *artist = (Artists *)value1;
    putArtistsVezesTop10Zero(artist);
  }
}