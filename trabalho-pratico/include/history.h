/**
 * @file history.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do history
 */
#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct history History;


/**
 * @brief Obtém o ID do histórico.
 *
 * Função que retorna o ID do histórico armazenado na struct.
 *
 * @param hist Pointer para a struct History.
 * @return O ID do histórico, como uma string.
 */
char *getHistoryId(History *hist);

/**
 * @brief Obtém o ID do utilizador no histórico.
 *
 * Função que retorna o ID do utilizador associado ao histórico.
 *
 * @param hist Pointer para a struct History.
 * @return O ID do utilizador, como uma string.
 */
char *getHistoryUserId(History *hist);

/**
 * @brief Obtém o ID da música no histórico.
 *
 * Função que retorna o ID da música associada ao histórico.
 *
 * @param hist Pointer para a struct History.
 * @return O ID da música, como uma string.
 */
char *getHistoryMusicId(History *hist);

/**
 * @brief Obtém o timestamp do histórico.
 *
 * Função que retorna a data e hora em que a música foi ouvida, associada ao histórico.
 *
 * @param hist Pointer para a struct History.
 * @return O timestamp, como uma string.
 */
char *getHistoryTimestamp(History *hist);

/**
 * @brief Obtém a duração da audição da música no histórico.
 *
 * Função que retorna a duração da audição da música registada no histórico.
 *
 * @param hist Pointer para a struct History.
 * @return A duração da audição, como uma string.
 */
char *getHistoryDuration(History *hist);

/**
 * @brief Obtém a plataforma de reprodução no histórico.
 *
 * Função que retorna a plataforma (computador ou dispositivo móvel) associada ao histórico.
 *
 * @param hist Pointer para a struct History.
 * @return A plataforma, como uma string.
 */
char *getHistoryPlatform(History *hist);

/**
 * @brief Define o ID do histórico.
 *
 * Função que define o ID do histórico na struct History.
 *
 * @param hist Pointer para a struct History.
 * @param id O ID a ser atribuído ao histórico.
 */
void setHistoryId(History *hist, char *id);

/**
 * @brief Define o ID do utilizador no histórico.
 *
 * Função que define o ID do utilizador no histórico.
 *
 * @param hist Pointer para a struct History.
 * @param user_id O ID do utilizador a ser atribuído.
 */
void setHistoryUserId(History *hist, char *user_id);

/**
 * @brief Define o ID da música no histórico.
 *
 * Função que define o ID da música no histórico.
 *
 * @param hist Pointer para a struct History.
 * @param music_id O ID da música a ser atribuído.
 */
void setHistoryMusicId(History *hist, char *music_id);

/**
 * @brief Define o timestamp no histórico.
 *
 * Função que define o timestamp do histórico.
 *
 * @param hist Pointer para a struct History.
 * @param timestamp O timestamp a ser atribuído.
 */
void setHistoryTimestamp(History *hist, char *timestamp);

/**
 * @brief Define a duração da audição no histórico.
 *
 * Função que define a duração da audição da música no histórico.
 *
 * @param hist Pointer para a struct History.
 * @param duration A duração a ser atribuída.
 */
void setHistoryDuration(History *hist, char *duration);

/**
 * @brief Define a plataforma de reprodução no histórico.
 *
 * Função que define a plataforma de reprodução da música no histórico.
 *
 * @param hist Pointer para a struct History.
 * @param platform A plataforma a ser atribuída.
 */
void setHistoryPlatform(History *hist, char *platform);

/**
 * @brief Inicializa a struct History.
 *
 * Função que aloca memória e inicializa os valores da struct History todos a NULL.
 *
 * @return Um pointer para a nova struct History.
 */
History *initHistory();

/**
 * @brief Liberta a memória ocupada pela struct History.
 *
 * Função que liberta a memória de todos os campos da struct History,
 * incluindo o próprio pointer.
 *
 * @param hist Pointer para a struct History a ser libertada.
 */
void destroyHistory(History *hist);

/**
 * @brief Separa os dados de um histórico a partir de uma linha CSV.
 *
 * Função que separa uma linha de um arquivo CSV e a utiliza para preencher uma struct History.
 *
 * @param line Linha do CSV a ser separada.
 * @return A struct History preenchida com os dados extraídos.
 */
History *separateHistory(char *line);




#endif