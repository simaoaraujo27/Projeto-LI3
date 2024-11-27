#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile(FILE *newFile, char *text) {
  // Escreve a string formatada no arquivo
  fprintf(newFile, "%s", text);

  // Fecha o arquivo/file
  fclose(newFile);
}