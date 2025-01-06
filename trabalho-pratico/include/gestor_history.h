#ifndef _GESTORHISTORY_H_
#define _GESTORHISTORY_H_

/**
 * @file gestor_history.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Gestor History`.
 */

typedef struct gestorHistory gestorHistory;

#include "gestor_musics.h"
#include "gestor_users.h"
#include "history.h"
#include "utils.h"
#include <glib.h>
#include <stdio.h>
/**
 * @brief Função para processar uma linha do histórico.
 *
 * Esta função processa uma linha do histórico e atualiza as informações
 * necessárias nas estruturas do sistema, como incrementando o número de álbuns
 * de um artista, guardando informações para as queries 4, 5 e 6, e atualizando
 * o resumo do utilizador na query 6, se necessário.
 *
 * @param history Pointer para o histórico a ser processado.
 * @param line Linha original a ser processada.
 * @param copia Linha copiada para processamento adicional.
 * @param gestor Pointer para o gestor que contém as estruturas necessárias.
 */
void parserHistory(History *history, char *line, char *copia, Gestores *gestor);

/**
 * @brief Função que processa um ficheiro de histórico.
 *
 * Esta função lê o ficheiro de histórico, linha por linha, e chama a função
 * `parserHistory` para processar cada linha válida, inserindo os dados
 * necessários nas hashtables e outras estruturas.
 *
 * @param gestor Pointer para o gestor que contém as estruturas necessárias.
 * @param historyPath Caminho para o ficheiro de histórico.
 * @return int Retorna 1 se o processamento for bem-sucedido, 0 caso contrário.
 */
int GestorHistory(Gestores *gestor, char *historyPath);
#endif