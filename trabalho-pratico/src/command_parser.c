#include "command_parser.h"
#include "validation.c"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artista = malloc(sizeof(struct artists));
  if (!artista) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }
  
  artista->id = atoi(strsep(&line, ";"));
  artista->nome = strdup(strsep(&line, ";"));
  artista->descricao = strdup(strsep(&line, ";"));
  artista->dinheiro_por_musica = atoi(strsep(&line, ";"));
  artista->listaIdArtistas = strdup(strsep(&line, ";"));
  artista->nacionalidade = strdup(strsep(&line, ";"));
  artista->artista_solo = strcmp(strsep(&line, "\n"), "individual") == 0;

  return artista;
}

Musics *separateMusics(char *line) {
  // separa cada linha pelas suas respetivas variáveis

  Musics *musica = malloc(sizeof(struct musics));
  if (!artista) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  musica->id = atoi(strsep(&line, ";"));
  musica->title = strdup(strsep(&line, ";"));
  musica->artist_id = strdup(strsep(&line, ";"));
  char *duration_str = strdup(strsep(&line, ";"));
  muisca->genre = strdup(strsep(&line, ";"));
  musica->year = atoi(strsep(&line, ";"));
  musica->lyrics = strdup(strsep(&line, ";"));


  if (validate_duration(duration_str))
    musica->duration = atoi(duration_str) /* horas */ * 3600 +
               atoi(duration_str + 3) /* minutos */ * 60 +
               atoi(duration_str + 6) /* segundos */;
  else
    musica->duration = -1;
  // a duração fica em segundos
  
  // retorna a musica criada
  return musica;
}


Users *separateUsers(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  users->username = strdup(strsep(&line, ";"));
  users->email = strdup(strsep(&line, ";"));
  users->first_name = strdup(strsep(&line, ";"));
  users->last_name = strdup(strsep(&line, ";"));
  users->birth_date = strdup(strsep(&line, ";"));
  users->country = strdup(strsep(&line, ";"));
  users->subscription_type = strdup(strsep(&line, ";"));
  users->liked_musics_id = strdup(strsep(&line, ";"));

  
  // retorna o utilizador criado
  return user;
}
