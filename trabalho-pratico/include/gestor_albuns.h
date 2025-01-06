#ifndef _GESTORALBUNS_H_
#define _GESTORALBUNS_H_

/**
 * @file gestor_albuns.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Gestor Albuns`.
 */
typedef struct gestorAlbuns gestorAlbuns;

#include "albuns.h"
#include "gestor_artists.h"
#include "gestores.h"
#include <glib.h>
#include <stdio.h>

/**
 * @brief Inicializa o gestor de álbuns e a sua hash table.
 *
 * Esta função cria e inicializa uma nova instância de `gestorAlbuns`, com
 * uma hash table vazia para armazenar os álbuns.
 *
 * @return Um pointer para o gestorAlbuns inicializado.
 */
gestorAlbuns *initGestorAlbuns();

/**
 * @brief Liberta a memória alocada para o gestor de álbuns.
 *
 * Esta função destrói a hash table de álbuns e liberta a memória associada
 * ao gestor de álbuns.
 *
 * @param gestor Pointer para o gestorAlbuns a ser destruído.
 */
void freeGestorAlbuns(gestorAlbuns *gestor);

/**
 * @brief Processa uma linha de dados e insere um álbum na hash table.
 *
 * Esta função valida uma linha de dados referente a um álbum. Caso os dados
 * sejam válidos, o álbum é inserido na hash table. Caso contrário, a linha
 * é registada no ficheiro de erros.
 *
 * @param albunsTable A hash table onde os álbuns serão armazenados.
 * @param album O álbum a ser inserido na hash table.
 * @param gestor O gestor global que contém informações de erros.
 * @param line A linha original de dados referente ao álbum.
 * @param copia A linha de dados duplicada, utilizada para validação.
 * @param gestorArtists O gestor de artistas, utilizado na validação dos dados.
 */
void parserAlbum(GHashTable *albunsTable, Albuns *album, Gestores *gestor,
                 char *line, char *copia, gestorArtists *gestorArtists);

/**
 * @brief Processa o ficheiro de álbuns e insere todos os álbuns na hash table.
 *
 * Esta função abre o ficheiro de álbuns e lê cada linha. Para cada linha válida,
 * ela chama a função `parserAlbum` para inserir o álbum na hash table. Caso ocorra um
 * erro na leitura ou validação, a linha de erro é registada.
 *
 * @param gestor O gestor global que contém as informações necessárias.
 * @param albunsPath O caminho para o ficheiro de álbuns a ser processado.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int GestorAlbuns(Gestores *gestor, char *albunsPath);

/**
 * @brief Verifica se um álbum está presente na hash table.
 *
 * Esta função realiza uma procura na hash table para verificar se um álbum,
 * identificado pela chave, já foi inserido. Caso o álbum seja encontrado, a
 * função retorna TRUE.
 *
 * @param gestorAlbuns Pointer para a estrutura gestorAlbuns.
 * @param key A chave de pesquisa (ID do álbum).
 * @param value O valor correspondente à chave, se encontrado.
 * @param orig_key A chave original fornecida à função, se encontrado.
 * @return Retorna TRUE se o álbum foi encontrado, FALSE caso contrário.
 */
gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key);

#endif
