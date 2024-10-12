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
bool validate_date(char *date);
bool validate_duration(char *duration);
bool validate_email(char *email);
bool validate_subscription_type(char *type);
bool validate_Artist(Artists *artista);
bool validate_Music(Musics *musica);
bool validate_User(Users *user);

#endif