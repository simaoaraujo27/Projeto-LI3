#include "programa-testes.h"
#include "compare_files.h"
#define MAX_PATH_SIZE 1024

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

  // Aloca memória para os caminhos dos ficheiros
  char *filenameResultados = malloc(sizeof(char) * MAX_PATH_SIZE);
  char *filenameResultadosEsperados = malloc(sizeof(char) * MAX_PATH_SIZE);

  char *executaMain = malloc(sizeof(char) * MAX_PATH_SIZE);
  // Cria o comando para executar o programa principal com os ficheiros
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
  comandos = fopen(comandosPath, "r"); // Abre o ficheiro de comandos

  if (comandos == NULL) {
    perror("Erro ao abrir os ficheiros"); // Exibe erro se o ficheiro não puder
                                          // ser aberto
    return 1;
  }

  // Contador para o número de testes de cada query e para o total de testes
  int totalTestesQ1 = 0;
  int totalTestesQ2 = 0;
  int totalTestesQ3 = 0;
  int totalTestesQ4 = 0;
  int totalTestesQ5 = 0;
  int totalTestesQ6 = 0;
  int totalTestes = 0;

  // Flag para indicar o início de uma nova linha
  int ch;
  int nova_linha = 1;

  // Lê o ficheiro de comandos e conta os testes para cada tipo de consulta
  while ((ch = fgetc(comandos)) != EOF) {
    if (nova_linha) {
      // Aqui temos o primeiro caractere de uma linha
      char primeiro_char = (char)ch;

      if (primeiro_char == '1') {
        totalTestesQ1++;
      } else if (primeiro_char == '2') {
        totalTestesQ2++;
      } else if (primeiro_char == '3') {
        totalTestesQ3++;
      } else if (primeiro_char == '4') {
        totalTestesQ4++;
      } else if (primeiro_char == '5') {
        totalTestesQ5++;
      } else if (primeiro_char == '6') {
        totalTestesQ6++;
      }

      totalTestes++;

      nova_linha = 0;
    }

    // Se encontramos um '\n', significa que mudamos de linha
    if (ch == '\n') {
      nova_linha = 1;
    }
  }

  fclose(comandos); // Fecha o ficheiro de comandos

  comandos = fopen(comandosPath, "r"); // Abre o ficheiro de comandos

  if (comandos == NULL) {
    perror("Erro ao abrir os ficheiros");
    return 1;
  }

  nova_linha = 1;
  // Array que vai armazenar qual a query que será executada para cada linha do
  // input
  int nQuery[totalTestes];
  int i = 0;

  while ((ch = fgetc(comandos)) != EOF) {
    if (nova_linha) {
      // Aqui temos o primeiro caractere de uma linha
      char primeiro_char = (char)ch;

      if (primeiro_char == '1')
        nQuery[i++] = 1;
      else if (primeiro_char == '2')
        nQuery[i++] = 2;
      else if (primeiro_char == '3')
        nQuery[i++] = 3;
      else if (primeiro_char == '4')
        nQuery[i++] = 4;
      else if (primeiro_char == '5')
        nQuery[i++] = 5;
      else if (primeiro_char == '6')
        nQuery[i++] = 6;
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

  // Contadores para os testes corretos de cada tipo de query
  int corretas[6] = {0};

  // Loop para verificar os resultados dos testes
  for (i = 1; i <= totalTestes; i++) {
    if (i >= 56 && i <= 65)
      continue;
    // Formata os paths para os ficheiros de resultados
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

    // Abre os ficheiros de resultados gerados e esperados
    fp1 = fopen(filenameResultados, "r");
    fp2 = fopen(filenameResultadosEsperados, "r");

    if (fp1 == NULL || fp2 == NULL) {
      perror("Erro ao abrir os ficheiros %d"); // Exibe erro caso não consiga
                                               // abrir os ficheiros
      return 1;
    }

    // Compara os ficheiros de resultados e verifica se são iguais
    if (compareFiles(fp1, fp2, nQuery[i - 1], i)) {
      corretas[nQuery[i - 1] - 1]++;
    }

    fclose(fp1); // Fecha o ficheiro de resultados
    fclose(fp2); // Fecha o ficheiro esperado
  }

  // Printa o número de testes corretos para cada query
  printf("Query 1: %d/%d testes corretos!\n", corretas[0], totalTestesQ1);
  printf("Query 2: %d/%d testes corretos!\n", corretas[1], totalTestesQ2);
  printf("Query 3: %d/%d testes corretos! \n", corretas[2], totalTestesQ3);
  printf("Query 4: %d/%d testes corretos! \n", corretas[3], totalTestesQ4);
  printf("Query 5: %d/%d testes corretos! \n", corretas[4], totalTestesQ5);
  printf("Query 6: %d/%d testes corretos! \n", corretas[5], totalTestesQ6);

  // Printa o tempo total de execução
  printf("Tempo total de execução: %.6f segundos\n", elapsed);

  // Liberta a memória alocada para os paths dos ficheiros
  free(filenameResultados);
  free(filenameResultadosEsperados);
  free(executaMain);

  return 0;
}
