#include "gestor_artists.h"
#include "musics.h"

void print(GList **listaResposta, int numeroArtistas, FILE *newFile) {
  GList *node = *listaResposta;
  char *name;
  char *type;
  int discografia;
  char *country;
  char *new_str;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    name = pegarArtistName(currentArtist);
    type = pegarArtistType(currentArtist);
    discografia = pegarArtistDiscografia(currentArtist);
    country = pegarArtistCountry(currentArtist);

    int total_len = strlen(name) + strlen(type) + 4 /*tamanho da discografia*/ +
                    strlen(country) + 4;              // 4 para os ';' e o '\0'
    new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    snprintf(new_str, total_len + 1, "%s;%s;%d;%s\n", name, type, discografia,
             country);

    if (node->next == NULL)
      fprintf(newFile, "%s", new_str);
    else
      fprintf(newFile, "%s\n", new_str);
    node = node->next;
  }
  fclose(newFile);
}
