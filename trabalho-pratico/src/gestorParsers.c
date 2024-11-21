#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "users.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int GestorParsers(FILE *fp, gestorArtists *gestorArtists,
                  gestorMusics *gestorMusics, gestorUsers *gestorUsers,
                  char *artistsPath, char *musicsPath, char *usersPath) {
  if (!GestorArtists(fp, gestorArtists, artistsPath))
    return 0;
  
  if (!GestorMusics(fp, gestorMusics, gestorArtists, musicsPath))
    return 0;

  if (!GestorUsers(fp, gestorUsers, gestorMusics, usersPath))
    return 0;

  return 1;
}