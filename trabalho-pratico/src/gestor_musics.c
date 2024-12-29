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
  GHashTable *genresTable; // Hashtable para armazenar os diferentes géneros
                           // (para ser usado na Query 5)
  int *nGeneros; // Contador do número de géneros (para ser usado na Query 5)
};

// Função para inicializar a estrutura gestorMusics
// Abre o ficheiro de erros e atribui a hashtable fornecida
gestorMusics *initGestorMusics(const char *errorsFilePath) {

  // Inicializa a hashtable para musicas
  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);

  GHashTable *genresTable = g_hash_table_new(g_str_hash, g_str_equal);

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
  gestorMusic->genresTable = genresTable;

  gestorMusic->nGeneros = malloc(sizeof(int *));
  *(gestorMusic->nGeneros) = 0;
  return gestorMusic;
}

// Função para libertar a estrutura gestorMusics e os seus recursos
void freeGestorMusics(gestorMusics *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    g_hash_table_destroy(gestor->musicsTable);
    g_hash_table_destroy(gestor->genresTable);
    free(gestor->nGeneros);
    free(gestor); // Liberta a memória da estrutura
  }
}

void addGenre(GHashTable *genresTable, int *nGeneros, char *genre) {
  if (!g_hash_table_contains(genresTable, genre)) {
    g_hash_table_insert(genresTable, (gpointer)genre, NULL);
    (*nGeneros)++;
  }
}

char **insertGenreToArray(gestorMusics *gestorMusics, int numGeneros) {
  // Aloca memória para o array de ponteiros para char
  char **valuesArray = (char **)malloc(numGeneros * sizeof(char *));
  if (valuesArray == NULL) {
    perror("Falha na alocação de memória para o array");
    exit(1);
  }

  GHashTableIter iter;
  g_hash_table_iter_init(&iter, gestorMusics->genresTable);

  gpointer key1;
  gpointer value1;
  int i = 0;

  // Itera sobre os elementos da GHashTable e armazena os valores no array
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    // Verifique se value1 é um ponteiro válido para uma string
    if (key1 != NULL) {
      valuesArray[i] = "";
      char *genre = strdup((char *)key1);
      // printf("%s\n", genre);
      if (genre == NULL) {
        perror("Falha na alocação de memória para a string");
        return NULL;
      }
      valuesArray[i++] = genre;
    }
  }

  return valuesArray;
}

void parserMusic(char *copia, gestorArtists *gestorArtist, char *line,
                 Musics *music, GHashTable *musicsTable, FILE *errorsFile,
                 gestorAlbuns *gestorAlbuns, GHashTable *genresTable,
                 int *nGeneros) {
  char *id;    // ID da música
  char *genre; // Género da música
  if (validateMusicsLine(copia, gestorArtist, gestorAlbuns)) {
    // Se a linha for válida, separa os campos e cria um objeto Musics
    music = separateMusics(line);

    //  Obtém o ID da música e insere na hashtable usando o ID como chave
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);

    genre = getMusicGenre(music);
    addGenre(genresTable, nGeneros, genre);
    free(genre);
    genre = NULL;
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
                  gestorMusic->errorsFile, gestorAlbuns,
                  gestorMusic->genresTable, gestorMusic->nGeneros);
      free(copia); // Liberta a memória alocada para a cópia da linha
    }

    // Liberta a memória alocada para a linha utilizada pelo getline
    free(line);

    fclose(fp);
  } else {
    perror("Error opening musics file");
    return 0;
  }
  return 1;
}

// Função para obter a hashtable de músicas da estrutura gestorMusics
GHashTable *getMusicsTable(gestorMusics *gestorMusic) {
  return gestorMusic->musicsTable;
}

int getMusicsNGenres(gestorMusics *gestorMusic) {
  int *i = gestorMusic->nGeneros;
  return *i;
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

void incrementMusicRep(char *musicId, gestorMusics *gestorMusics,
                       gestorArtists *gestorArtists) {
  gpointer value0;
  gpointer orig_key0;

  remove_quotes(musicId);
  gboolean found1 =
      lookUpMusicsHashTable(gestorMusics, musicId, &value0, &orig_key0);

  if (found1) {

    char *artistId = getMusicArtistId(orig_key0);
    char *artistIdOriginal = artistId;
    remove_quotes(artistId);
    removeFstLast(artistId);

    int lentghArtistId = (int)strlen(artistId); // esta certo

    char *currentArtist = NULL;
    gpointer orig_key;
    gpointer value;
    gpointer orig_key1;
    gpointer value1;

    while (lentghArtistId > 0) {
      if (lentghArtistId == (int)strlen(artistId)) {
        artistId = artistId + 1;
      } else
        artistId = artistId + 3;
      currentArtist = strdup(strsep(&artistId, "'")); // Separa o ID do artista
      currentArtist[8] = '\0'; // Limita o ID a 8 caracteres
      gboolean found = lookUpArtistsHashTable(gestorArtists, currentArtist,
                                              &orig_key, &value);
      if (found) {
        char *type = getArtistTypeStr(orig_key);

        float recipe_Per_Stream =
            getArtistRecipePerStream(orig_key); // esta certo

        float receitaTotal = recipe_Per_Stream;

        float receitaAntiga = getArtistReceitaTotal(orig_key);

        float receitaAtualizada = receitaAntiga + receitaTotal;

        setArtistReceitaTotal(orig_key, receitaAtualizada);

        if (strcmp(type, "group") == 0) {

          int NumComponentesBanda = getArtistTamanhoGrupo(orig_key);

          char *idComponentes = getArtistIdConstituent(orig_key);
          char *idComponentesOriginal = idComponentes;

          remove_quotes(idComponentes);
          removeFstLast(idComponentes);
          int TamanhoIdComponentes = (int)strlen(idComponentes);

          while (TamanhoIdComponentes > 0) {
            if (TamanhoIdComponentes == (int)strlen(idComponentes)) {
              idComponentes = idComponentes + 1;
            } else
              idComponentes = idComponentes + 3;
            char *currentComponent = strdup(strsep(&idComponentes, "'"));
            currentComponent[8] = '\0'; // Limita o ID a 8 caracteres
            lookUpArtistsHashTable(gestorArtists, currentComponent, &orig_key1,
                                   &value1);

            float receitaAntigaComp = getArtistReceitaTotal(orig_key1);
            setArtistReceitaTotal(
                orig_key1, receitaAntigaComp +
                               (receitaTotal / (float)NumComponentesBanda));
            TamanhoIdComponentes -= 12;
            free(currentComponent);
          }
          free(idComponentesOriginal);
        }
      }
      lentghArtistId -= 12; // Ajusta o comprimento restante da string
      free(currentArtist);
      currentArtist = NULL;
    }

    free(artistIdOriginal);
  }
}

char *getMusicGenreById(char *musicId, gestorMusics *gestorMusics) {
  gpointer value;
  gpointer orig_key;
  gboolean found =
      lookUpMusicsHashTable(gestorMusics, musicId, &value, &orig_key);
  if (found) {
    char *genre = getMusicGenre(orig_key);
    return genre;
  }
  return NULL;
}