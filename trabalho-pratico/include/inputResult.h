/**
 * @file inputResult.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do inputResult
 */
#ifndef _INPUTRESULT_H_
#define _INPUTRESULT_H_

/**
 * @brief Cria um arquivo de resultados com base em um índice.
 *
 * Esta função cria um arquivo de texto na pasta "resultados" com um nome baseado
 * no índice fornecido, permitindo gerar arquivos distintos para cada comando.
 *
 * @param i Índice que será incluído no nome do arquivo.
 * @return Um pointer para o arquivo recém-criado ou NULL em caso de falha.
 * @note O arquivo será criado com a extensão `.txt` e será aberto para escrita.
 */
FILE *createFile(int i);


#endif