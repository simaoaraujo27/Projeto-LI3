#include "command_parser.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_linked_list(GSList *list);
void free_linked_list(GSList *list);
void destroyUser(gpointer user);