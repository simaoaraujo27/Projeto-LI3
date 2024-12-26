#include "gestor_history.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "history.h"
#include "query4.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>

struct gestorHistory {
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *historyTable; // Hashtable para armazenar o history
};

// Função para inicializar a estrutura gestorHistory
gestorHistory *initGestorHistory(const char *errorsFilePath) {

  GHashTable *gestorTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyHistory);

  // Aloca memória para a estrutura
  gestorHistory *gestorHistory = malloc(sizeof(struct gestorHistory));
  if (!gestorHistory)
    return NULL;

  // Abre o ficheiro para escrita de erros
  gestorHistory->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorHistory->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorHistory);
    return NULL;
  }

  // Atribui a hashtable fornecida
  gestorHistory->historyTable = gestorTable;
  return gestorHistory;
}

// Função para libertar a estrutura gestorHistory e os seus recursos
void freeGestorHistory(gestorHistory *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(
          gestor->errorsFile); // Fecha o ficheiro de erros, se estiver aberto
    g_hash_table_destroy(gestor->historyTable);
    free(gestor); // Liberta a memória da estrutura
  }
}

void parserHistory(GHashTable *historyTable, History *history, FILE *errorsFile,
                   char *line, char *copia, gestorMusics *gestorMusics,
                   gestorArtists *gestorArtists) {
  // TODO: ADICIONAR O IF DA VALIDAÇÃO QUANDO ESTIVER FEITO
  // ESTE IF É SÓ PARA NÃO DAR ERRO PORQUE AINDA FALTA A VALIDAÇÃO
  if (validateHistoryLine(copia)) {
    // Obtém o ID do history e remove aspas
    char *id = getHistoryId(history);
    remove_quotes(id);

    // Insere o novo history na tabela hash
    g_hash_table_insert(historyTable, id, history);

    char *musicId = getHistoryMusicId(history);
    incrementMusicRep(musicId, gestorMusics, gestorArtists);


//--- para a query4
    remove_quotes(musicId);
    char *timeStamp = getHistoryTimestamp(history);
    remove_quotes(timeStamp);
    int dias = calcularDiasAte_9_9_2024(timeStamp);
    char *durationStr = getHistoryDuration(history);
    remove_quotes(durationStr);
    int durationSeg = converterParaSegundos(durationStr);

    armazenarValores(musicId, durationSeg, dias, gestorMusics, gestorArtists,
                     getGArrayTops10(gestorArtists));

    free(musicId);

  } else {
    // Escreve a linha inválida no ficheiro de erros
    fprintf(errorsFile, "%s", line);
  }
}

// Função para processar o ficheiro de history utilizando a estrutura
// gestorHistory
int GestorHistory(gestorHistory *gestor, gestorMusics *gestorMusic,
                  gestorArtists *gestorArtists, char *historyPath) {
  // Abre o arquivo de history e carrega os dados
  FILE *fp = fopen(historyPath, "r");

  if (fp) {
    char *line = NULL; // Pointer para armazenar cada linha lida
    size_t len = 0;    // Tamanho da linha
    History *history = NULL;

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

        history = separateHistory(line_copy);

        char *currentMusic = getHistoryMusicId(history);
        gpointer orig_key;
        gpointer value;
        lookUpMusicsHashTable(gestorMusic, currentMusic, &value, &orig_key);

        char *copia = strdup(line);
        parserHistory(gestor->historyTable, history, gestor->errorsFile, line,
                      copia, gestorMusic, gestorArtists);
        free(copia);
        free(line_copy);
        free(currentMusic);
      }
    }
    // Liberta a linha utilizada pelo getline
    free(line);
    fclose(fp);
  } else {
    perror("Error opening history file");
    return 0;
  }
  return 1;
}