#include "query3.h"
#include <stdio.h>
#include "utils.h"
//#include <.h>

struct nodoMusica {
  char *genero;
  GArray *likes;
  struct nodoMusica *prox;
};

// Função para criar um novo nodo com um genero e inicializar o GArray de likes
NodoMusica *criar_nodo(char *genero, guint idade_max) {
  NodoMusica *nodo = (NodoMusica *)malloc(
      sizeof(struct nodoMusica)); // Alocação de memória para o nodo

  if (nodo == NULL) {
    printf("Malloc failed!\n");
    return NULL;
  }

  nodo->genero = strdup(genero);
  nodo->likes = g_array_new(FALSE, TRUE,
                            sizeof(guint)); // Inicializa o GArray para inteiros

  // Inicializa cada faixa etária com 0 likes
  for (guint i = 0; i <= idade_max; i++) {
    guint zero = 0;
    g_array_append_val(nodo->likes, zero);
  }

  nodo->prox = NULL;
  return nodo;
}

// Função para expandir todos os arrays até o novo limite de idade
void expandir_arrays(NodoMusica *lista, guint nova_idade_max) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    guint tamanho_atual = atual->likes->len;
    // Adiciona zeros até que o array atinja o novo tamanho
    for (guint i = tamanho_atual; i <= nova_idade_max; i++) {
      guint zero = 0;
      g_array_append_val(atual->likes, zero);
    }
    atual = atual->prox;
  }
}

// Função para adicionar um like a uma faixa etária específica
NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max) {
  // Se a idade for maior que a idade máxima, expande todos os arrays
  if (idade > *idade_max) {
    expandir_arrays(lista, idade);
    *idade_max = idade; // Atualiza o novo limite de idade máxima
  }

  NodoMusica *atual = lista;
  NodoMusica *anterior = NULL;

  // Procura o nodo com o género especificado
  while (atual != NULL) {
    if (strcmp(atual->genero, genero) == 0) {
      // Adiciona um like na posição correspondente à idade
      guint *likes = &g_array_index(atual->likes, guint, idade);
      (*likes)++;
      return lista; // Retorna a lista original, pois o nodo já foi encontrado e
                    // atualizado
    }
    anterior = atual;
    atual = atual->prox;
  }

  // Se não encontrou o género, cria um novo nodo
  NodoMusica *novo_nodo = criar_nodo(genero, *idade_max);
  guint *likes = &g_array_index(novo_nodo->likes, guint, idade);
  (*likes)++;

  // Insere o novo nodo no final da lista
  if (anterior != NULL) {
    anterior->prox = novo_nodo;
  } else {
    lista = novo_nodo; // Caso a lista esteja vazia, o novo nodo é o primeiro
  }
  return lista;
}

// Função para liberar a memória da lista
void liberar_lista(NodoMusica *lista) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    NodoMusica *prox = atual->prox;
    g_array_free(atual->likes, TRUE); // Libera o GArray
    free(atual->genero);              // Libera a string do gênero
    free(atual);                      // Libera o nodo
    atual = prox;
  }
}

// Estrutura temporária para armazenar o género e a contagem de likes
struct generoLikes{
  char *genero;
  guint count;
};

// Função de comparação para ordenar em ordem decrescente de likes
gint comparar_likes(gconstpointer a, gconstpointer b) {
  const GeneroLikes *g1 = a;
  const GeneroLikes *g2 = b;
  return (g1->count < g2->count) - (g1->count > g2->count);
}

void query3(int minAge, int maxAge, NodoMusica *lista, int i) {
  NodoMusica *l = lista;
  GList *generos_lista = NULL;

  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt", i);
  newFile = fopen(new, "w");

  while (l != NULL) {
    guint count = 0;
    for (guint j = (guint)minAge; j <= (guint)maxAge; j++) {
      count += g_array_index(l->likes, guint, j);
    }

    // Adiciona o género e o total de likes para essa faixa etária
    GeneroLikes *genero_likes = malloc(sizeof(GeneroLikes));
    genero_likes->genero = strdup(l->genero);
    genero_likes->count = count;

    generos_lista = g_list_prepend(generos_lista, genero_likes);
    l = l->prox;
  }

  generos_lista = g_list_sort(generos_lista, comparar_likes);

  int tudoAZero = 1;
  // Escrevendo a lista ordenada no arquivo
  for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
    GeneroLikes *genero_likes = iter->data;
    if (genero_likes->count != 0) {

      remove_quotes(genero_likes->genero);
      fprintf(newFile, "%s;%d\n", genero_likes->genero, genero_likes->count);
      tudoAZero = 0;
    }

    // Liberando memória da string de género
    free(genero_likes->genero);
    free(genero_likes);
  }

  if (tudoAZero) {
    fprintf(newFile, "\n");
  }

  g_list_free(generos_lista);
  free(new);

  fclose(newFile);
}
