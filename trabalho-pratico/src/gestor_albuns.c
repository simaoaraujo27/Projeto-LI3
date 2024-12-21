#include "gestor_albuns.h"
#include "albuns.h"
#include <glib.h>
#include <stdio.h>

struct gestorAlbuns {
  FILE *errorsFile;        // Ficheiro para registo de erros
  GHashTable *albunsTable; // Hashtable para armazenar os albuns
};

// Função para inicializar a estrutura gestorAlbuns
gestorAlbuns *initGestorAlbuns(const char *errorsFilePath) {

  GHashTable *albunsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyAlbum);

  // Aloca memória para a estrutura
  gestorAlbuns *gestorAlbuns = malloc(sizeof(gestorAlbuns));
  if (!gestorAlbuns)
    return NULL;

  // Abre o ficheiro para escrita de erros
  gestorAlbuns->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorAlbuns->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorAlbuns);
    return NULL;
  }

  // Atribui a hashtable fornecida
  gestorAlbuns->albunsTable = albunsTable;
  return gestorAlbuns;
}

// Função para libertar a estrutura gestorAlbuns e os seus recursos
void freeGestorAlbuns(gestorAlbuns *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    g_hash_table_destroy(gestor->albunsTable);
    free(gestor); // Liberta a memória da estrutura
  }
}

void parserAlbum(GHashTable *albunsTable, Albuns *album, FILE *errorsFile,
                 char *line) {
  // TODO: ADICIONAR O IF DA VALIDAÇÃO QUANDO ESTIVER FEITO

  // Obtém o ID do album e remove aspas
  char *id = getAlbumId(album);
  remove_quotes(id);

  // Verifica se o album já está presente na hashtable
  Albuns *existingAlbum = g_hash_table_lookup(albunsTable, id);
  if (existingAlbum != NULL) {
    destroyAlbum(existingAlbum);
  }

  // Insere o novo album na tabela hash
  g_hash_table_insert(albunsTable, id, album);
}
/* else {
  // Regista a linha no ficheiro de erros se não for válida
  fprintf(errorsFile, "%s", line);
  destroyAlbum(album); // Liberta a memória do album inválido

} */

// Função para processar o ficheiro de álbuns utilizando a estrutura
// gestorAlbuns
int GestorAlbuns(gestorAlbuns *gestor, char *albunsPath) {
  // Abre o arquivo de albuns e carrega os dados
  FILE *fp = fopen(albunsPath, "r");

  if (fp) {
    char *line = NULL; // Pointer para armazenar cada linha lida
    size_t len = 0;    // Tamanho da linha
    Albuns *album = NULL;

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

        artist = separateAlbuns(line_copy);

        parserAlbum(gestor->albunsTable, album, gestor->errorsFile, line);

        free(line_copy);
      }
    }
    // Liberta a linha utilizada pelo getline
    free(line);

    fclose(fp);
  } else {
    perror("Error opening albuns file");
    return 0;
  }
  free(albunsPath); // Liberta a memoria do path dos albuns
  return 1;
}