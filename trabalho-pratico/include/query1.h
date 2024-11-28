#ifndef _QUERIE1_H_
#define _QUERIE1_H_

void query1User(gestorUsers *gestorUser, char *line, int i, int temS);

void query1Artist(gestorArtists *gestorArtist, char *line, int i, int temS);

void printQuery1(gpointer orig_key, FILE *newFile);

#endif