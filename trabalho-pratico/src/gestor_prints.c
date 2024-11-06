#include "gestor_artists.h"
#include "musics.h"

char *SegundosParaHoras(int segundos) {
  int horas = segundos / 3600;
  int minutos = (segundos % 3600) / 60;
  int segundosRestantes = segundos % 60;
  char *hora = malloc(10);
  snprintf(hora, 16, "%02d:%02d:%02d", horas, minutos, segundosRestantes);
  return hora;
}

void print(GList **listaResposta, int numeroArtistas, FILE *newFile) {
  GList *node = *listaResposta;
  char *name;
  char *type;
  char *discografia;
  char *country;
  char *new_str;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    name = pegarArtistName(currentArtist);
    type = pegarArtistType(currentArtist);
    discografia = SegundosParaHoras(pegarArtistDiscografia(currentArtist));
    country = pegarArtistCountry(currentArtist);

    int total_len = strlen(name) + strlen(type) + 4 /*tamanho da discografia*/ +
                    strlen(country) + 4;              // 4 para os ';' e o '\0'
    new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    remove_quotes(name);
    remove_quotes(country);
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type, discografia,
             country);

    if (node->next == NULL)
      fprintf(newFile, "%s", new_str);
    else
      fprintf(newFile, "%s", new_str);
    free(new_str);
    node = node->next;
  }
  fprintf(newFile,"\n");
  fclose(newFile);
}
