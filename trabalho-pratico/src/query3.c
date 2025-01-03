#include "query3.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "inputResult.h"
#include "utils.h"
#include <stdio.h>

struct generoLikes {
  char *genero;
  guint count;
};

gint comparar_likes(gconstpointer a, gconstpointer b) {
  const GeneroLikes *g1 = a;
  const GeneroLikes *g2 = b;
  if ((g1->count == g2->count)) {
    return (strcmp(g1->genero, g2->genero) > 0);
  } else {
    return ((g1->count < g2->count) - (g1->count > g2->count));
  }
}

NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, Gestores *gestor) {
  processAllUsers(gestor, &lista);
  return lista;
}

void query3(int minAge, int maxAge, NodoMusica *lista, int i, int temS) {
  NodoMusica *l = lista;
  GList *generos_lista = NULL;
  FILE *newFile = createFile(i);

  while (l != NULL) {
    guint count = 0;
    for (guint j = (guint)minAge; j <= (guint)maxAge; j++) {
      count += g_array_index(getLikesNodoMusic(l), guint, j);
    }
    GeneroLikes *genero_likes = malloc(sizeof(GeneroLikes));
    genero_likes->genero = strdup(getGeneroNodoMusic(l));
    genero_likes->count = count;

    generos_lista = g_list_prepend(generos_lista, genero_likes);
    l = getProxNodoMusic(l);
  }
  generos_lista = g_list_sort(generos_lista, comparar_likes);

  int tudoAZero = 1;
  for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
    GeneroLikes *genero_likes = iter->data;
    if (genero_likes->count != 0) {
      remove_quotes(genero_likes->genero);
      if (temS) {
        fprintf(newFile, "%s=%d\n", genero_likes->genero, genero_likes->count);
      } else {
        fprintf(newFile, "%s;%d\n", genero_likes->genero, genero_likes->count);
      }
      tudoAZero = 0;
    }
    free(genero_likes->genero);
    free(genero_likes);
  }
  if (tudoAZero) {
    fprintf(newFile, "\n");
  }

  g_list_free(generos_lista);
  fclose(newFile);
}
