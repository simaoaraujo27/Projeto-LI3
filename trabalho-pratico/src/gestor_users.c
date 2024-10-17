#include "gestor_users.h"
#include "command_parser.h"
#include <glib.h>

void destroyUser(gpointer user) {
    return;
}

// Função para imprimir os valores da lista ligada
void print_linked_list(GSList *list) {
  for (GSList *l = list; l != NULL; l = l->next) {
    printf("%s ", (char *)l->data);
  }
  printf("\n");
}

// Função de destruição das listas ligadas (GSList)
void free_linked_list(GSList *list) { g_slist_free_full(list, g_free); }
