#ifndef _ERROS_H_
#define _ERROS_H_

/**
 * @file erros.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Erros`.
 */
typedef struct ficheiroErrosCSV FicheiroErrosCSV;

/**
 * @brief Inicializa todos os ficheiros de erros.
 *
 * Esta função aloca memória para a estrutura `FicheiroErrosCSV` e abre os
 * ficheiros de erros correspondentes aos diferentes tipos de dados (artists,
 * musics, users, albuns, history). Caso haja falha ao abrir qualquer um dos
 * ficheiros, a função retorna `NULL`.
 *
 * @return Um pointer para a estrutura `FicheiroErrosCSV` contendo os ficheiros
 * de erros abertos, ou `NULL` em caso de erro.
 */
FicheiroErrosCSV *initFicheiroErrosCSV();

/**
 * @brief Escreve uma linha no ficheiro de erros apropriado.
 *
 * Esta função escreve uma linha de erro no ficheiro de erros correspondente ao
 * tipo de dado fornecido (artists, musics, users, albuns, history).
 *
 * @param ficheiroErrosCSV Pointer para a estrutura `FicheiroErrosCSV` contendo
 * os ficheiros de erros.
 * @param typeFile Tipo de dado (artists, musics, users, albuns, history) que
 * determina o ficheiro de erro onde a linha será escrita.
 * @param line A linha de erro a ser escrita no ficheiro.
 */
void WriteErrorsFile(FicheiroErrosCSV *ficheiroErrosCSV, char *typeFile,
                     char *line);

/**
 * @brief Liberta a memória e fecha os ficheiros de erros.
 *
 * Esta função fecha todos os ficheiros de erros abertos na estrutura
 * `FicheiroErrosCSV` e libera a memória alocada para essa estrutura.
 *
 * @param ficheiroErrosCSV Pointer para a estrutura `FicheiroErrosCSV` a ser
 * destruída.
 */
void destroyFicheiroErrosCSV(FicheiroErrosCSV *ficheiroErrosCSV);

#endif
