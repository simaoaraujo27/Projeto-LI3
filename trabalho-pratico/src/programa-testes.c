#include "compare_files.h"
#define MAX_PATH_SIZE 1024

/*
TODO:
    // Compara os arquivos de resultados e verifica se são iguais
    if (compareFiles(fp1, fp2, totalTestesQ1, totalTestesQ2, totalTestesQ3,
                     i)) {
      // Conta os testes corretos de acordo com o tipo de consulta
      if (i <= totalTestesQ1)
        corretasQ1++;
      else if (i <= (totalTestesQ1 + totalTestesQ2))
        corretasQ2++;
      else
        corretasQ3++;
    }
*/

int main(int argc, char **argv) {
  struct timespec start, end;
  double elapsed;

  clock_gettime(CLOCK_REALTIME, &start); // Registra o tempo de início

  FILE *fp1 = NULL;
  FILE *fp2 = NULL;

  // Verifica se o número de argumentos está correto
  if (argc < 4) {
    fprintf(stderr,
            "Error: Missing filename\n"); // Exibe erro se faltar argumento
    return 1;
  }

  // Aloca memória para os caminhos dos arquivos
  char *filenameResultados = malloc(sizeof(char) * MAX_PATH_SIZE);
  char *filenameResultadosEsperados = malloc(sizeof(char) * MAX_PATH_SIZE);

  char *executaMain = malloc(sizeof(char) * MAX_PATH_SIZE);
  // Cria o comando para executar o programa principal com os arquivos
  // fornecidos como argumento
  snprintf(executaMain, sizeof(char) * MAX_PATH_SIZE,
           "RAM_MONITOR=1 ./programa-principal %s %s", argv[1], argv[2]);

  // Executa o comando do sistema
  int ret = system(executaMain);
  if (ret == -1) {
    perror("Erro ao executar o programa-principal\n"); // Exibe erro se a
                                                       // execução falhar
    return 1;
  }

  clock_gettime(CLOCK_REALTIME, &end); // Regista o tempo de término
  elapsed = (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9; // Calcula o tempo de execução

  char *comandosPath = argv[2];
  FILE *comandos = NULL;
  comandos = fopen(comandosPath, "r"); // Abre o arquivo de comandos

  if (comandos == NULL) {
    perror("Erro ao abrir os ficheiros"); // Exibe erro se o arquivo não puder
                                          // ser aberto
    return 1;
  }

  // Contadores para os testes de cada query
  int totalTestesQ1 = 0;
  int totalTestesQ2 = 0;
  int totalTestesQ3 = 0;
  int totalTestes = 0;

  int ch;
  int nova_linha = 1; // Flag para indicar o início de uma nova linha

  // Lê o arquivo de comandos e conta os testes para cada tipo de consulta
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

  fclose(comandos); // Fecha o arquivo de comandos

  char *pasta = argv[3];
  int lenPasta = strlen(pasta);

  // Contadores para os testes corretos de cada tipo de consulta
  int corretasQ1 = 0, corretasQ2 = 0, corretasQ3 = 0;

  // Loop para verificar os resultados dos testes
  for (int i = 1; i <= totalTestes; i++) {
    // Formata os paths para os arquivos de resultados
    snprintf(filenameResultados, MAX_PATH_SIZE,
             "./resultados/command%d_output.txt", i);

    // Verifica se o diretório de resultados esperados tem '/' no final
    if (pasta[lenPasta - 1] == '/') {
      snprintf(filenameResultadosEsperados, MAX_PATH_SIZE,
               "./%scommand%d_output.txt", argv[3], i);
    } else {
      snprintf(filenameResultadosEsperados, MAX_PATH_SIZE,
               "./%s/command%d_output.txt", argv[3], i);
    }

    // Abre os arquivos de resultados gerados e esperados
    fp1 = fopen(filenameResultados, "r");
    fp2 = fopen(filenameResultadosEsperados, "r");

    if (fp1 == NULL || fp2 == NULL) {
      perror("Erro ao abrir os ficheiros"); // Exibe erro caso não consiga abrir
                                            // os arquivos
      return 1;
    }

    // Compara os arquivos de resultados e verifica se são iguais
    if (compareFiles(fp1, fp2, totalTestesQ1, totalTestesQ2, totalTestesQ3,
                     i)) {
      // Conta os testes corretos de acordo com o tipo de consulta
      if (i <= totalTestesQ1)
        corretasQ1++;
      else if (i <= (totalTestesQ1 + totalTestesQ2))
        corretasQ2++;
      else
        corretasQ3++;
    }

    fclose(fp1); // Fecha o arquivo de resultados
    fclose(fp2); // Fecha o arquivo esperado
  }

  // Printa o número de testes corretos para cada query
  printf("Query 1: %d/%d testes corretos!\n", corretasQ1, totalTestesQ1);
  printf("Query 2: %d/%d testes corretos!\n", corretasQ2, totalTestesQ2);
  printf("Query 3: %d/%d testes corretos! \n", corretasQ3, totalTestesQ3);

  // Printa o tempo de execução
  printf("Tempo total de execução: %.6f segundos\n", elapsed);

  // Liberta a memória alocada para os paths dos arquivos
  free(filenameResultados);
  free(filenameResultadosEsperados);
  free(executaMain);

  return 0;
}
