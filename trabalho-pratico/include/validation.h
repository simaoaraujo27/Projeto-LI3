#ifndef _VALIDATION_H
#define _VALIDATION_H

#include <stdbool.h>
#include <glib.h>

// Funções para validar os campos
bool validateDate(char *date);
bool validateDuration(char *duration);
bool validateEmail(char *email);
bool validateSubscriptionType(char *type);
bool validateCSVList(char *list);
bool validateUsersLine(char *line, GHashTable *musicsTable);
bool validateArtistLine(char *idConstituent, char *type);
bool validateMusicsLine(char *line, GHashTable *artistsTable);

#endif