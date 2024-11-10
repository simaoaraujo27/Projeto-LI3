#include "compare_files.h"

bool compareFiles(FILE *fp1, FILE *fp2, int totalTestesQ1, int totalTestesQ2,
                  int totalTestesQ3, int i) {
  int ch1, ch2;
  int position = 0, line = 1;

  while (1) {
    // Ignora caracteres especiais no fim da linha
    do {
      ch1 = fgetc(fp1);
    } while (ch1 == '\r');

    do {
      ch2 = fgetc(fp2);
    } while (ch1 == '\r');

    // Se ambos os caracteres são EOF, os ficheiros são iguais
    if (ch1 == EOF && ch2 == EOF) {
      return true;
    }

    // Se um dos ficheiros terminou antes do outro, são diferentes
    if (ch1 != ch2) {
      int nQuery = 0;
      if (i <= totalTestesQ1) {
        nQuery = 1;
      } else if (i <= totalTestesQ1 + totalTestesQ2) {
        nQuery = 2;
      } else if (i <= totalTestesQ1 + totalTestesQ2 + totalTestesQ3) {
        nQuery = 3;
      }

      printf("Diferença encontrada na query %d: linha %d no ficheiro "
             "resultados/command%d_output.txt\n",
             nQuery, line, i);
      return false;
    }

    position++;

    // Se encontra um '\n', reseta a posição e incrementa a linha
    if (ch1 == '\n') {
      line++;
      position = 0;
    }
  }
}