#include "queries.h"
#include "artists.h"
#include "musics.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void query1(GHashTable *usersTable, char *line, int i) {
  line = line + 2;
  line[strlen(line) - 1] = '\0';

  // Cria o ficheiro e guarda-o na pasta resultados
  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");
  gpointer value;
  gpointer orig_key;

  gboolean found =
      g_hash_table_lookup_extended(usersTable, line, &value, &orig_key);

  if (found) {
    char *email = getUserEmail(orig_key);
    char *firstName = getUserFirstName(orig_key);
    char *lastName = getUserLastName(orig_key);
    char *age = calculate_age(getUserBirthDate(orig_key));
    char *country = getUserCountry(orig_key);

    int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                    strlen(age) + strlen(country) + 5; // 5 para os ';' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    // Concatenar as strings, separando-as por ;
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
             lastName, age, country);

    fprintf(newFile, "%s", new_str);
    fclose(newFile);

    free(email);
    free(firstName);
    free(lastName);
    free(age);
    free(country);
  }
}

int temAspas(char *line) {
  for (int i = 0; line[i]; i++) {
    if (line[i] == '"') {
      return 1;
    }
  }
  return 0;
}

void removeFstLast(char *str) {
  int len = strlen(str);
  // Verifica se a string começa e termina com aspas duplas
  // Move a string para "remover" as aspas duplas
  for (int i = 0; i < len - 1; i++) {
    str[i] = str[i + 1]; // Desloca os caracteres para a esquerda
  }
  str[len - 2] = '\0'; // Coloca o terminador nulo na nova posição
}

//util para remover o enter no fim
void removeLast(char *str) {
  int len = strlen(str);
  
  str[len - 1] = '\0';
}

void query2(int numeroArtistas, char *country, GHashTable *artistsTable,
            GList *listMusics, char *line, int i) {
  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");

  GList *listaResposta = NULL;
  for (GList *l = listMusics; l != NULL; l = l->next) {
    Musics *p = (Musics *)l->data;
    char *artistId = getMusicArtistId(p);
    remove_quotes(artistId);
    removeFstLast(artistId);
    int duracao = getMusicDuration(p);
    char *key;
    gpointer value;
    gpointer orig_key;
    int l = strlen(artistId);
    for (int j = 0; j < l; j += 12) {
      if (j == 0)
        artistId = artistId + 1;
      else
        artistId = artistId + 3;
      key = strdup(strsep(&artistId, "'"));
      if (g_hash_table_lookup_extended(artistsTable, key, &orig_key, &value)) {
        increment_artist_discografia(value, duracao, &listaResposta,
                                     numeroArtistas, country);
      }
    }
  }
  print(&listaResposta, numeroArtistas, newFile);
  colocaZero(artistsTable);
}

typedef struct GenreList {
    char *genre;
    int likes;
    struct GenreList *next;
} GenreList;

GenreList* createNode(char *genre, int likes) {
    GenreList *newNode = (GenreList*)malloc(sizeof(GenreList));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->genre = (char*)malloc(strlen(genre) + 1);
    if (newNode->genre == NULL) {
        return NULL;
    }
    strcpy(newNode->genre, genre);
    newNode->likes = likes;
    newNode->next = NULL;
    return newNode;
}

// inserção à cabeça
void insertNode(GenreList **head, char *genre, int likes) {
    GenreList *newNode = createNode(genre, likes);
    newNode->next = *head;
    *head = newNode;
}

void freeList(GenreList *head) {
    GenreList *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->genre);
        free(temp);
    }
}

void printList(GenreList *head) {
    GenreList *temp = head;
    while (temp != NULL) {
        printf("Gênero: %s, Likes: %d\n", temp->genre, temp->likes);
        temp = temp->next;
    }
}

// ordena a lista ligada por ordem decrescente de likes usando uma adaptação do bubbleSort
void sortListByLikes(GenreList **head) {
    if (*head == NULL) return;

    int trocado = 1;
    GenreList *temp; // percorre a lista
    GenreList *desordenado = NULL; // ate onde a lista esta desordenada (ja está ordenada deste nodo para a frente)

    while (trocado) { // enquanto alguma troca for feita continua
        trocado = 0;
        temp = *head;

        while (temp->next != desordenado) {
            if (temp->likes < temp->next->likes) {
                // Troca os dados dos nós
                int tempLikes = temp->likes;
                char *tempGenre = temp->genre;

                temp->likes = temp->next->likes;
                temp->genre = temp->next->genre;

                temp->next->likes = tempLikes;
                temp->next->genre = tempGenre;

                trocado = 1;
            }
            temp = temp->next;
        }
        desordenado = temp;
    }
}

void query3(int minAge, int maxAge, GList *listUsers, GHashTable *musicsTable, int i) {
  GenreList *lista = NULL;
  int age = 0;
  for (GList *l = listUsers; l != NULL; l = l->next) {
    Users *u = (Users *)l->data;
    Musics *music;
    char *username = getUserUsername(u);
    char *birthdate = getUserBirthDate(u);
    char *likedMusics;
    age = atoi(calculate_age(birthdate));
    char *key;
    gpointer value;
    gpointer orig_key;
    int continua = 1;
    if (age >= minAge && age <= maxAge){
    likedMusics = getUserLikedMusicsId(u);
    removeLast(likedMusics);
    removeFstLast(likedMusics);
    removeFstLast(likedMusics);
    int l = strlen(likedMusics);
    for (int j = 0; j < l; j += 12) {
      if (j == 0)
        likedMusics = likedMusics + 1;
      else
        likedMusics = likedMusics + 3;
      key = strdup(strsep(&likedMusics, "'"));
      if (g_hash_table_lookup_extended(musicsTable, key, &orig_key, &value)) {
        music = (Musics *)value;
        char *genero = getMusicGenre(music);
        remove_quotes(genero);
        for (GenreList *temp = lista; temp != NULL && continua; temp = temp->next){
          if (!strcmp(genero, temp->genre)){
            temp->likes++;
            continua = 0;
          }
        }
          if (continua){
        insertNode(&lista, genero, 1);
          }
        //printf("%s\n", genero);
        //contarLikesGenero(genero);
    }
    }

  }
  //percorrer todos os users
  // ver se estao dentro da faixa etaria
  //por cada user ver liked_musics_id
  //por cada uma das likedmusics ver o género e contar mais um like
  // printar por ordem decrescente
  // guardar 
} 
  sortListByLikes(&lista);
  
  //printList(lista);
  freeList(lista);
}