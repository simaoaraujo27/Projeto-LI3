#include "gestor_albuns.h"
#include <glib.h>
#include <stdio.h>

struct gestorAlbuns {
  FILE *errorsFile;        // Ficheiro para registo de erros
  GHashTable *albunsTable; // Hashtable para armazenar os albuns
};
