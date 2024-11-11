#include "musics.h"
#include "utils.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma música
struct musics {
  char *id;            // identificador único da música
  char *title;         // nome da música
  char *artist_id;     // lista de identificadores dos autores da música
  int durationSeconds; // tempo de duração em segundos
  char *genre;         // género da música
  int year;            // ano de lançamento
};

// Função para definir o id de uma música
void setMusicId(Musics *m, char *id) {
  remove_quotes(id); 
  m->id = id;        
}

// Função para definir o título de uma música
void setMusicTitle(Musics *m, char *title) {
  m->title = title; 
}

// Função para definir o(s) id(s) do(s) artista(s) de uma música
void setMusicArtistId(Musics *m, char *artist_id) {
  m->artist_id = artist_id;
}

// Função para definir a duração de uma música em segundos
void setMusicDurationSeconds(Musics *m, int durationSeconds) {
  m->durationSeconds = durationSeconds;
}

// Função para definir o género de uma música
void setMusicGenre(Musics *m, char *genre) {
  m->genre = genre; 
}

// Função para definir o ano de lançamento de uma música
void setMusicYear(Musics *m, int year) {
  m->year = year;
}

// Função para separar os campos de uma linha e criar uma estrutura Musics
Musics *separateMusics(char *line) {
  // Aloca a estrutura Musics
  Musics *music = malloc(sizeof(struct musics));
  if (!music) { // Verifica se a alocação foi bem-sucedida
    fprintf(stderr, "Malloc failed!"); // Caso contrário, exibe erro
    return NULL;                       // Retorna NULL se a alocação falhar
  }

  // Duplicação e atribuição dos campos usando strsep para separar os campos
  setMusicId(music, strdup(strsep(&line, ";")));
  setMusicTitle(music, strdup(strsep(&line, ";")));
  setMusicArtistId(music, strdup(strsep(&line, ";")));

  char *duration_str = strdup(strsep(&line, ";"));
  setMusicGenre(music, strdup(strsep(&line, ";")));

  char *year_str = strdup(strsep(&line, ";"));
  setMusicYear(music, atoi(year_str)); // Converte o ano de string para inteiro
  free(year_str);                      // Liberta a memória alocada para o ano

  // Configuração da duração, com validação
  if (validateDuration(duration_str)) { // Valida a duração
    setMusicDurationSeconds(music,
                            atoi(duration_str) * 3600 +       // horas
                                atoi(duration_str + 3) * 60 + // minutos
                                atoi(duration_str + 6));      // segundos
  } else {
    setMusicDurationSeconds(music,
                            -1); // Caso a validação falhe, define como -1
  }
  free(duration_str); // Liberta a memória alocada para a duração

  return music; // Retorna a estrutura Musics preenchida
}

// Função para validar uma música
bool validateMusic(Musics *music) {
  return (music->durationSeconds != -1 &&
          music->year <= 2024); // Valida a duração e o ano
}

// Funções para obter os campos de uma música
char *pegarMusicId(Musics *m) { return strdup(m->id); }

char *pegarMusicTitle(Musics *m) { return strdup(m->title); }

char *pegarMusicArtistId(Musics *m) { return strdup(m->artist_id); }

int pegarMusicDuration(Musics *m) { return (m->durationSeconds); }

char *pegarMusicGenre(Musics *m) { return strdup(m->genre); }

int pegarMusicYear(Musics *m) { return (m->year); }

// Funções para obter os campos de uma música com um gpointer
char *getMusicId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->id);
}

char *getMusicTitle(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->title);
}

char *getMusicArtistId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->artist_id);
}

int getMusicDuration(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->durationSeconds);
}

char *getMusicGenre(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->genre);
}

int getMusicYear(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->year);
}

// Função para libertar a memória alocada para a estrutura Musics
void destroyMusic(Musics *music) {
  if (music) {
    free(music->id);        // Liberta memória do id
    free(music->title);     // Liberta memória do título
    free(music->artist_id); // Liberta memória do identificador do artista
    free(music->genre);     // Liberta memória do género

    free(music); // Liberta a estrutura Musics em si
  }
}
