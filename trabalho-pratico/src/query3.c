#include "query3.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "inputResult.h"
#include "utils.h"
#include <stdio.h>

// Estrutura temporária para armazenar o género e a contagem de likes
// Esta struct irá servir para printar no ficheiro por ordem decrescente
struct generoLikes {
  char *genero; // género da música
  guint count;  // Contagem total de likes para o género
};

// Função de comparação para ordenar em ordem decrescente de likes
gint comparar_likes(gconstpointer a, gconstpointer b) {
  const GeneroLikes *g1 = a;
  const GeneroLikes *g2 = b;
  // Em caso de empate, ordena lexicograficamente
  if ((g1->count == g2->count)) {
    return (strcmp(g1->genero, g2->genero) < 0);
  } else {
    return ((g1->count < g2->count) - (g1->count > g2->count));
  }
}

void processUser(char *liked_musics_id, Gestores *gestor, NodoMusica **lista,
                 int userAge, guint idade_max) {

  // Percorre a lista de liked_musics_id
  char *music_id = strtok(liked_musics_id, ", ");
  while (music_id != NULL) {
    if (music_id[0] == '\'')
      music_id++;
    if (music_id[strlen(music_id) - 1] == '\'')
      music_id[strlen(music_id) - 1] = '\0';

    // Procura pela música na tabela
    gpointer music_value;
    gpointer orig_music_key;
    gboolean found = lookUpMusicsHashTable(pegarGestorMusic(gestor), music_id,
                                           &music_value, &orig_music_key);

    if (found) {
      char *genre = getMusicGenre(orig_music_key);
      *lista = adicionar_like(*lista, genre, userAge,
                              &idade_max); // Adiciona à lista
      free(genre);
    }
    music_id = strtok(NULL, ", ");
  }
  free(liked_musics_id);
}

NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, Gestores *gestor) {
  processAllUsers(gestor, &lista);
  return lista;
}

// Função principal para a query 3
void query3(int minAge, int maxAge, NodoMusica *lista, int i, int temS) {
  NodoMusica *l = lista;
  GList *generos_lista =
      NULL; // Lista para armazenar os géneros e as suas contagens de likes

  // Criar o arquivo para escrever
  FILE *newFile = createFile(i);

  // Itera sobre a lista de músicas
  while (l != NULL) {
    guint count = 0;
    // Soma os likes para as idades entre minAge e maxAge
    for (guint j = (guint)minAge; j <= (guint)maxAge; j++) {
      count += g_array_index(getLikesNodoMusic(l), guint,
                             j); // Soma os likes para a idade j
    }

    // Cria uma struct GeneroLikes e armazena o género e a contagem de likes
    GeneroLikes *genero_likes = malloc(sizeof(GeneroLikes));
    genero_likes->genero =
        strdup(getGeneroNodoMusic(l)); // Duplica a string do género
    genero_likes->count = count;       // Armazena a contagem de likes

    // Adiciona o nodo GeneroLikes à lista de géneros
    generos_lista = g_list_prepend(generos_lista, genero_likes);
    l = getProxNodoMusic(l); // Avança para o próximo nodo na lista
  }

  // Ordena a lista de géneros pela contagem de likes de forma decrescente
  generos_lista = g_list_sort(generos_lista, comparar_likes);

  int tudoAZero = 1; // Flag para verificar se todos os likes são zero
  // Escreve os géneros e suas contagens de likes no arquivo
  for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
    GeneroLikes *genero_likes = iter->data;
    if (genero_likes->count != 0) {
      remove_quotes(genero_likes->genero); // Remove as aspas do género
      if (temS) {
        fprintf(newFile, "%s=%d\n", genero_likes->genero,
                genero_likes->count); // Escreve no arquivo
      } else {
        fprintf(newFile, "%s;%d\n", genero_likes->genero,
                genero_likes->count); // Escreve no arquivo
      }
      tudoAZero = 0; // Se houver pelo menos um like, a flag é alterada
    }
    free(genero_likes->genero); // Liberta a memória alocada para o género
    free(genero_likes);         // Liberta a memória alocada para o GeneroLikes
  }

  // Se todos os likes forem zero, escreve uma linha em branco
  if (tudoAZero) {
    fprintf(newFile, "\n");
  }

  // Liberta a lista de géneros e fecha o arquivo
  g_list_free(generos_lista);
  fclose(newFile);
}
