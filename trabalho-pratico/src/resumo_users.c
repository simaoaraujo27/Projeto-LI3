#include "resumo_users.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artistaAudicoes {
  char *artista;
  guint tempo;
  guint numMusicas;
};

struct categoriaTempo {
  char *categoria;
  guint tempo;
};

struct resumo {
  GArray *idsMusics;
  GList *artists;
  GList *albuns;
  GList *generos;
  int dias[366];
  int horas[24];
  int listening_time;
  int num_musicas_diferentes;
};

GArray *initIdsMusics() {
  GArray *idsMusics = g_array_new(FALSE, FALSE, sizeof(char *));
  g_array_set_size(idsMusics, 10);
  for (int i = 0; i < (int)idsMusics->len; i++) {
    g_array_index(idsMusics, char *, i) = NULL;
  }

  return idsMusics;
}

Resumo *initResumo() {
  Resumo *res = (Resumo *)malloc(sizeof(Resumo));
  res->idsMusics = initIdsMusics();
  res->artists = NULL;
  res->albuns = NULL;
  res->generos = NULL;
  for (int i = 0; i < 366; i++) {
    res->dias[i] = 0;
  }
  for (int i = 0; i < 24; i++) {
    res->horas[i] = 0;
  }
  res->listening_time = 0;
  res->num_musicas_diferentes = 0;

  return res;
}

int elemUserResumeIdsMusics(Resumo *res, char *musicId) {
  GArray *idsMusics = res->idsMusics;
  char *musicPercorrer = NULL;
  for (int i = 0; (int)idsMusics->len; i++) {
    musicPercorrer = g_array_index(idsMusics, char *, i);
    if (musicPercorrer == NULL)
      return 0;
    if (!strcmp(musicId, musicPercorrer))
      return 1;
  }
  return 0;
}

int updateUserResumeArtists(Resumo *res, char *artistId, int duracao,
                            char *musicId) {

  int lentghArtistId = (int)strlen(artistId);

  char *currentArtist = NULL;
  int add = 0, continua = 1;
  while (lentghArtistId > 0) {
    if (lentghArtistId == (int)strlen(artistId)) {
      artistId = artistId + 1;
    } else {
      artistId = artistId + 3;
    }
    currentArtist = strdup(strsep(&artistId, "'"));
    currentArtist[8] = '\0';
    GList *a = res->artists;
    while (a != NULL && continua) {
      ArtistaTempo *artist = (ArtistaTempo *)a->data;
      if (strcmp(artist->artista, currentArtist) == 0) {
        artist->tempo += duracao;
        if (!elemUserResumeIdsMusics(res, musicId)) {
          g_array_append_val(res->idsMusics, musicId);
          artist->numMusicas++;
          add = 1;
        }
        continua = 0;
      }
      a = a->next;
    }
    if (continua) {
      ArtistaTempo *newArtist = (ArtistaTempo *)malloc(sizeof(ArtistaTempo));
      newArtist->artista = currentArtist;
      newArtist->tempo = duracao;
      newArtist->numMusicas = 0;
      if (!elemUserResumeIdsMusics(res, musicId)) {
        g_array_append_val(res->idsMusics, musicId);
        newArtist->numMusicas++;
        add = 1;
      }
      res->artists = g_list_prepend(res->artists, newArtist);
    }
    lentghArtistId -= 12;
    continua = 1;
  }
  return add;
}

void updateUserResumeAlbuns(Resumo *res, char *albumId, int duracao) {
  GList *a = res->albuns;
  int continua = 1;
  while (a != NULL && continua) {
    AlbumTempo *album = (AlbumTempo *)a->data;
    if (strcmp(album->categoria, albumId) == 0) {
      album->tempo += duracao;
      continua = 0;
    }
    a = a->next;
  }
  if (continua) {
    AlbumTempo *newAlbum = (AlbumTempo *)malloc(sizeof(AlbumTempo));
    newAlbum->categoria = strdup(albumId);
    newAlbum->tempo = duracao;
    res->albuns = g_list_prepend(res->albuns, newAlbum);
  }
}

