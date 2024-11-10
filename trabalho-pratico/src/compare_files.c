#include "compare_files.h"

// Função para comparar dois ficheiros linha por linha
// Retorna 'true' se forem iguais, 'false' caso contrário
bool compareFiles(FILE *fp1, FILE *fp2, int totalTestesQ1, int totalTestesQ2,
                  int totalTestesQ3, int i) {
  int ch1, ch2; // Variáveis para armazenar caracteres dos ficheiros
  int position = 0, line = 1; // Controlam a posição e o número da linha

  // Loop que percorre ambos os ficheiros simultaneamente
  while (1) {
    // Ignora caracteres '\r' (usados em sistemas Windows para indicar fim de linha)
    do {
      ch1 = fgetc(fp1);
    } while (ch1 == '\r');

    do {
      ch2 = fgetc(fp2);
    } while (ch2 == '\r');

    // Se ambos os ficheiros chegarem ao fim ao mesmo tempo, são iguais
    if (ch1 == EOF && ch2 == EOF) {
      return true;
    }

    // Se um dos ficheiros terminar antes do outro, ou os caracteres não coincidirem, são diferentes
    if (ch1 != ch2) {
      int nQuery = 0;

      // Determina a qual query pertence o teste com base no índice 'i'
      if (i <= totalTestesQ1) {
        nQuery = 1;
      } else if (i <= totalTestesQ1 + totalTestesQ2) {
        nQuery = 2;
      } else if (i <= totalTestesQ1 + totalTestesQ2 + totalTestesQ3) {
        nQuery = 3;
      }

      // Imprime uma mensagem indicando onde a diferença foi encontrada
      printf("Diferença encontrada na query %d: linha %d no ficheiro "
             "resultados/command%d_output.txt\n",
             nQuery, line, i);

      return false; // Retorna 'false' porque os ficheiros são diferentes
    }

    position++; // Incrementa a posição para o próximo caractere

    // Se um '\n' (nova linha) for encontrado, incrementa o número da linha e reseta a posição
    if (ch1 == '\n') {
      line++;
      position = 0;
    }
  }
}
