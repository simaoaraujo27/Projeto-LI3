#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include "users.h"
#include "artists.h"
#include "musics.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Artists *separateArtists(char *line);

Musics *separateMusics(char *line);

Users *separateUsers(char *line);

#endif