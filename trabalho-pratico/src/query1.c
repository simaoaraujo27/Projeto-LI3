#include "artists.h"
#include "gestor_artists.h"
#include "gestor_users.h"
#include "inputResult.h"
#include "output_Result.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query1User(gestorUsers *gestorUser, char *line, int i, int temS) {
  line = line + 2;
  if (temS)
    line++;
  line[strlen(line) - 1] = '\0';
  FILE *newFile = createFile(i);
  gpointer value;
  gpointer orig_key;
  gboolean found = lookUpUsersHashTable(gestorUser, line, &value, &orig_key);
  if (found) {
    printQuery1User(orig_key, newFile, temS);
  } else {
    writeFile(newFile, "\n");
  }
}

void query1Artist(gestorArtists *gestorArtist, char *line, int i, int temS) {
  line = line + 2;
  if (temS)
    line++;
  line[strlen(line) - 1] = '\0';
  FILE *newFile = createFile(i);
  gpointer value;
  gpointer orig_key;
  gboolean found =
      lookUpArtistsHashTable(gestorArtist, line, &orig_key, &value);

  if (found) {
    printQuery1Artist(orig_key, newFile, temS);
  } else {
    writeFile(newFile, "\n");
  }
}
