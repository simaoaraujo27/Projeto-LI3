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
  char *id = strtok(line, ";");
  char *title = strtok(NULL, ";");
  char *artist_id = strtok(NULL, ";");
  char *duration_str = strtok(NULL, ";");
  char *genre = strtok(NULL, ";");
  char *year_str = strtok(NULL, ";");
  char *lyrics = strtok(NULL, "\n");

  // muda o tipo das variáveis para poderem entrar na função newMusic
  int IdMusica = atoi(id);

  int IdArtistas[strlen(artist_id)];

  for (int i = 0; i < strlen(artist_id); i++) {
    IdArtistas[i] = atoi(strtok(artist_id, ","));
  }

  int duration;

  if (validate_duration(duration_str))
    duration = atoi(duration_str) /* horas */ * 3600 +
               atoi(duration_str + 3) /* minutos */ * 60 +
               atoi(duration_str + 6) /* segundos */;
  else
    duration = -1;

  int year;

  if (strlen(year_str) == 4)
    year = atoi(year_str);
  else
    year = 3000;

  // cria uma musica com a informação dada na linha do ficheiro
  Musics *musica =
      newMusic(IdMusica, title, IdArtistas, duration, genre, year, lyrics);
  // retorna a musica criada
  return musica;
}


Users *separateUsers(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  char *username = strtok(line, ";");
  char *email = strtok(NULL, ";");
  char *first_name = strtok(NULL, ";");
  char *last_name = strtok(NULL, ";");
  char *birth_date = strtok(NULL, ";");
  char *country = strtok(NULL, ";");
  char *subscription_type = strtok(NULL, ";");
  char *liked_musics_Ids = strtok(NULL, "\n");

  int liked_musics_Id[strlen(liked_musics_Ids)];

  for (int i = 0; i < strlen(liked_musics_Ids); i++) {
    liked_musics_Id[i] = atoi(strtok(liked_musics_Ids, ","));
  }

  // cria um utilizador com as informações do ficheiro
  Users *user = newUser(username, email, first_name, last_name, birth_date,
                        country, subscription_type, liked_musics_Id);
  // retorna o utilizador criado
  return user;
}
