/**
 * @file albuns.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do albuns
 */
#ifndef _ALBUNS_H_
#define _ALBUNS_H_

typedef struct albuns Albuns;

#include "gestor_artists.h"

char *getAlbumId(Albuns *album);

void setAlbumId(Albuns *album, char *id);
void setAlbumTitle(Albuns *album, char *title);
void setAlbumArtistsId(Albuns *album, char *artists_id);
void setAlbumYear(Albuns *album, char *year);
void setAlbumProducers(Albuns *album, char *producers);

Albuns *initAlbum();
void destroyAlbum(Albuns *album);

Albuns *separateAlbuns(char *line, gestorArtists *gestorArtists);

#endif