void updateUserResumeGeneros(Resumo *res, char *gen, int duracao) {
  GList *g = res->generos;
  while (g != NULL) {
    GeneroTempo *genero = (GeneroTempo *)g->data;
    if (strcmp(genero->categoria, gen) == 0) {
      genero->tempo += duracao;
      return;
    }
    g = g->next;
  }
  GeneroTempo *newGenero = (GeneroTempo *)malloc(sizeof(GeneroTempo));
  newGenero->categoria = strdup(gen);
  newGenero->tempo = duracao;
  res->generos = g_list_prepend(res->generos, newGenero);
}

void updateUserResume(gpointer u, int year, int duracao, char *musicId,
                      char *artistId, char *albumId, char *genero, int dia,
                      int hora) {
  if (u == NULL)
    return;
  Users *user = (Users *)u;
  if (user == NULL)
    return;
  GArray *resumos = getUserResumo(user);

  if (resumos == NULL)
    return;
  int tamanho = resumos->len;
  int indice = 2024 - year;

  if (indice >= tamanho) {
    g_array_set_size(resumos, (guint)(indice + 1));

    for (int i = tamanho; i <= indice; i++) {
      g_array_index(resumos, Resumo *, i) = NULL;
    }
    tamanho = resumos->len;
  }

  Resumo *res = g_array_index(resumos, Resumo *, indice);
  if (res == NULL) {
    res = initResumo();
  }
  res->listening_time += duracao;
  int add = updateUserResumeArtists(res, artistId, duracao, musicId);
  res->num_musicas_diferentes += add;
  updateUserResumeAlbuns(res, albumId, duracao);
  updateUserResumeGeneros(res, genero, duracao);
  res->dias[dia]++;
  res->horas[hora] += duracao;
  g_array_index(resumos, Resumo *, indice) = res;
}

int getUserResumoListeningTime(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  return res->listening_time;
}

int getUserResumoNumMusicasDiferentes(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  return res->num_musicas_diferentes;
}

gint comparar_likes_Q6(gconstpointer a, gconstpointer b) {
  const ArtistaTempo *g1 = a;
  const ArtistaTempo *g2 = b;
  if ((g1->tempo == g2->tempo)) {
    return (strcmp(g1->artista, g2->artista) > 0);
  } else {
    return ((g1->tempo < g2->tempo) - (g1->tempo > g2->tempo));
  }
}

char *getUserResumoArtists(gpointer user, int year, int N, int temS) {
  if (N < 2) {
    struct users *u = (struct users *)user;
    GArray *resumos = getUserResumo(u);
    int indice = 2024 - year;
    Resumo *res = g_array_index(resumos, Resumo *, indice);
    GList *a = res->artists;
    int duracao = 0, numeroMusicas = 0;
    char *art = NULL;
    while (a != NULL) {
      ArtistaTempo *artist = (ArtistaTempo *)a->data;
      if ((int)artist->tempo > duracao ||
          ((int)artist->tempo == duracao &&
           (strcmp(artist->artista, art) > 0))) {
        duracao = (int)artist->tempo;
        numeroMusicas = (int)artist->numMusicas;
        if (art != NULL)
          free(art);
        art = strdup(artist->artista);
      }

      a = a->next;
    }

    char *duracaoStr = malloc(sizeof(char) * 16);
    converterParaTempo(duracao, duracaoStr);
    char *numeroMusicasStr = intToString(numeroMusicas);
    int total_len =
        strlen(art) + strlen(numeroMusicasStr) + strlen(duracaoStr) + 3;
    char *new_str = malloc((total_len + 1) * sizeof(char));
    if (temS) {
      snprintf(new_str, total_len + 1, "%s=%s=%s\n", art, numeroMusicasStr,
               duracaoStr);
    } else {
      snprintf(new_str, total_len + 1, "%s;%s;%s\n", art, numeroMusicasStr,
               duracaoStr);
    }
    free(art);
    free(numeroMusicasStr);
    free(duracaoStr);
    return new_str;
  } else {
    struct users *u = (struct users *)user;
    GArray *resumos = getUserResumo(u);
    int indice = 2024 - year;
    Resumo *res = g_array_index(resumos, Resumo *, indice);
    GList *a = res->artists;
    a = g_list_sort(a, comparar_likes_Q6);
    GList *current = a;
    char *new_str = NULL;
    int total_len = 0;

    for (int i = 0; i < N && current != NULL; i++) {
      ArtistaTempo *artist = (ArtistaTempo *)current->data;

      char *duracaoStr = malloc(sizeof(char) * 16);
      converterParaTempo(artist->tempo, duracaoStr);
      char *numeroMusicasStr = intToString(artist->numMusicas);

      int current_len = strlen(artist->artista) + strlen(numeroMusicasStr) +
                        strlen(duracaoStr) + 3;
      new_str = realloc(new_str, total_len + current_len + 1);
      if (new_str == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
      }

      if (temS) {
        snprintf(new_str + total_len, current_len + 1, "%s=%s=%s\n",
                 artist->artista, numeroMusicasStr, duracaoStr);
      } else {
        snprintf(new_str + total_len, current_len + 1, "%s;%s;%s\n",
                 artist->artista, numeroMusicasStr, duracaoStr);
      }

      total_len += current_len;

      free(duracaoStr);
      free(numeroMusicasStr);

      current = current->next;
    }

    return new_str;
  }
}

