#include "query3.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "utils.h"
#include <stdio.h>

// Definição da estrutura de dados que armazena o genero e a quantidade de likes
// desse género para cada idade
struct nodoMusica {
  char *genero;            // género da música
  GArray *likes;           // GArray que armazena a contagem de likes por idade
  struct nodoMusica *prox; // Pointer para o próximo nodo da lista
};

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
  return (g1->count < g2->count) - (g1->count > g2->count);
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

void processAllUsers(Gestores *gestor, NodoMusica **lista) {
  int IDADE_INICIAL = 120;
  guint idade_max = IDADE_INICIAL; // Inicializa a idade máxima

  // Itera sobre a tabela de users para processar as músicas que eles gostam
  GHashTableIter iter;
  gpointer hash_key, hash_value;
  g_hash_table_iter_init(&iter, getUsersTable(pegarGestorUser(gestor)));

  while (g_hash_table_iter_next(&iter, &hash_key, &hash_value)) {
    char *birthDate = getUserBirthDate(hash_value);
    char *age = calculate_age_str(birthDate); // Calcula a idade do user

    int userAge = atoi(age);
    char *liked_musics_id = getUserLikedMusicsId(hash_value);

    free(birthDate);
    free(age);

    removeFstLast(liked_musics_id); // Remove o primeiro e último caracteres

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
}

NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, Gestores *gestor) {
  processAllUsers(gestor, &lista);
  return lista;
}

// Função principal para a query 3
void query3(int minAge, int maxAge, NodoMusica *lista, int i) {
  NodoMusica *l = lista;
  GList *generos_lista =
      NULL; // Lista para armazenar os géneros e as suas contagens de likes

  // Criar o arquivo para escrever
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt"; // Path base para o arquivo
  char *new =
      malloc(sizeof(char) *
             (strlen(path) + 10)); // Aloca memória para o nome do arquivo
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt",
           i);               // Formata o nome do arquivo
  newFile = fopen(new, "w"); // Abre o arquivo para escrita

  // Itera sobre a lista de músicas
  while (l != NULL) {
    guint count = 0;
    // Soma os likes para as idades entre minAge e maxAge
    for (guint j = (guint)minAge; j <= (guint)maxAge; j++) {
      count +=
          g_array_index(l->likes, guint, j); // Soma os likes para a idade j
    }

    // Cria uma struct GeneroLikes e armazena o género e a contagem de likes
    GeneroLikes *genero_likes = malloc(sizeof(GeneroLikes));
    genero_likes->genero = strdup(l->genero); // Duplica a string do género
    genero_likes->count = count;              // Armazena a contagem de likes

    // Adiciona o nodo GeneroLikes à lista de géneros
    generos_lista = g_list_prepend(generos_lista, genero_likes);
    l = l->prox; // Avança para o próximo nodo na lista
  }

  // Ordena a lista de géneros pela contagem de likes de forma decrescente
  generos_lista = g_list_sort(generos_lista, comparar_likes);

  int tudoAZero = 1; // Flag para verificar se todos os likes são zero
  // Escreve os géneros e suas contagens de likes no arquivo
  for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
    GeneroLikes *genero_likes = iter->data;
    if (genero_likes->count != 0) {
      remove_quotes(genero_likes->genero); // Remove as aspas do género
      fprintf(newFile, "%s;%d\n", genero_likes->genero,
              genero_likes->count); // Escreve no arquivo
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
  free(new);
  fclose(newFile);
}
