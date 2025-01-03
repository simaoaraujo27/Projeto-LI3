#include "nodo_musica.h"

struct nodoMusica {
  char *genero;
  GArray *likes;
  struct nodoMusica *prox;
};

char *getGeneroNodoMusic(NodoMusica *l) { return l->genero; }

GArray *getLikesNodoMusic(NodoMusica *l) { return l->likes; }

NodoMusica *getProxNodoMusic(NodoMusica *l) { return l->prox; }

NodoMusica *criar_nodo(char *genero, guint idade_max) {
  NodoMusica *nodo = (NodoMusica *)malloc(sizeof(struct nodoMusica));
  if (nodo == NULL) {
    printf("Malloc failed!\n");
    return NULL;
  }
  nodo->genero = strdup(genero);
  nodo->likes = g_array_new(FALSE, TRUE, sizeof(guint));
  for (guint i = 0; i <= idade_max; i++) {
    guint zero = 0;
    g_array_append_val(nodo->likes, zero);
  }
  nodo->prox = NULL;
  return nodo;
}

void expandir_arrays(NodoMusica *lista, guint nova_idade_max) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    guint tamanho_atual = atual->likes->len;
    for (guint i = tamanho_atual; i <= nova_idade_max; i++) {
      guint zero = 0;
      g_array_append_val(atual->likes, zero);
    }
    atual = atual->prox;
  }
}

NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max) {
  if (idade > *idade_max) {
    expandir_arrays(lista, idade);
    *idade_max = idade;
  }

  NodoMusica *atual = lista;
  NodoMusica *anterior = NULL;

  while (atual != NULL) {
    if (strcmp(atual->genero, genero) == 0) {
      guint *likes = &g_array_index(atual->likes, guint, idade);
      (*likes)++;
      return lista;
    }
    anterior = atual;
    atual = atual->prox;
  }

  NodoMusica *novo_nodo = criar_nodo(genero, *idade_max);
  guint *likes = &g_array_index(novo_nodo->likes, guint, idade);
  (*likes)++;
  if (anterior != NULL) {
    anterior->prox = novo_nodo;
  } else {
    lista = novo_nodo;
  }
  return lista;
}

void liberar_lista(NodoMusica *lista) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    NodoMusica *prox = atual->prox;
    g_array_free(atual->likes, TRUE);
    free(atual->genero);
    free(atual);
    atual = prox;
  }
}