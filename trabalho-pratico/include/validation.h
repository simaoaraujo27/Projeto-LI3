/**
 * @file validation.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do validation.h
 */

#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include <glib.h>
#include <stdbool.h>

/**
 * @brief Valida o histórico de uma plataforma.
 *
 * Verifica se o histórico fornecido é válido para a plataforma especificada.
 *
 * @param plataform Nome da plataforma.
 * @return `true` se for válido, `false` caso contrário.
 */
bool validatePlataformHistory(char *plataform);

/**
 * @brief Valida uma data no formato esperado.
 *
 * Confirma se a data fornecida segue o formato e os valores esperados.
 *
 * @param date Data a ser validada.
 * @return `true` se a data for válida, `false` caso contrário.
 */
bool validateDate(char *date);

/**
 * @brief Valida a duração de uma música ou item.
 *
 * Checa se a duração segue o formato adequado.
 *
 * @param duration String representando a duração.
 * @return `true` se válida, `false` caso contrário.
 */
bool validateDuration(char *duration);

/**
 * @brief Valida um endereço de email.
 *
 * Verifica se o email fornecido é válido com base no formato padrão.
 *
 * @param email Endereço de email a ser validado.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateEmail(char *email);

/**
 * @brief Valida o tipo de assinatura.
 *
 * Checa se o tipo de assinatura está dentro dos valores permitidos.
 *
 * @param type String representando o tipo de assinatura.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateSubscriptionType(char *type);

/**
 * @brief Valida uma lista de valores no formato CSV.
 *
 * Garante que a lista fornecida esteja formatada corretamente.
 *
 * @param list String representando a lista em formato CSV.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateCSVList(char *list);

/**
 * @brief Valida uma linha de usuário no ficheiro.
 *
 * Verifica se os dados do usuário na linha seguem os padrões esperados.
 *
 * @param line Linha com informações do usuário.
 * @param gestorMusics Estrutura de gestão de músicas para referências cruzadas.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateUsersLine(char *line, gestorMusics *gestorMusics);

/**
 * @brief Valida informações de artistas.
 *
 * Confirma a validade do ID do artista e do tipo fornecido.
 *
 * @param idConstituent ID do artista.
 * @param type Tipo associado ao artista.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateArtistLine(char *idConstituent, char *type);

/**
 * @brief Valida uma linha de música no ficheiro.
 *
 * Checa se a linha contém dados consistentes e compatíveis com os gestores
 * fornecidos.
 *
 * @param line Linha contendo informações da música.
 * @param gestorArtists Estrutura de gestão de artistas para referência.
 * @param gestorAlbuns Estrutura de gestão de álbuns para referência.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateMusicsLine(char *line, gestorArtists *gestorArtists,
                        gestorAlbuns *gestorAlbuns);

/**
 * @brief Valida uma linha de álbuns.
 *
 * Verifica se as informações fornecidas seguem os critérios esperados.
 *
 * @param line Linha com informações do álbum.
 * @param gestorArtists Estrutura de gestão de artistas para referências
 * cruzadas.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateAlbumsLine(char *line, gestorArtists *gestorArtists);

/**
 * @brief Valida uma linha do histórico.
 *
 * Confirma a consistência e validade das informações contidas na linha do
 * histórico.
 *
 * @param line Linha a ser validada.
 * @return `true` se válida, `false` caso contrário.
 */
bool validateHistoryLine(char *line);

/**
 * @brief Valida a idade fornecida.
 *
 * Verifica se a idade está dentro de um intervalo aceitável e é numérica.
 *
 * @param age String representando a idade.
 * @return `true` se válida, `false` caso contrário.
 */
bool validateAge(char *age);

/**
 * @brief Valida um ID.
 *
 * Checa se o ID segue os padrões esperados.
 *
 * @param id ID a ser validado.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateId(char *id);

/**
 * @brief Compara se uma data de fim ocorre após uma data de início.
 *
 * Confirma a ordem temporal entre duas datas.
 *
 * @param end Data de término.
 * @param begin Data de início.
 * @return `true` se a data de término for posterior, `false` caso contrário.
 */
bool isAfter(const char *end, const char *begin);

/**
 * @brief Verifica se uma string contém apenas dígitos.
 *
 * Garante que a string fornecida é composta exclusivamente por caracteres
 * numéricos.
 *
 * @param num String a ser verificada.
 * @return `true` se contiver apenas dígitos, `false` caso contrário.
 */
bool allDigit(char *num);

/**
 * @brief Valida um ano.
 *
 * Checa se o ano é numérico e está dentro de um intervalo aceitável.
 *
 * @param year String representando o ano.
 * @return `true` se válido, `false` caso contrário.
 */
bool validateYear(char *year);

#endif
