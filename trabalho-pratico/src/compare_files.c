#include "compare_files.h"

struct temposTestes {
  double totalTimeQuery1;
  double totalTimeQuery2;
  double totalTimeQuery3;
  double totalTimeQuery4;
  double totalTimeQuery5;
  double totalTimeQuery6;
};

temposTestes *initTemposTestes() {
  temposTestes *t = malloc(sizeof(struct temposTestes));
  if (t == NULL) {
    printf("Erro ao alocar memória para a struct temposTestes!\n");
    return NULL;
  }
  t->totalTimeQuery1 = 0;
  t->totalTimeQuery2 = 0;
  t->totalTimeQuery3 = 0;
  t->totalTimeQuery4 = 0;
  t->totalTimeQuery5 = 0;
  t->totalTimeQuery6 = 0;

  return t;
}

void destroyTemposTestes(temposTestes *t) {
  if (t) {
    free(t);
  }
}

double getTemposTestes(temposTestes *t, int i) {
  switch (i) {
  case 1:
    return t->totalTimeQuery1;
    break;
  case 2:
    return t->totalTimeQuery2;
    break;
  case 3:
    return t->totalTimeQuery3;
    break;
  case 4:
    return t->totalTimeQuery4;
    break;
  case 5:
    return t->totalTimeQuery5;
    break;
  case 6:
    return t->totalTimeQuery6;
    break;
  default:
    return -1;
    break;
  }
}

void setTemposTestes(temposTestes *t, int i, double val) {
  switch (i) {
  case 1:
    t->totalTimeQuery1 += val;
    break;
  case 2:
    t->totalTimeQuery2 += val;
    break;
  case 3:
    t->totalTimeQuery3 += val;
    break;
  case 4:
    t->totalTimeQuery4 += val;
    break;
  case 5:
    t->totalTimeQuery5 += val;
    break;
  case 6:
    t->totalTimeQuery6 += val;
    break;
  default:
    return;
    break;
  }
}

// Função para comparar dois ficheiros linha por linha
// Retorna 'true' se forem iguais, 'false' caso contrário
bool compareFiles(FILE *fp1, FILE *fp2, int nQuery, int i) {
  int ch1, ch2; // Variáveis para armazenar caracteres dos ficheiros
  int position = 0, line = 1; // Controlam a posição e o número da linha

  // Loop que percorre ambos os ficheiros simultaneamente
  while (1) {
    // Ignora caracteres '\r'
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

    // Se um dos ficheiros terminar antes do outro, ou os caracteres não
    // coincidirem, são diferentes
    if (ch1 != ch2) {

      // Imprime uma mensagem que indica onde é que a diferença foi encontrada
      printf("Diferença encontrada na query %d: linha %d no ficheiro "
             "resultados/command%d_output.txt\n",
             nQuery, line, i);

      return false; // Retorna 'false' porque os ficheiros são diferentes
    }

    position++; // Incrementa a posição para o próximo caractere

    // Se um '\n' (nova linha) for encontrado, incrementa o número da linha e
    // reseta a posição
    if (ch1 == '\n') {
      line++;
      position = 0;
    }
  }
}
