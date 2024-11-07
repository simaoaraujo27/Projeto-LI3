#ifndef _COMPARE_FILES_H_
#define _COMPARE_FILES_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

#define MAX_PATH_SIZE 1024

bool compareFiles(FILE *fp1, FILE *fp2, int totalTestesQ1, int totalTestesQ2, int totalTestesQ3, int i);

#endif