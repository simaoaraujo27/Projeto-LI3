#include "output_Result.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_SIZE 1024
#define MAX_INPUT_SIZE 512

int main() {
  const char *red = "\033[1;31m";   // Vermelho brilhante
  const char *green = "\033[1;32m"; // Verde brilhante

  // Imprimir linhas completas e texto centralizado
  printFullLine('*', green); // Linha superior
  printCentered("*   PROGRAMA INTERATIVO   *", red);
  printFullLine('*', green); // Linha inferior

  char path[MAX_PATH_SIZE];
  printf("Introduza o caminho do ficheiro ou diretório: ");
  assert(fgets(path, sizeof(path), stdin) != NULL);

  if (strcmp(path, "\n") == 0) {
    strcpy(path, "dataset/sem_erros");
  }

  removerNovaLinha(path);

  while (!validaPath(path)) {
    printf("\033[1;31mERRO: O caminho introduzido (%s) é inválido!\033[0m\n",
           path);
    printf("Por favor introduza um caminho válido: ");
    assert(fgets(path, sizeof(path), stdin) != NULL);
    if (strcmp(path, "\n") == 0) {
      strcpy(path, "dataset/sem_erros");
    }
    removerNovaLinha(path);
  }
  printf("\033[32mDataset carregado!\033[0m (caminho: %s) \n", path);
  printf("\n");

  int query = 0;
  bool continuar = true;
  char separador;
  int nQueries = 0;

  FILE *newFile = fopen("input.txt", "w");
  if (newFile == NULL) {
    perror("Erro ao criar o arquivo input.txt");
    return 1;
  }

  while (continuar) {

    query = lerNumeroValido();
    limparBufferEntrada();

    switch (query) {
    case 0:
      continuar = false;
      printf("\n");
      if (nQueries == 0) {
        printf("A terminar...\n");
        return 0;
      } else if (nQueries == 1) {
        printf("A executar a query pedida...\n");
      } else {
        printf("A executar as %d queries pedidas...\n", nQueries);
      }

      printf("Por favor aguarde\n");
      break;

    case 1: {
      nQueries++;
      char userId[10];
      printf("ID (Utilizador ou Artista): ");
      assert(scanf("%9s", userId) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateId(userId)) {
          printRed("ERRO: O ID inserido é inválido!\n");
          printf("Por favor, insira um ID válido: ");
          assert(scanf("%9s", userId) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);

      char input[MAX_INPUT_SIZE];
      if (separador == '=') {
        snprintf(input, sizeof(input), "1S %s\n", userId);
      } else {
        snprintf(input, sizeof(input), "1 %s\n", userId);
      }

      fprintf(newFile, "%s", input);
      break;
    }

    case 2: {
      nQueries++;
      char n[5], country[100];
      printf("N: ");
      assert(scanf("%4s", n) != -1);
      limparBufferEntrada();
      while (1) {
        if (!allDigit(n)) {
          printRed("ERRO: O valor para N inserido é inválido!\n");
          printf("Por favor, insira um valor válido: ");
          assert(scanf("%4s", n) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      printf("Country, entre aspas duplas (\"\") (insira 0 se não quiser "
             "especificar): ");
      assert(scanf("%99s", country) != -1);
      limparBufferEntrada();
      while (1) {
        if (!strcmp(country, "0") || !strcmp(country, "\"0\"")) {
          break;
        }
        if (country[0] != '"' && country[strlen(country) - 1] != '"') {
          printRed("ERRO: O country é inválido!\n");
          printf("Por favor, insira o country entre aspas (\"\") : ");

          assert(scanf("%99s", country) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);

      char input[MAX_INPUT_SIZE];
      if (!strcmp(country, "0") || !strcmp(country, "\"0\"")) {
        snprintf(input, sizeof(input), "2 %s\n", n);
      } else {
        snprintf(input, sizeof(input), "2 %s %s\n", n, country);
      }

      fprintf(newFile, "%s", input);
      break;
    }

    case 3: {
      nQueries++;
      char minAge[4], maxAge[4];
      printf("Min Age: ");
      assert(scanf("%3s", minAge) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateAge(minAge)) {
          printRed("ERRO: A idade inserida é inválida!\n");
          printf("Por favor, insira uma idade válida: ");
          assert(scanf("%3s", minAge) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }
      printf("Max Age: ");
      assert(scanf("%3s", maxAge) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateAge(maxAge) || atoi(maxAge) < atoi(minAge)) {
          printRed("ERRO: A idade inserida é inválida!\n");
          printf("Por favor, insira uma idade válida: ");
          assert(scanf("%3s", maxAge) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);
      char input[MAX_INPUT_SIZE];
      snprintf(input, sizeof(input), "%s %s\n", minAge, maxAge);
      if (separador == '=') {
        snprintf(input, sizeof(input), "3S %s %s\n", minAge, maxAge);
      }

      fprintf(newFile, "%s", input);
      break;
    }

    case 4: {
      nQueries++;
      char usar[3], beginDate[12], endDate[12];
      printf("Deseja inserir datas? (S/N) (default: N): ");
      assert(scanf("%2s", usar) != -1);
      limparBufferEntrada();

      if (strcmp(usar, "S") == 0 || strcmp(usar, "s") == 0) {
        printf("Begin Date (formato: YYYY/MM/DD): ");
        assert(scanf("%11s", beginDate) != -1);
        limparBufferEntrada();
        while (1) {
          if (!validateDate(beginDate)) {
            printRed("ERRO: A data inserida é inválida!\n");
            printf("Por favor, insira uma data válida: ");
            assert(scanf("%11s", beginDate) != -1);
            limparBufferEntrada();
          } else {
            break;
          }
        }

        printf("End Date (formato: YYYY/MM/DD): ");
        assert(scanf("%11s", endDate) != -1);
        limparBufferEntrada();
        while (1) {
          if (!validateDate(endDate) || !isAfter(endDate, beginDate)) {
            printRed("ERRO: A data inserida é inválida!\n");
            printf("Por favor, insira uma data válida: ");
            assert(scanf("%11s", endDate) != -1);
            limparBufferEntrada();
          } else {
            break;
          }
        }
        escolheSeparador(&separador);
        char input[MAX_INPUT_SIZE];
        snprintf(input, sizeof(input), "4 %s %s\n", beginDate, endDate);
        if (separador == '=') {
          snprintf(input, sizeof(input), "4S %s %s\n", beginDate, endDate);
        }

        fprintf(newFile, "%s", input);
      } else {
        escolheSeparador(&separador);
        char input[MAX_INPUT_SIZE];
        snprintf(input, sizeof(input), "4\n");
        if (separador == '=') {
          snprintf(input, sizeof(input), "4S\n");
        }

        fprintf(newFile, "%s", input);
      }
      break;
    }

    case 5: {
      nQueries++;
      char username[12], numUtilizadores[9];
      printf("Username: ");
      assert(scanf("%11s", username) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateId(username)) {
          printRed("ERRO: O username inserido é inválido!\n");
          printf("Por favor, insira um username válido: ");
          assert(scanf("%11s", username) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      printf("Número de utilizadores: ");
      assert(scanf("%8s", numUtilizadores) != -1);
      limparBufferEntrada();
      while (1) {
        if (!allDigit(numUtilizadores)) {
          printRed("ERRO: O número de utilizadores é inválido!\n");
          printf("Por favor, insira um número de utilizadores válido: ");
          assert(scanf("%8s", numUtilizadores) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);
      char input[MAX_INPUT_SIZE];
      snprintf(input, sizeof(input), "5 %s %s\n", username, numUtilizadores);
      if (separador == '=') {
        snprintf(input, sizeof(input), "5S %s %s\n", username, numUtilizadores);
      }

      fprintf(newFile, "%s", input);
      break;
    }

    case 6: {
      nQueries++;
      char id[12], year[5], num[5];
      printf("User ID: ");
      assert(scanf("%11s", id) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateId(id)) {
          printRed("ERRO: O ID inserido é inválido!\n");
          printf("Por favor, insira um ID válido: ");
          assert(scanf("%9s", id) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      printf("Ano: ");
      assert(scanf("%4s", year) != -1);
      limparBufferEntrada();

      while (1) {
        if (!validateYear(year)) {
          printRed("Erro: O ano inserido é inválido!\n");
          printf("Por favor, insira um ano válido: ");
          assert(scanf("%4s", year) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      printf("Insira o número de artistas (se não quiser, insira 0): ");
      assert(scanf("%4s", num) != -1);
      limparBufferEntrada();
      while (1) {
        if (!allDigit(num)) {
          printRed("ERRO: O número de artistas inserido é inválido!\n");
          printf("Por favor, insira um número de artistas válido: ");
          assert(scanf("%4s", num) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);
      char input[MAX_INPUT_SIZE];
      if (strcmp(num, "0") == 0) {
        snprintf(input, sizeof(input), "6 %s %s\n", id, year);
      } else {
        snprintf(input, sizeof(input), "6 %s %s %s\n", id, year, num);
      }

      if (separador == '=') {
        snprintf(input, sizeof(input), "6S %s %s %s\n", id, year, num);
      }

      fprintf(newFile, "%s", input);
      break;
    }

    default:
      printRed("Query inválida!\n");
      fclose(newFile);
      return 1;
    }

    printf("\n");
  }

  fclose(newFile);

  char executaMain[MAX_PATH_SIZE];
  snprintf(executaMain, sizeof(executaMain),
           "./programa-principal %s input.txt", path);

  int ret = system(executaMain);
  if (ret == -1) {
    perror("Erro ao executar o programa-principal\n");
    return 1;
  }

  printResults(nQueries);

  if (remove("input.txt") != 0) {
    printf("Ocorreu um erro ao apagar o ficheiro de input!\n");
    return 1;
  }

  return 0;
}
