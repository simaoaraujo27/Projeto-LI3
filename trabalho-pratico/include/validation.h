#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include <glib.h>
#include <stdbool.h>

bool validatePlataformHistory(char *plataform);
bool validateDate(char *date);
bool validateDuration(char *duration);
bool validateEmail(char *email);
bool validateSubscriptionType(char *type);
bool validateCSVList(char *list);
bool validateUsersLine(char *line, gestorMusics *gestorMusics);
bool validateArtistLine(char *idConstituent, char *type);
bool validateMusicsLine(char *line, gestorArtists *gestorArtists,
                        gestorAlbuns *gestorAlbuns);
bool validateAlbumsLine(char *line, gestorArtists *gestorArtists);
bool validateHistoryLine(char *line);
bool validateAge(char *age);
bool validateId(char *id);
bool isAfter(const char *end, const char *begin);
bool allDigit(char *num);

#endif