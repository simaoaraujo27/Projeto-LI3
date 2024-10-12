#include "command_parser.h"

Artists *separateArtists(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  char *id = strtok(line, ";");
  char *nome = strtok(NULL, ";");
  char *descricao = strtok(NULL, ";");
  char *dinheiro_por_musica = strtok(NULL, ";");
  char *listaIdArtistas = strtok(NULL, ";");
  char *nacionalidade = strtok(NULL, ";");
  char *artista_solo = strtok(NULL, "\n");

  // muda o tipo das variáveis para poderem entrar na função newArtist
  int IdArtista = atoi(id);

  int DinheiroMusica = atoi(dinheiro_por_musica);

  int IdArtistas[lenght(listaIdArtistas)];

  for (int i = 0; i < lenght(listaIdArtistas); i++) {
    IdArtistas[i] = atoi(strtok(listaIdArtistas, ","));
  }

  bool typeArtist = 0;

  if (strcmp(artista_solo, "individual") == 0)
    typeArtist = 0;
  else
    typeArtist = 1;

  // cria um artista com a informação dada na linha do ficheiro
  Artists *artista = newArtist(IdArtista, nome, descricao, DinheiroMusica,
                               IdArtistas, nacionalidade, typeArtist);

  // retorna o artista criado
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

  int IdArtistas[lenght(artist_id)];

  for (int i = 0; i < lenght(artist_id); i++) {
    IdArtistas[i] = atoi(strtok(artist_id, ","));
  }

  int duration = atoi(duration_str);

  int year = atoi(year_str);
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
  char **liked_musics_Id = strtok(NULL, "\n");
  // cria um utilizador com as informações do ficheiro
  Users *user = newUser(username, email, first_name, last_name, birth_date,
                        country, subscription_type, liked_musics_Id);
  // retorna o utilizador criado
  return user;
}
