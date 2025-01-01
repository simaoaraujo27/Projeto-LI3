#include "query6.h"
#include "glib.h"
#include "inputResult.h"
#include "outputResult.h"
#include "utils.h"
#include <string.h>

/*
Output:
listening time;#musics;artist;day;genre;favorite_album;hour
[artista_preferido_1;#musicas;listening_time]
[artista_preferido_2;#musicas;listening_time]
[. . . ]
*/
// percorrer o history
// guardar numa nova struct que estara na struct dos users:
// todas as musics_id (diferentes) que ele ouviu
// guardar o artista dessa musica e o tempo que passou a ouvir este artista e o
// numero de musicas distintas ouvidas desse artista ao somar todos os artistas
// temos o tempo total de audição guardar o album dessa musica e o tempo que
// passou a ouvir este album Fazer um array com 366 posicoes (dias possiveis)
// Inicializar com tudo a zero
// sempre que se passar por uma musica aumentar em 1 no array nesse dia
// Fazer um lista ligada de structs genero e tempo de reprodução à semelhança da
// GenreLikes
// Fazer um array com 24 posicoes (horas possiveis)
// Inicializar com tudo a zero
// sempre que se passar por uma musica aumentar em 1 no array nessa hora

// ATENCAO AO CASO DE HAVER MAIS DE UM ARTIST PARA A MUSICA
void query6(char *user_id, int year, int N, gestorUsers *gestorUsers, int i,
            int temS) {
  FILE *newFile = createFile(i);
  gpointer value;
  gpointer orig_key;

  gboolean found =
      lookUpUsersHashTable(gestorUsers, user_id, &value, &orig_key);
  if (found && year <= 2024) {
    int indice = 2024 - year;
    if (existUserResume(orig_key, indice)) {
      int listeningTime = getUserResumoListeningTime(orig_key, year);
      // printf("%d\n", listeningTime);
      char *listeningTimeStr = malloc(sizeof(char) * 16);
      converterParaTempo(listeningTime, listeningTimeStr);
      // printf("%s\n", listeningTimeStr);
      int numMusicasDiferentes =
          getUserResumoNumMusicasDiferentes(orig_key, year);
      // printf("%d\n", numMusicasDiferentes);
      char *numMusicasStr = intToString(numMusicasDiferentes);
      // printf("%s\n", numMusicasStr);
      char *artists = getUserResumoArtists(orig_key, year, N, temS);
      // printf("%s\n", artists);
      //  deve ser da forma: artistId;numMusicasDiferentes;listening_time\n ou
      //  com =
      int day = getUserResumoDay(orig_key, year);
      // printf("%d\n", day);
      char *dayStr = calculateData(day, year);
      // printf("%s\n", dayStr);
      char *genre = getUserResumoGenero(orig_key, year);
      // printf("%s\n", genre);
      char *album = getUserResumoAlbum(orig_key, year);
      // printf("%s\n", album);
      int hour = getUserResumoHora(orig_key, year);
      // printf("%d\n", hour);
      char *hourStr = intToHour(hour);
      // printf("%s\n", hourStr);
      char *favouriteArtist = strdup(artists);
      favouriteArtist[8] = '\0';
      // printf("%s\n", favouriteArtist);
      int total_len = strlen(listeningTimeStr) + strlen(numMusicasStr) +
                      strlen(favouriteArtist) + strlen(dayStr) + strlen(genre) +
                      strlen(album) + strlen(hourStr) +
                      7; // 5 para os ';' ou '=' e o '\0'
      if (N != 0)
        total_len += 1 + strlen(artists);
      char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'

      if (temS && N == 0) {
        // Formata a string concatenada com os dados do user, separando-os por
        // '='
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s=%s=%s\n",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr);
      } else if (temS && N != 0) {
        // Formata a string concatenada com os dados do user, separando-os por
        // '='
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s=%s=%s\n%s",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr, artists);
      } else if (N == 0) {
        // Formata a string concatenada com os dados do user, separando-os por
        // ';'
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s;%s;%s\n",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr);
      } else {
        // Formata a string concatenada com os dados do user, separando-os por
        // ';'
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s;%s;%s\n%s",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr, artists);
      }
      writeFile(newFile, new_str);

      // Liberta a memória alocada para as strings
      // free(listeningTimeStr);
      // free(numMusicasStr);
      // free(favouriteArtist);
      // free(dayStr);
      // free(genre);
      // free(album);
      // free(hourStr);
      // free(artists);
      // free(new_str);
    } else {
      writeFile(newFile, "\n");
    }
  } else {
    writeFile(newFile, "\n");
  }
}
/*
void query6(char *user_id, int year, int N, gestorHistory *gestorHistory){
    int numMusicasDiferentes = 0;
    int dias[366] = {0};
    int horas[24] = {0}; // quantos segundos de música ouviu nessa hora
    gpointer value, orig_key;
    // comecar a percorrer a historyTable
    char *userIdPercorrer = getHistoryUserId(orig_key);
    remove_quotes(user_id_percorrer);
    char *timestamp = getHistoryTimestamp(orig_key)
    remove_quotes(timestamp);
    int yearPercorrer = atoi(timestamp); //ver se o caso de trocar de um ano
para outro interessa if (!strcmp(user_id, userIdPercorrer) && yearPercorrer ==
year){ char *musicId = getHistoryMusicId(orig_key);
    //ver se ja esta no array com as musicas
    //se nao estiver:
    //adicionar esta musica e
    numMusicasDiferentes++;
    char *durationStr = getHistoryDuration(orig_key);
    int duration = converterParaSegundos(durationStr);
    gpointer value1, orig_key1;
    gboolean found1 =
      lookUpMusicsHashTable(gestorMusics, musicId, &value1, &orig_key1);
    if (found1) {
        char *artistId = getMusicArtistId(orig_key1);
        // ver se esta na lista ligada
        // se estiver aumentar o tempo de reprodução desse artista
        char *albumId = getMusicAlbumId(orig_key1);
        char *genre = getMusicGenre(orig_key1);
    }

    }
}
*/