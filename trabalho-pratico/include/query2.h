#ifndef _QUERY2_H_
#define _QUERY2_H_

#include "gestores.h"

void query2(int numeroArtistas, char *country, Gestores *gestor, int i, int temS);

void processMusic(Musics *music, gestorArtists *gestorArtists,
                  int numeroArtistas, char *country, GList **listaResposta,
                  char *artistsId);

#endif