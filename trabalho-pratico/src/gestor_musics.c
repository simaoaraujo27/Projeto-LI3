#include "gestor_musics.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestores.h"
#include "query2.h"
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
gestorMusics *initGestorMusics(const char *errorsFilePath) {

  // Inicializa a hashtable para musicas
  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);

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
    g_hash_table_destroy(gestor->musicsTable);
    free(gestor); // Liberta a memória da estrutura
  }
}

void colocaIdMusicNosArtists(char *IdComponents, gestorArtists *gestorArtists) {
  removeFstLast(IdComponents);
  removeFstLast(IdComponents);
  int l = (int)strlen(IdComponents);
  char *key = NULL;
  gpointer value;
  gpointer orig_key;
  /* int solo = 0;
  if (l - 12 <= 0)
    solo = 1; */
  // Processa os IDs das músicas
  while (l > 0) {
    if (l == (int)strlen(IdComponents)) {
      IdComponents = IdComponents + 1;
    } else
      IdComponents = IdComponents + 3;
    key = strdup(strsep(&IdComponents, "'")); // Separa o ID da música
    key[8] = '\0';                            // Limita o ID a 8 caracteres
    lookUpArtistsHashTable(gestorArtists, key, &value, &orig_key);
    // ColocaIdMusicInArtist(&orig_key, IdMusic, solo);
    l -= 12;
  }
  free(key);
}

void parserMusic(char *copia, gestorArtists *gestorArtist, char *line,
                 Musics *music, GHashTable *musicsTable, FILE *errorsFile,
                 gestorAlbuns *gestorAlbuns) {
  char *id; // ID da música
  if (validateMusicsLine(copia, gestorArtist, gestorAlbuns)) {
    // Se a linha for válida, separa os campos e cria um objeto Musics
    music = separateMusics(line);
    colocaIdMusicNosArtists(getMusicArtistId(music), gestorArtist);
    //  Obtém o ID da música e insere na hashtable usando o ID como chave
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);
  } else {
    // Escreve a linha inválida no ficheiro de erros
    fprintf(errorsFile, "%s", line);
  }
}

// Função para processar o ficheiro de músicas usando a estrutura gestorMusics
int GestorMusics(gestorMusics *gestorMusic, gestorArtists *gestorArtist,
                 gestorAlbuns *gestorAlbuns, char *musicsPath) {
  // Abre o arquivo de musicas e carrega os dados
  FILE *fp = fopen(musicsPath, "r");
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
                  gestorMusic->errorsFile, gestorAlbuns);
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

GHashTableIter iterInitMusicsHashTable(gestorMusics *gestorMusics) {
  // Iterador para percorrer a hashtable das músicas
  GHashTableIter iter;
  g_hash_table_iter_init(
      &iter, getMusicsTable(
                 gestorMusics)); // Inicializa o iterador da tabela de músicas
  return iter;
}

gboolean iter_HashTableMusics(gpointer *key1, gpointer *value1,
                              GHashTableIter iter) {

  return g_hash_table_iter_next(&iter, key1, value1);
}

gboolean lookUpMusicsHashTable(gestorMusics *gestorMusic, char *line,
                               gpointer *value, gpointer *orig_key) {
  // Procura o music na hashtable usando a chave fornecida (line)
  gboolean found = g_hash_table_lookup_extended(gestorMusic->musicsTable, line,
                                                value, orig_key);
  return found;
}

void processAllMusics(gestorMusics *gestorMusics, int numeroArtistas,
                      char *country, GList **listaResposta,
                      gestorArtists *gestorArtists) {
  // Inicializa o iterador para a hashtable das músicas
  GHashTableIter iter;
  iter = iterInitMusicsHashTable(gestorMusics);
  gpointer key1, value1;

  // Percorre todas as músicas na hashtable
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1; // Obtém a música atual
    char *artistsId = pegarMusicArtistId(music);
    processMusic(music, gestorArtists, numeroArtistas, country, listaResposta,
                 artistsId);
    free(artistsId);
  }
}