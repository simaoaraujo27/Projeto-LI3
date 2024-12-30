#ifndef _COMPARE_FILES_H_
#define _COMPARE_FILES_H_

typedef struct temposTestes temposTestes;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

#define MAX_PATH_SIZE 1024

temposTestes *initTemposTestes();
void destroyTemposTestes(temposTestes *t);
double getTemposTestes(temposTestes *t, int i);
void setTemposTestes(temposTestes *t, int i, double val);
bool compareFiles(FILE *fp1, FILE *fp2, int nQuery, int i);

#endif