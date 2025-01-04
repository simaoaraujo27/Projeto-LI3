#include "output_Result.h"
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

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Valida o caminho inserido pelo utilizador
bool validaPath(const char *path) {
  struct stat info;
  return stat(path, &info) == 0;
}

// Remove o caracter '\n' no fim de uma string
void removerNovaLinha(char *str) {
  char *pos = strchr(str, '\n');
  if (pos != NULL) {
    *pos = '\0';
  }
}

// Função para imprimir uma linha ajustada à largura do terminal
void printFullLine(char ch, const char *color) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int largura_terminal = w.ws_col;

  printf("%s", color);
  for (int i = 0; i < largura_terminal; i++) {
    putchar(ch);
  }
  printf("\033[0m\n");
}

// Função para imprimir texto centralizado
void printCentered(const char *text, const char *color) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int largura_terminal = w.ws_col;

  int len_text = strlen(text);
  int padding_esquerda = (largura_terminal - len_text) / 2;

  printf("%s%*s%s\033[0m\n", color, padding_esquerda + len_text, text, "");
}

void printRGB(const char *text) {
  int r, g, b;
  size_t len = strlen(text);

  for (size_t i = 0; i < len; i++) {
    // Calcular cores vibrantes usando senos para suavidade
    r = (int)(sin(0.1 * i + 0) * 127 + 128); // Variando entre 0-255
    g = (int)(sin(0.1 * i + 2) * 127 + 128); // Fase deslocada
    b = (int)(sin(0.1 * i + 4) * 127 + 128); // Fase deslocada

    // Imprimir o caractere com a cor RGB
    printf("\033[38;2;%d;%d;%dm%c", r, g, b, text[i]);
    fflush(stdout); // Forçar saída no terminal
    usleep(50000);  // Pequeno atraso para efeito visual
  }

  printf("\033[0m\n"); // Resetar cor
}

// Função para gerar e armazenar query no arquivo de input
void escreverQuery(FILE *newFile, const char *query) {
  fprintf(newFile, "%s", query);
}

void escolheSeparador(char *separador) {
  *separador = ' ';
  printf("Escolha o separador (; ou =): ");
  assert(scanf("%c", separador) != -1);
  limparBufferEntrada();

  while (1) {
    if (*separador != ';' && *separador != '=') {
      printf("\033[31;31mERRO: O separador inserido (%c) é inválido!\033[0m\n",
             *separador);

      printf("Por favor, insira um separador válido: ");
      assert(scanf("%c", separador) != -1);
      limparBufferEntrada();
    } else {
      break;
    }
  }
}

// Função para printar resultados das queries
void printResults(int nQueries) {
  for (int i = 1; i <= nQueries; i++) {
    char title[64];
    snprintf(title, 64, "Resultado do input %d:", i);
    printRGB(title);
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "./resultados/command%d_output.txt", i);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo: %s\n", path);
      continue;
    }

    char line[MAX_INPUT_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {
      printf("%s", line);
    }
    printf("\n");

    fclose(file);
  }
}

int lerNumeroValido() {
  int num;
  while (1) {
    printf("Que query deseja executar (Opções de 1 a 6) | 0 para parar o "
           "programa: ");
    if (scanf("%d", &num) == 1) {
      // Se a leitura foi bem-sucedida, retornamos o número
      if (num >= 0 && num <= 6) {
        return num;
      }
      printf("\033[31mERRO: Query inválida! Por favor, insira um número "
             "válido.\033[0m\n");

    } else {
      // Se não foi um número, descartamos o que foi inserido e pedimos
      // novamente
      printf("\033[31mERRO: Entrada inválida. Por favor, insira um número "
             "válido.\033[0m\n");
      limparBufferEntrada();
    }
    printf("\n");
  }
}

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
    printf("\033[31mERRO: O caminho introduzido (%s) é inválido!\033[0m\n",
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
          printf("ERRO: O ID inserido é inválido!\n");
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

      escreverQuery(newFile, input);
      break;
    }

    case 2: {
      nQueries++;
      char n[5], country[100];
      printf("N: ");
      assert(scanf("%4s", n) != -1);
      limparBufferEntrada();

      printf("Country, entre aspas duplas (\"\") (insira 0 se não quiser "
             "especificar): ");
      assert(scanf("%99s", country) != -1);
      limparBufferEntrada();
      while (1) {
        if (country[0] != '"' && country[strlen(country) - 1] != '"') {
          printf("ERRO: O country é inválido!\n");
          printf("Por favor, insira o country entre aspas (\"\") : ");

          assert(scanf("%99s", country) != -1);
          limparBufferEntrada();
        } else {
          break;
        }
      }

      escolheSeparador(&separador);

      char input[MAX_INPUT_SIZE];
      if (strcmp(country, "0") == 0) {
        snprintf(input, sizeof(input), "2 %s\n", n);
      } else {
        snprintf(input, sizeof(input), "2 %s %s\n", n, country);
      }

      escreverQuery(newFile, input);
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
          printf("ERRO: A idade inserida é inválida!\n");
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
          printf("ERRO: A idade inserida é inválida!\n");
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

      escreverQuery(newFile, input);
      break;
    }

    case 4: {
      nQueries++;
      char usar[2], beginDate[12], endDate[12];
      printf("Deseja inserir datas? (S/N) (default: N): ");
      assert(scanf("%1s", usar) != -1);
      limparBufferEntrada();

      if (strcmp(usar, "S") == 0) {
        printf("Begin Date: ");
        assert(scanf("%11s", beginDate) != -1);
        limparBufferEntrada();
        while (1) {
          if (!validateDate(beginDate)) {
            printf("ERRO: A data inserida é inválida!\n");
            printf("Por favor, insira uma data válida: ");
            assert(scanf("%11s", beginDate) != -1);
            limparBufferEntrada();
          } else {
            break;
          }
        }

        printf("End Date: ");
        assert(scanf("%11s", endDate) != -1);
        limparBufferEntrada();
        while (1) {
          if (!validateDate(endDate) || !isAfter(endDate, beginDate)) {
            printf("ERRO: A data inserida é inválida!\n");
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

        escreverQuery(newFile, input);
      } else {
        char input[MAX_INPUT_SIZE];
        snprintf(input, sizeof(input), "4\n");
        if (separador == '=') {
          snprintf(input, sizeof(input), "4S\n");
        }

        escreverQuery(newFile, input);
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
          printf("ERRO: O username inserido é inválido!\n");
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
          printf("ERRO: O número de utilizadores é inválido!\n");
          printf("Por favor, insira um número de utilizadores válido: ");
          assert(scanf("%11s", username) != -1);
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

      escreverQuery(newFile, input);
      break;
    }

    case 6: {
      nQueries++;
      char id[12], year[5], num[5];
      printf("ID: ");
      assert(scanf("%11s", id) != -1);
      limparBufferEntrada();
      while (1) {
        if (!validateId(id)) {
          printf("ERRO: O ID inserido é inválido!\n");
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

      // TODO: Fazer validateYear e chamar em cima deste comment
      // Ajeitar a função scanf para funcionar para um enter

      printf("Insira o número de artistas (se não quiser, insira 0): ");
      assert(scanf("%4s", num) != -1);
      limparBufferEntrada();

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

      escreverQuery(newFile, input);
      break;
    }

    default:
      printf("Query inválida!\n");
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

  // Exibe os resultados
  printResults(nQueries);

  // Apaga o arquivo de input
  if (remove("input.txt") != 0) {
    printf("Ocorreu um erro ao apagar o ficheiro de input!\n");
    return 1;
  }

  return 0;
}
