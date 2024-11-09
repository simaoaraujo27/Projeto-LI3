#include "gestor_artists.h"
#include "artists.h"
#include "validation.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

// Assumindo que estas funções e tipos já estão definidos:
// - separateArtists()
// - validateArtistLine()
// - validateCSVList()
// - pegarArtistIdConstituent()
// - pegarArtistType()
// - getArtistId()
// - remove_quotes()

void parseArtists(FILE *fp, GHashTable *artistsTable) {
  char *line = NULL;
  size_t len = 0;
  char *id;
  Artists *artist = NULL;

  // Abre o ficheiro para escrever os erros
  FILE *newFile = fopen("./resultados/artists_errors.csv", "w");
  if (newFile == NULL) {
    perror("Erro ao abrir o ficheiro de erros");
    return;
  }

  // Ignorar a primeira linha (cabeçalho)
  getline(&line, &len, fp);

  // Lê o ficheiro linha a linha
  while (getline(&line, &len, fp) != -1) {
    if (line != NULL) {
      // Processa e valida a linha
      artist = separateArtists(strdup(line));
      if (validateArtistLine(pegarArtistIdConstituent(artist),
                             pegarArtistType(artist)) &&
          validateCSVList(pegarArtistIdConstituent(artist))) {
        // Insere na hash table se for válido
        id = getArtistId(artist);
        remove_quotes(id);
        g_hash_table_insert(artistsTable, id, artist);
      } else {
        // Escreve a linha inválida no ficheiro de erros
        fprintf(newFile, "%s", line);
      }
      // Liberta a memória alocada para 'artist'
    }
  }

  // Fecha o ficheiro de erros e liberta a memória
  fclose(newFile);
  free(line);
}
