#include "gestor_artists.h"
#include "musics.h"
#include "utils.h"

// Função para converter segundos em uma string no formato "hh:mm:ss"
char *SegundosParaHoras(int segundos) {
  int horas = segundos / 3600;           // Calcula horas a partir de segundos
  int minutos = (segundos % 3600) / 60;  // Calcula minutos restantes
  int segundosRestantes = segundos % 60; // Calcula segundos restantes
  char *hora =
      malloc(20 * sizeof(char)); // Aloca memória para a string de saída
  snprintf(hora, 20, "%02d:%02d:%02d", horas, minutos,
           segundosRestantes); // Formata a string
  return hora;
}

// Função para imprimir os resultados da query 2 em um ficheiro
void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists,
                 int temS, char *country1) {
  GList *node = listaResposta;

  int contadorDeNodes = 0;

  if (country1 == NULL) {
    while (node != NULL && contadorDeNodes < numeroArtists) {
      char *name;
      char *type;
      char *discografia;
      char *country;
      char *new_str;

      // Obtém o artista atual da lista
      Artists *currentArtist = (Artists *)node->data;

      name = pegarArtistName(currentArtist); // Nome do artista
      type = pegarArtistType(currentArtist); // Tipo (Individual ou Grupo)
      discografia = SegundosParaHoras(pegarArtistDiscografia(
          currentArtist)); // Duração total em formato "hh:mm:ss"
      country = pegarArtistCountry(currentArtist); // País do artista

      // Calcula o comprimento total da string de saída
      int total_len = strlen(name) + strlen(type) + 4 + strlen(country) + 4;

      // Aloca memória para a nova string a ser escrita no ficheiro
      new_str =
          malloc((total_len + 1) * sizeof(char)); // +1 para o caractere '\0'

      // Remove aspas no nome e país
      remove_quotes(name);
      remove_quotes(country);
      if (temS) {
        // Formata a string de saída no formato: "name=type=discografia=country"
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s\n", name, type,
                 discografia, country);
      } else {
        // Formata a string de saída no formato: "name;type;discografia;country"
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type,
                 discografia, country);
      }
      // Escreve no ficheiro
      fprintf(newFile, "%s", new_str);

      // Avança para o próximo nó da lista
      node = node->next;

      contadorDeNodes++; // Incrementa o contador

      // Liberta a memória alocada para cada campo
      free(name);
      free(type);
      free(discografia);
      free(country);
      free(new_str);
    }
  } else {
    removeLast(country1);
    while (node != NULL && contadorDeNodes < numeroArtists) {
      char *name;
      char *type;
      char *discografia;
      char *country;
      char *new_str;

      // Obtém o artista atual da lista
      Artists *currentArtist = (Artists *)node->data;
      country = pegarArtistCountry(currentArtist); // País do artista
      if (strcmp(country1, country) != 0) {
        node = node->next;
      } else {
        name = pegarArtistName(currentArtist); // Nome do artista
        type = pegarArtistType(currentArtist); // Tipo (Individual ou Grupo)
        discografia = SegundosParaHoras(pegarArtistDiscografia(
            currentArtist)); // Duração total em formato "hh:mm:ss"

        // Calcula o comprimento total da string de saída
        int total_len = strlen(name) + strlen(type) + 4 + strlen(country) + 4;

        // Aloca memória para a nova string a ser escrita no ficheiro
        new_str =
            malloc((total_len + 1) * sizeof(char)); // +1 para o caractere '\0'

        // Remove aspas no nome e país
        remove_quotes(name);
        remove_quotes(country);
        if (temS) {
          // Formata a string de saída no formato:
          // "name=type=discografia=country"
          snprintf(new_str, total_len + 1, "%s=%s=%s=%s\n", name, type,
                   discografia, country);
        } else {
          // Formata a string de saída no formato:
          // "name;type;discografia;country"
          snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type,
                   discografia, country);
        }
        // Escreve no ficheiro
        fprintf(newFile, "%s", new_str);

        // Avança para o próximo nó da lista
        node = node->next;

        contadorDeNodes++; // Incrementa o contador

        // Liberta a memória alocada para cada campo
        free(name);
        free(type);
        free(discografia);
        free(country);
        free(new_str);
      }
    }
  }
  if (contadorDeNodes == 0) {
    fprintf(newFile, "\n");
  }
  fclose(newFile);
}

// Função para imprimir os resultados da query 4 em um ficheiro
void printQuery4(FILE *newFile, int temS, char *name, char *type,
                 int countTop10) {

  char *contarTop10 = intToString(countTop10);

  // Calcula o comprimento total da string de saída
  int total_len = strlen(name) + strlen(type) + 6;

  // Aloca memória para a nova string a ser escrita no ficheiro
  char *new_str =
      malloc((total_len + 1) * sizeof(char)); // +1 para o caractere '\0'

  if (temS) {
    // Formata a string de saída no formato: "name=type=discografia=country"
    snprintf(new_str, total_len + 1, "%s=%s=%s\n", name, type, contarTop10);
  } else {
    // Formata a string de saída no formato: "name;type;discografia;country"
    snprintf(new_str, total_len + 1, "%s;%s;%s\n", name, type, contarTop10);
  }
  // Escreve no ficheiro
  fprintf(newFile, "%s", new_str);

  // Liberta a memória alocada para cada campo
  free(contarTop10);
  free(new_str);

  // Fecha o ficheiro após a escrita
  fclose(newFile);
}

// Função para imprimir os resultados da query 5 em um ficheiro
void printQuery5(FILE *newFile, char **recomendacao, int numRecomendacoes) {
  for (int i = 0; i < numRecomendacoes; i++) {
    fprintf(newFile, "%s\n", recomendacao[i]);
  }

  // Fecha o ficheiro após a escrita
  fclose(newFile);
}
