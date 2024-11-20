#ifndef _PARSER_H_
#define _PARSER_H_

void parserArtist(GHashTable *ArtistsTable, Artists *artist, FILE *errorsFile,
                  char *line);

void parserMusic(char *copia, gestorArtists *gestorArtist, char *line,
                 Musics *music, GHashTable *musicsTable, FILE *errorsFile);

void parserUser(char *line, gestorMusics *gestorMusic, FILE *errorsFile,
                GHashTable *usersTable);

#endif