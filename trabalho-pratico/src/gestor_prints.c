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
void printQuery2(GList **listaResposta, FILE *newFile) {
  GList *node = *listaResposta;
  int i = 0; // Contador para verificar se a lista está vazia

  // Percorre a lista de artistas
  while (node != NULL) {
    char *name;
    char *type;
    char *discografia;
    char *country;
    char *new_str;

    // Obtém o artista atual da lista
    Artists *currentArtist = (Artists *)node->data;

    // Extrai informações do artista
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

    // Formata a string de saída no formato: "name;type;discografia;country"
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type, discografia,
             country);

    // Escreve no ficheiro
    fprintf(newFile, "%s", new_str);

    // Avança para o próximo nó da lista
    node = node->next;

    i++; // Incrementa o contador

    // Liberta a memória alocada para cada campo
    free(name);
    free(type);
    free(discografia);
    free(country);
    free(new_str);
  }

  // Caso a lista esteja vazia, escreve apenas uma linha em branco no ficheiro
  if (i == 0)
    fprintf(newFile, "\n");

  // Fecha o ficheiro após a escrita
  fclose(newFile);
}
