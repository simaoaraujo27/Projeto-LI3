#include "query6.h"
#include "glib.h"
#include "inputResult.h"
#include "output_Result.h"
#include "resumo_users.h"
#include "utils.h"
#include <string.h>

void query6(char *user_id, int year, int N, gestorUsers *gestorUsers, int i,
            int temS) {
  FILE *newFile = createFile(i);
  gpointer value;
  gpointer orig_key;

  // vê se o user esta na hashtable
  gboolean found =
      lookUpUsersHashTable(gestorUsers, user_id, &value, &orig_key);
  if (found && year <= 2024) {
    // calcula o indice do resumo deste user para o ano em questão
    int indice = 2024 - year;
    if (existUserResume(orig_key, indice)) { // se tiver algum registo de atividade neste ano
      int listeningTime = getUserResumoListeningTime(orig_key, year);
      char *listeningTimeStr = malloc(sizeof(char) * 16);
      converterParaTempo(listeningTime, listeningTimeStr);
      int numMusicasDiferentes =
          getUserResumoNumMusicasDiferentes(orig_key, year);
      char *numMusicasStr = intToString(numMusicasDiferentes);
      char *artists = getUserResumoArtists(orig_key, year, N, temS);
      int day = getUserResumoDay(orig_key, year);
      char *dayStr = calculateData(day, year);
      char *genre = getUserResumoGenero(orig_key, year);
      char *album = getUserResumoAlbum(orig_key, year);
      int hour = getUserResumoHora(orig_key, year);
      char *hourStr = intToHour(hour);
      char *favouriteArtist = strdup(artists);
      favouriteArtist[8] = '\0';
      int total_len = strlen(listeningTimeStr) + strlen(numMusicasStr) +
                      strlen(favouriteArtist) + strlen(dayStr) + strlen(genre) +
                      strlen(album) + strlen(hourStr) + 7;
      if (N != 0)
        total_len += 1 + strlen(artists);
      char *new_str = malloc((total_len + 1) * sizeof(char));

      if (temS && N == 0) {
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s=%s=%s\n",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr);
      } else if (temS && N != 0) {
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s=%s=%s\n%s",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr, artists);
      } else if (N == 0) {
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s;%s;%s\n",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr);
      } else {
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s;%s;%s\n%s",
                 listeningTimeStr, numMusicasStr, favouriteArtist, dayStr,
                 genre, album, hourStr, artists);
      }
      writeFile(newFile, new_str);

      free(listeningTimeStr);
      free(numMusicasStr);
      free(favouriteArtist);
      free(genre);
      free(album);
      free(hourStr);
      free(artists);
      free(new_str);
    } else { // caso o user não tenha nenhum registo de atividade neste ano
      writeFile(newFile, "\n");
    }
  } else {
    writeFile(newFile, "\n");
  }
}
