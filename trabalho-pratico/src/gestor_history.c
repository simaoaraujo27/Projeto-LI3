#include "gestor_history.h"
#include <glib.h>
#include <stdio.h>

struct gestorHistory {
  FILE *errorsFile;         // Ficheiro para registo de erros
  GHashTable *historyTable; // Hashtable para armazenar os albuns
};