char *getUserResumoGenero(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  GList *g = res->generos;
  int duracao = 0;
  char *gen = NULL;
  while (g != NULL) {
    GeneroTempo *genero = (GeneroTempo *)g->data;
    if ((int)genero->tempo > duracao ||
        ((int)genero->tempo == duracao &&
         (strcmp(genero->categoria, gen) > 0))) {
      duracao = (int)genero->tempo;
      if (gen != NULL)
        free(gen);
      gen = strdup(genero->categoria);
    }
    g = g->next;
  }
  return gen;
}

char *getUserResumoAlbum(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  GList *a = res->albuns;
  int duracao = 0;
  char *alb = NULL;
  while (a != NULL) {
    AlbumTempo *album = (AlbumTempo *)a->data;
    if ((int)album->tempo > duracao ||
        ((int)album->tempo == duracao && (strcmp(album->categoria, alb) > 0))) {
      duracao = (int)album->tempo;
      if (alb != NULL)
        free(alb);
      alb = strdup(album->categoria);
    }
    a = a->next;
  }
  return alb;
}

int getUserResumoDay(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  int max = res->dias[0], maxInd = 0;
  for (int i = 1; i < 366; i++) {
    if (res->dias[i] >= max) {
      max = res->dias[i];
      maxInd = i;
    }
  }
  return maxInd;
}

int getUserResumoHora(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = getUserResumo(u);
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  int max = res->horas[0], maxInd = 0;
  for (int i = 1; i < 24; i++) {
    if (res->horas[i] > max) {
      max = res->horas[i];
      maxInd = i;
    }
  }
  return maxInd;
}

void destroyUserResumo(GArray *resumos) {
  for (int i = 0; i < (int)resumos->len; i++) {
    Resumo *resumo = g_array_index(resumos, Resumo *, i);
    if (resumo != NULL) {
      if (resumo->idsMusics != NULL) {
        g_array_free(resumo->idsMusics, TRUE);
      }
      if (resumo->artists != NULL) {
        GList *iterator = resumo->artists;
        while (iterator != NULL) {
          struct artistaAudicoes *data =
              (struct artistaAudicoes *)iterator->data;
          if (data->artista != NULL) {
            free(data->artista);
          }
          free(data);
          iterator = iterator->next;
        }
        g_list_free(resumo->artists);
      }
      if (resumo->albuns != NULL) {
        GList *iterator = resumo->albuns;
        while (iterator != NULL) {
          AlbumTempo *data = (AlbumTempo *)iterator->data;
          if (data->categoria != NULL) {
            free(data->categoria);
          }
          free(data);
          iterator = iterator->next;
        }
        g_list_free(resumo->albuns);
      }
      if (resumo->generos != NULL) {
        GList *iterator = resumo->generos;
        while (iterator != NULL) {
          GeneroTempo *data = (GeneroTempo *)iterator->data;

          if (data->categoria != NULL) {
            free(data->categoria);
          }
          free(data);
          iterator = iterator->next;
        }

        g_list_free(resumo->generos);
      }
      g_free(resumo);
    }
  }
}