/**
 * @file utils.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file para utilitários e funções auxiliares.
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>
#include <stdbool.h>

/**
 * @brief Converte um tempo no formato HH:MM:SS para segundos.
 * @param tempo String representando o tempo no formato HH:MM:SS.
 * @return Tempo convertido em segundos.
 */
int converterParaSegundos(char *tempo);

/**
 * @brief Calcula o número de dias desde 09/09/2024 até a data especificada.
 * @param data String representando a data no formato DD/MM/YYYY.
 * @return Número de dias desde 09/09/2024.
 */
int calcularDiasAte_9_9_2024(char *data);

/**
 * @brief Converte uma string para minúsculas.
 * @param word String a ser convertida.
 */
void colocaTudoMinusculo(char *word);

/**
 * @brief Remove as aspas de uma string.
 * @param str String da qual as aspas serão removidas.
 */
void remove_quotes(char *str);

/**
 * @brief Encontra a primeira ocorrência de um caractere em uma string.
 * @param line String onde o caractere será procurado.
 * @param carac Caractere a ser localizado.
 * @return Índice da primeira ocorrência ou -1 se não encontrado.
 */
int primeiraOcorr(char *line, char carac);

/**
 * @brief Verifica se uma string contém aspas.
 * @param line String a ser verificada.
 * @return 1 se houver aspas, 0 caso contrário.
 */
int temAspas(char *line);

/**
 * @brief Remove o primeiro e o último caractere de uma string.
 * @param str String a ser modificada.
 */
void removeFstLast(char *str);

/**
 * @brief Remove o último caractere de uma string.
 * @param str String a ser modificada.
 */
void removeLast(char *str);

/**
 * @brief Calcula a idade a partir da data de nascimento fornecida.
 * @param birth_date Data de nascimento no formato DD/MM/YYYY.
 * @return String representando a idade calculada.
 */
char *calculate_age_str(char *birth_date);

/**
 * @brief Converte um número inteiro para uma string.
 * @param number Número inteiro a ser convertido.
 * @return String representando o número.
 */
char *intToString(int number);

/**
 * @brief Converte um número de segundos em uma string no formato HH:MM:SS.
 * @param number Número de segundos a ser convertido.
 * @return String formatada como HH:MM:SS.
 */
char *intToHour(int number);

/**
 * @brief Converte segundos para uma string de tempo formatada.
 * @param segundos Número de segundos a serem convertidos.
 * @param resultado String onde o resultado será armazenado.
 */
void converterParaTempo(int segundos, char *resultado);

/**
 * @brief Calcula o dia do ano a partir de uma string de data.
 * @param diaStr String representando a data.
 * @return Dia do ano correspondente.
 */
int calculateDiaAno(char *diaStr);

/**
 * @brief Verifica se um ano é bissexto.
 * @param year Ano a ser verificado.
 * @return 1 se for bissexto, 0 caso contrário.
 */
int isLeapYear(int year);

/**
 * @brief Calcula a data a partir do dia do ano e do ano fornecidos.
 * @param diaAno Dia do ano.
 * @param year Ano de referência.
 * @return String representando a data calculada no formato DD/MM/YYYY.
 */
char *calculateData(int diaAno, int year);

/**
 * @brief Limpa o buffer de entrada.
 */
void limparBufferEntrada();

/**
 * @brief Valida se o caminho fornecido é válido.
 * @param path Caminho a ser validado.
 * @return true se for válido, false caso contrário.
 */
bool validaPath(const char *path);

/**
 * @brief Remove o caractere de nova linha de uma string.
 * @param str String da qual o caractere será removido.
 */
void removerNovaLinha(char *str);

/**
 * @brief Imprime uma linha completa de caracteres coloridos.
 * @param ch Caractere a ser repetido.
 * @param color Cor a ser utilizada.
 */
void printFullLine(char ch, const char *color);

/**
 * @brief Imprime um texto centralizado e colorido.
 * @param text Texto a ser impresso.
 * @param color Cor do texto.
 */
void printCentered(const char *text, const char *color);

/**
 * @brief Imprime um texto em RGB.
 * @param text Texto a ser impresso.
 */
void printRGB(const char *text);

/**
 * @brief Escolhe o separador de campos para impressão.
 * @param separador Separador a ser utilizado.
 */
void escolheSeparador(char *separador);

/**
 * @brief Imprime os resultados formatados para múltiplas queries.
 * @param nQueries Número de queries.
 */
void printResults(int nQueries);

/**
 * @brief Imprime um texto em vermelho.
 * @param text Texto a ser impresso.
 */
void printRed(const char *text);

/**
 * @brief Lê e valida um número inteiro.
 * @return Número inteiro válido lido.
 */
int lerNumeroValido();

#endif
