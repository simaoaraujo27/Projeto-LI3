#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

#include "artists.h"

// Declaração incompleta de gestorArtists (forward declaration)
typedef struct gestorArtists gestorArtists;

// Função para inicializar a estrutura gestorArtists
gestorArtists *initGestorArtists(const char *errorsFilePath,
                                 GHashTable *artistsTable);

GHashTable *getArtistTable(gestorArtists *gestorArtist);

// Função para liberar a estrutura gestorArtists e seus recursos
void freeGestorArtists(gestorArtists *gestor);

// Função para processar o arquivo de artistas usando gestorArtists
void parseArtists(FILE *fp, gestorArtists *gestor);

#endif // _GESTORARTISTS_H_
