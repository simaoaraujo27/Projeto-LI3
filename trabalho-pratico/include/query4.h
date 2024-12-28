#ifndef _QUERY4_H_
#define _QUERY4_H_

#include "gestor_musics.h"

void armazenarValores(char *musicId, int duration,
                      int timeStamp /* esta em dias ate ao dia 9 / 9 / 2024 */,
                      gestorMusics *gestorMusics, gestorArtists *gestorArtists,
                      GArray *Tops10);

void query4(gestorArtists *gestorArtists, char *DataFim, char *DataInicio,
            int contadorOutputs, int TemS);

#endif