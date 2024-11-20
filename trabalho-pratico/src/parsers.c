#include "users.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void parserArtist(GHashTable *ArtistsTable, Artists *artist, FILE *errorsFile,
                  char *line) {
  // Extrai informações do artista para validação
  char *idConstituentLine = pegarArtistIdConstituent(artist);
  char *idConstituentCSV = pegarArtistIdConstituent(artist);
  char *type = pegarArtistType(artist);

  // Valida a linha e a lista de constituintes
  if (validateArtistLine(idConstituentLine, type) &&
      validateCSVList(idConstituentCSV)) {

    // Obtém o ID do artista e remove aspas
    char *id = getArtistId(artist);
    remove_quotes(id);

    // Verifica se o artista já está presente na hashtable
    Artists *existing_artist = g_hash_table_lookup(ArtistsTable, id);
    if (existing_artist != NULL) {
      destroyArtist(existing_artist); // Liberta o artista duplicado
    }

    // Insere o novo artista na tabela hash
    g_hash_table_insert(ArtistsTable, id, artist);
  } else {
    // Regista a linha no ficheiro de erros se não for válida
    fprintf(errorsFile, "%s", line);
    destroyArtist(artist); // Liberta a memória do artista inválido
  }
  free(idConstituentLine);
  free(idConstituentCSV);
  free(type);
}

void parserMusic(char *copia, gestorArtists *gestorArtist, char *line,
                 Musics *music, GHashTable *musicsTable, FILE *errorsFile) {
  char *id; // ID da música
  if (validateMusicsLine(copia, gestorArtist)) {
    // Se a linha for válida, separa os campos e cria um objeto Musics
    music = separateMusics(line);

    // Obtém o ID da música e insere na hashtable usando o ID como chave
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);
  } else {
    // Escreve a linha inválida no ficheiro de erros
    fprintf(errorsFile, "%s", line);
  }
}

void parserUser(char *line, gestorMusics *gestorMusic, FILE *errorsFile,
                GHashTable *usersTable) {
  char *copia = strdup(line); // Faz uma cópia segura da linha
  Users *user;
  char *username;
  // Valida a linha com base nas regras definidas
  if (validateUsersLine(copia, gestorMusic)) {
    user =
        separateUsers(line); // Se a linha for válida, separa os dados do user

    username = getUserUsername(user); // Obtém o nome do user

    // Insere o user na hashtable usando o username como chave
    g_hash_table_insert(usersTable, username, user);
  } else {
    // Se a linha for inválida, escreve no arquivo de erros
    fprintf(errorsFile, "%s", line);
  }
  free(copia); // Liberta a memória da cópia da linha
}
