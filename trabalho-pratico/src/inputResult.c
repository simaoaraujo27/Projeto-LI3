#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *createFile(int i) {
  // Cria o path para o arquivo de resultados na pasta "resultados"
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new =
      malloc(sizeof(char) *
             (strlen(path) + 10)); // Aloca memória para o path do arquivo
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt",
           i);               // Formata o nome do arquivo
  newFile = fopen(new, "w"); // Abre o arquivo para escrita
  free(new);
  return newFile;
}