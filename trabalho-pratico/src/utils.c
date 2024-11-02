#include "utils.h"
#include <string.h>

void remove_quotes(char *str) {
  int len = strlen(str);

  // Verifica se a string começa e termina com aspas duplas
  if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
    // Move a string para "remover" as aspas duplas
    for (int i = 0; i < len - 1; i++) {
      str[i] = str[i + 1]; // Desloca os caracteres para a esquerda
    }
    str[len - 2] = '\0'; // Coloca o terminador nulo na nova posição
  }
}
