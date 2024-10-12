#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "command_parser.c"

// Funções para validar os campos
bool validate_date(char *date);
bool validate_duration(char *duration);
bool validate_email(char *email);
bool validate_subscription_type(char *type);
bool validate_year(char *year);
bool validate_Artist(Artists *artista);
bool validate_Music(Musics *musica);
bool validate_User(Users *user);

#endif