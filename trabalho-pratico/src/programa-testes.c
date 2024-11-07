#include "compare_files.h"
#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  struct timespec start, end;
  double elapsed;

  clock_gettime(CLOCK_REALTIME, &start);

  FILE *fp1 = NULL;
  FILE *fp2 = NULL;

  if (argc < 4) {
    fprintf(stderr, "Error: Missing filename\n");
    return 1;
  }

  char *filenameResultados = malloc(sizeof(char) * MAX_PATH_SIZE);
  char *filenameResultadosEsperados = malloc(sizeof(char) * MAX_PATH_SIZE);

  char *executaMain = malloc(sizeof(char) * MAX_PATH_SIZE);
  snprintf(executaMain, sizeof(char) * MAX_PATH_SIZE,
           "./programa-principal %s %s", argv[1], argv[2]);
  int ret = system(executaMain);
  if (ret == -1) {
    perror("Erro ao executar o programa-principal\n");
    return 1;
  }

  clock_gettime(CLOCK_REALTIME, &end);
  elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

  char *comandosPath = argv[2];
  FILE *comandos = NULL;
  comandos = fopen(comandosPath, "r");

  if (comandos == NULL) {
    perror("Erro ao abrir os ficheiros");
    return 1;
  }

  int totalTestesQ1 = 0;
  int totalTestesQ2 = 0;
  int totalTestesQ3 = 0;
  int totalTestes = 0;

  int ch;
  int nova_linha = 1; // Flag para indicar o início de uma nova linha

  while ((ch = fgetc(comandos)) != EOF) {
    if (nova_linha) {
      // Aqui temos o primeiro caractere de uma linha
      char primeiro_char = (char)ch;

      if (primeiro_char == '1')
        totalTestesQ1++;
      else if (primeiro_char == '2')
        totalTestesQ2++;
      else if (primeiro_char == '3')
        totalTestesQ3++;

      totalTestes++;

      nova_linha = 0;
    }

    // Se encontramos um '\n', significa que mudamos de linha
    if (ch == '\n') {
      nova_linha = 1;
    }
  }

  fclose(comandos);

  char *pasta = argv[3];
  int lenPasta = strlen(pasta);

  int corretasQ1 = 0, corretasQ2 = 0, corretasQ3 = 0;

  for (int i = 1; i <= totalTestes; i++) {
    snprintf(filenameResultados, MAX_PATH_SIZE,
             "./resultados/command%d_output.txt", i);

    // Verifica se o diretório dos resultados esperados já contém '/'
    if (pasta[lenPasta - 1] == '/') {
      snprintf(filenameResultadosEsperados, MAX_PATH_SIZE,
               "./%scommand%d_output.txt", argv[3], i);
    } else {
      snprintf(filenameResultadosEsperados, MAX_PATH_SIZE,
               "./%s/command%d_output.txt", argv[3], i);
    }

    fp1 = fopen(filenameResultados, "r");
    fp2 = fopen(filenameResultadosEsperados, "r");

    if (fp1 == NULL || fp2 == NULL) {
      perror("Erro ao abrir os ficheiros");
      return 1;
    }

    if (compareFiles(fp1, fp2, totalTestesQ1, totalTestesQ2, totalTestesQ3,
                     i)) {
      if (i <= totalTestesQ1)
        corretasQ1++;
      else if (i <= (totalTestesQ1 + totalTestesQ2))
        corretasQ2++;
      else
        corretasQ3++;
    }

    fclose(fp1);
    fclose(fp2);
  }

  printf("Query 1: %d/%d testes corretos!\n", corretasQ1, totalTestesQ1);
  printf("Query 2: %d/%d testes corretos!\n", corretasQ2, totalTestesQ2);
  printf("Query 3: %d/%d testes corretos! \n", corretasQ3, totalTestesQ3);

  struct rusage r_usage;
  getrusage(RUSAGE_SELF, &r_usage);

  printf("Memória utilizada: %ld KB\n", r_usage.ru_maxrss);
  printf("Tempo total de execução: %.6f segundos\n", elapsed);

  free(filenameResultados);
  free(filenameResultadosEsperados);
  free(executaMain);

  return 0;
}