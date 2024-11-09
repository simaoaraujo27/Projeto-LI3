#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

#include <glib.h>
#include <stdio.h>

void parseArtists(FILE *fp, GHashTable *artistsTable);

#endif