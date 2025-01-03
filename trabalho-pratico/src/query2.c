#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_prints.h"
#include "gestores.h"
#include "inputResult.h"
#include "musics.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função principal que executa a query 2
void query2(int numeroArtistas, char *country, Gestores *gestor, int i,
            int temS) {
  FILE *newFile = createFile(i);
  gestorArtists *gestorArtists = pegarGestorArtist(gestor);

  if (numeroArtistas == 0) {
    fprintf(newFile, "\n");
    fclose(newFile);
    return;
  }
  GList *listaResposta = getGListQuery2GestorArtist(gestorArtists);
  if (country == NULL) {
    GList *listaResposta = getGListQuery2GestorArtist(gestorArtists);
    printQuery2(listaResposta, newFile, numeroArtistas, temS, NULL);
  } else {
    printQuery2(listaResposta, newFile, numeroArtistas, temS, country);
  }
}