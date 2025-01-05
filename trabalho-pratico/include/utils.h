#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>
#include <stdbool.h>

int converterParaSegundos(char *tempo);

int calcularDiasAte_9_9_2024(char *data);

void colocaTudoMinusculo(char *word);

void remove_quotes(char *str);

int primeiraOcorr(char *line, char carac);

int temAspas(char *line);

void removeFstLast(char *str);

void removeLast(char *str);

char *calculate_age_str(char *birth_date);

char *intToString(int number);

char *intToHour(int number);

void converterParaTempo(int segundos, char *resultado);

int calculateDiaAno(char *diaStr);

int isLeapYear(int year);

char *calculateData(int diaAno, int year);

void limparBufferEntrada();
bool validaPath(const char *path);
void removerNovaLinha(char *str);
void printFullLine(char ch, const char *color);
void printCentered(const char *text, const char *color);
void printRGB(const char *text);
void escolheSeparador(char *separador);
void printResults(int nQueries);
void printRed(const char *text);
int lerNumeroValido();

#endif