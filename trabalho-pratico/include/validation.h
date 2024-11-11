#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "gestor_artists.h"
#include "gestor_musics.h"
#include <glib.h>
#include <stdbool.h>

bool validateDate(char *date);
bool validateDuration(char *duration);
bool validateEmail(char *email);
bool validateSubscriptionType(char *type);
bool validateCSVList(char *list);
bool validateUsersLine(char *line, gestorMusics *gestorMusics);
bool validateArtistLine(char *idConstituent, char *type);
bool validateMusicsLine(char *line, gestorArtists *gestorArtists);

#endif