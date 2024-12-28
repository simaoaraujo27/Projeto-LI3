#include "query6.h"
#include "glib.h"

/*
Output:
listening time;#musics;artist;day;genre;favorite_album;hour
[artista_preferido_1;#musicas;listening_time]
[artista_preferido_2;#musicas;listening_time]
[. . . ]
*/

// procurar este user_id e este year no history csv
// guardar numa nova struct:
// todas as musics_id (diferentes) que ele ouviu e o numero de musicas diferentes ouvidas 
// guardar o artista dessa musica e o tempo que passou a ouvir este artista
// ao somar todos os artistas temos o tempo total de audição
// guardar o album dessa musica e o tempo que passou a ouvir este album
// Fazer um array com 366 posicoes (dias possiveis)
// Inicializar com tudo a zero
// sempre que se passar por uma musica aumentar em 1 no array nesse dia
// Fazer um lista ligada de structs genero e tempo de reprodução à semelhança da GenreLikes
//Fazer um array com 24 posicoes (horas possiveis)
// Inicializar com tudo a zero
// sempre que se passar por uma musica aumentar em 1 no array nessa hora

struct categoriaTempo {
  char *categoria; // artista, album ou género
  guint time;  // tempo de reprodução em segundos
};
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
    int yearPercorrer = atoi(timestamp); //ver se o caso de trocar de um ano para outro interessa
    if (!strcmp(user_id, userIdPercorrer) && yearPercorrer == year){
    char *musicId = getHistoryMusicId(orig_key);
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