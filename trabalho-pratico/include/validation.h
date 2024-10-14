#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "artists.h"
#include "musics.h"
#include "users.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções para validar os campos
bool validateDate(char *date);
bool validateDuration(char *duration);
bool validateEmail(char *email);
bool validateSubscriptionType(char *type);
bool validateArtist(Artists *artist);
bool validateMusic(Musics *music);
bool validateUser(Users *user);

#endif