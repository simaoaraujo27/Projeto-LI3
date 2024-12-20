#include "nodo_musica.h"

// Definição da estrutura de dados que armazena o genero e a quantidade de likes
// desse género para cada idade
struct nodoMusica {
  char *genero;            // género da música
  GArray *likes;           // GArray que armazena a contagem de likes por idade
  struct nodoMusica *prox; // Pointer para o próximo nodo da lista
};

char *getGeneroNodoMusic(NodoMusica *l) { return l->genero; }
GArray *getLikesNodoMusic(NodoMusica *l) { return l->likes; }
void setGeneroNodoMusic(NodoMusica *l, char *genero) { l->genero = genero; }
void setLikesNodoMusic(NodoMusica *l, GArray *likes) { l->likes = likes; }
NodoMusica *getProxNodoMusic(NodoMusica *l) { return l->prox; }

// Função para criar um novo nodo com um género e inicializar o GArray de likes
NodoMusica *criar_nodo(char *genero, guint idade_max) {
  NodoMusica *nodo = (NodoMusica *)malloc(
      sizeof(struct nodoMusica)); // Aloca memória para o nodo

  if (nodo == NULL) {
    printf("Malloc failed!\n"); // Verifica se a alocação falhou
    return NULL;
  }

  nodo->genero = strdup(genero); // Duplica a string do género
  nodo->likes = g_array_new(
      FALSE, TRUE,
      sizeof(guint)); // Inicializa um GArray para armazenar inteiros (likes)

  // Inicializa cada faixa etária com 0 likes
  for (guint i = 0; i <= idade_max; i++) {
    guint zero = 0;
    g_array_append_val(nodo->likes,
                       zero); // Adiciona o valor 0 para cada idade até o limite
  }

  nodo->prox = NULL; // O próximo nodo é inicialmente NULL
  return nodo;
}

// Função para expandir todos os arrays de likes até o novo limite de idade
void expandir_arrays(NodoMusica *lista, guint nova_idade_max) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    guint tamanho_atual =
        atual->likes->len; // Obtém o tamanho atual do GArray de likes
    // Adiciona zeros até que o array atinja o novo tamanho
    for (guint i = tamanho_atual; i <= nova_idade_max; i++) {
      guint zero = 0;
      g_array_append_val(atual->likes, zero); // Adiciona o valor 0 no GArray
    }
    atual = atual->prox; // Avança para o próximo nodo na lista
  }
}

// Função para adicionar um like a uma idade específica
NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max) {
  // Se a idade for maior que a idade máxima, expande todos os arrays
  if (idade > *idade_max) {
    expandir_arrays(lista, idade); // Expande os arrays de todas as músicas
    *idade_max = idade;            // Atualiza o novo limite de idade máxima
  }

  NodoMusica *atual = lista;
  NodoMusica *anterior = NULL;

  // Procura o nodo com o género especificado
  while (atual != NULL) {
    if (strcmp(atual->genero, genero) ==
        0) { // Verifica se o género do nodo é igual ao fornecido
      // Adiciona um like na posição correspondente à idade
      guint *likes = &g_array_index(atual->likes, guint, idade);
      (*likes)++;   // Incrementa o número de likes para a idade especificada
      return lista; // Retorna a lista original, pois o nodo já foi encontrado e
                    // atualizado
    }
    anterior = atual;
    atual = atual->prox; // Avança para o próximo nodo
  }

  // Se não encontrou o género, cria um novo nodo
  NodoMusica *novo_nodo = criar_nodo(
      genero, *idade_max); // Cria um novo nodo com o género e a idade máxima
  guint *likes = &g_array_index(novo_nodo->likes, guint, idade);
  (*likes)++; // Incrementa o like para a idade especificada

  // Insere o novo nodo no final da lista
  if (anterior != NULL) {
    anterior->prox = novo_nodo;
  } else {
    lista = novo_nodo; // Caso a lista esteja vazia, o novo nodo é o primeiro
  }

  return lista;
}

// Função para libertar a memória da lista
void liberar_lista(NodoMusica *lista) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    NodoMusica *prox = atual->prox;
    g_array_free(atual->likes, TRUE); // Liberta o GArray de likes
    free(atual->genero);              // Liberta a string do género
    free(atual);                      // Liberta a memória do nodo
    atual = prox;                     // Avança para o próximo nodo
  }
}