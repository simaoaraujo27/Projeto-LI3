#include "validation.h"
#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "musics.h"
#include "users.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para validar uma data no formato aaaa/mm/dd
bool validateDate(char *date) {
  // Verifica se a data tem exatamente 10 caracteres
  if (strlen(date) != 10)
    return false;

  // Verifica se os separadores estão corretos ('/' nas posições 4 e 7)
  if (date[4] != '/' || date[7] != '/')
    return false;

  // Verifica se todos os outros caracteres são dígitos
  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i]))
      return false;
  }

  int year = atoi(date);      // Converte o ano para inteiro
  int month = atoi(date + 5); // Converte o mês para inteiro
  int day = atoi(date + 8);   // Converte o dia para inteiro

  // Verifica se o mês está entre 1 e 12 e o dia entre 1 e 31
  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  // Verifica se a data não é futura (limite: 2024/09/09)
  if (year > 2024 || (year == 2024 && (month > 9 || (month == 9 && day > 9))))
    return false;

  return true;
}

// Função para validar a duração no formato hh:mm:ss
bool validateDuration(char *duration) {
  remove_quotes(duration); // Remove as aspas
  // Verifica se a duração tem exatamente 8 caracteres
  if (strlen(duration) != 8)
    return false;
  // Verifica se os separadores estão corretos (':' nas posições 2 e 5)
  if (duration[2] != ':' || duration[5] != ':')
    return false;

  // Verifica se todos os outros caracteres são dígitos
  for (int i = 0; i < 8; i++) {
    if (i == 2 || i == 5)
      continue;
    if (!isdigit(duration[i]))
      return false;
  }

  int hours = atoi(duration);       // Converte as horas para inteiro
  int minutes = atoi(duration + 3); // Converte os minutos para inteiro
  int seconds = atoi(duration + 6); // Converte os segundos para inteiro

  // Verifica se as horas, minutos e segundos estão dentro dos limites válidos
  if (hours < 0 || hours > 99 || minutes < 0 || minutes > 59 || seconds < 0 ||
      seconds > 59)
    return false;

  return true;
}

// Função para validar um email no formato username@domain.com
bool validateEmail(char *email) {
  char *at = strchr(email, '@'); // Encontra o símbolo '@' no email
  if (!at) {
    return false;
  }
  char *dot = strrchr(at, '.'); // Encontra o ponto (.) após o '@'
  // Verifica se o domínio está correto (entre 2 a 3 caracteres após o ponto)
  if (!dot || dot - at < 2 || strlen(dot + 1) < 2 || strlen(dot + 1) > 3) {
    return false;
  }
  // Verifica se todos os caracteres antes do '@' são alfanuméricos
  for (char *p = email; p < at; p++) {
    if (!isalnum(*p)) {
      return false;
    }
  }

  // Verifica se todos os caracteres entre '@' e '.' são letras
  for (char *p = at + 1; p < dot; p++) {
    if (!isalpha(*p)) {
      return false;
    }
  }

  // Verifica se todos os caracteres após o ponto são letras minúsculas ou
  // alfabéticas
  for (char *p = dot + 1; *p; p++) {
    if (!islower(*p) && !isalpha(*p)) {
      return false;
    }
  }

  return true;
}

// Função para validar o tipo de assinatura ('normal' ou 'premium')
bool validateSubscriptionType(char *type) {
  return (strcmp(type, "normal") == 0 || strcmp(type, "premium") == 0);
}

// Função para validar uma lista CSV
bool validateCSVList(char *list) {
  int lastIndex = strlen(list) - 1;
  // Verifica se a lista está entre aspas e começa com '[', e termina com ']'
  return (list[0] == '"' && list[1] == '[' && list[lastIndex - 1] == ']' &&
          list[lastIndex] == '"');
}

// Função para validar os IDs das músicas de um user
bool validateMusicsIdUsers(char *musics_id, gestorMusics *gestorMusics) {
  remove_quotes(musics_id);       // Remove as aspas
  removeFstLast(musics_id);       // Remove os primeiros e últimos caracteres
  int l = (int)strlen(musics_id); // Obtém o comprimento da string

  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  // Processa os IDs das músicas
  while (l > 0) {
    if (l == (int)strlen(musics_id)) {
      musics_id = musics_id + 1;
    } else
      musics_id = musics_id + 3;
    key = strdup(strsep(&musics_id, "'")); // Separa o ID da música
    key[8] = '\0';                         // Limita o ID a 8 caracteres
    gboolean found = g_hash_table_lookup_extended(getMusicsTable(gestorMusics),
                                                  key, &orig_key, &value);
    if (!found) { // Se a música não for encontrada, retorna false
      free(key);
      return false;
    }
    free(key);
    l -= 12; // Ajusta o comprimento restante da string
  }

  return true;
}

// Função para validar uma linha de artistas
bool validateArtistLine(char *idConstituent, char *type) {
  removeFstLast(idConstituent); // Remove os primeiros e últimos caracteres
  removeFstLast(idConstituent); // Remove mais um caractere
  // Valida se o tipo de artista é 'individual' ou 'grupo'
  return (((strcmp(type, "individual") == 0) && strlen(idConstituent) == 0) ||
          ((strcmp(type, "group")) == 0 && (strlen(idConstituent) != 0)));
}

// Função para validar os artistas associados a uma música
bool validateMusicsArtists(char *artists_id, gestorArtists *gestorArtists) {
  remove_quotes(artists_id);       // Remove as aspas
  removeFstLast(artists_id);       // Remove os primeiros e últimos caracteres
  int l = (int)strlen(artists_id); // Obtém o comprimento da string
  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  // Processa os IDs dos artistas
  while (l > 0) {
    if (l == (int)strlen(artists_id)) {
      artists_id = artists_id + 1;
    } else
      artists_id = artists_id + 3;
    key = strdup(strsep(&artists_id, "'")); // Separa o ID do artista
    key[8] = '\0';                          // Limita o ID a 8 caracteres
    gboolean found = g_hash_table_lookup_extended(getArtistTable(gestorArtists),
                                                  key, &orig_key, &value);
    if (!found) { // Se o artista não for encontrado, retorna false
      free(key);
      return false;
    }
    free(key);
    l -= 12; // Ajusta o comprimento restante da string
  }

  return true;
}

// Função para validar uma linha de música
bool validateMusicsLine(char *line, gestorArtists *gestorArtists) {
  // Divide a linha em diferentes partes usando o delimitador ";"
  char *id = strdup(strsep(&line, ";"));
  char *title = strdup(strsep(&line, ";"));
  char *artists_id = strdup(strsep(&line, ";"));
  char *durationSeconds = strdup(strsep(&line, ";"));
  char *genre = strdup(strsep(&line, ";"));
  char *year = strdup(strsep(&line, "\n"));
  char *artist_id_copia = strdup(artists_id);

  // Valida a duração, o ano, o formato da lista CSV e os artistas associados à
  // música
  bool isValid = validateDuration(durationSeconds) && atoi(year) <= 2024 &&
                 validateCSVList(artists_id) &&
                 validateMusicsArtists(artist_id_copia, gestorArtists);

  free(id); // Libera a memória
  free(title);
  free(artists_id);
  free(durationSeconds);
  free(genre);
  free(year);
  free(artist_id_copia);

  return isValid;
}

// Função para validar uma linha de user
bool validateUsersLine(char *line, gestorMusics *gestorMusics) {
  // Divide a linha em diferentes partes usando o delimitador ";"
  char *username = strdup(strsep(&line, ";"));
  char *email = strdup(strsep(&line, ";"));
  remove_quotes(email); // Remove as aspas do email

  // Valida o formato do email
  if (!validateEmail(email)) {
    free(username);
    free(email);
    return false;
  }

  // Valida o nome, sobrenome e data de nascimento
  char *first_name = strdup(strsep(&line, ";"));
  char *last_name = strdup(strsep(&line, ";"));
  char *birth_date = strdup(strsep(&line, ";"));
  remove_quotes(birth_date); // Remove as aspas da data de nascimento

  if (!validateDate(birth_date)) {
    free(first_name);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    return false;
  }

  char *country = strdup(strsep(&line, ";"));
  char *subscription_type = strdup(strsep(&line, ";"));
  remove_quotes(subscription_type); // Remove as aspas do tipo de assinatura

  // Valida o tipo de assinatura
  if (!validateSubscriptionType(subscription_type)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    return false;
  }

  // Valida a lista de músicas favoritas
  char *liked_musics_id = strdup(line);
  removeLast(liked_musics_id); // Remove o último caractere
  if (!validateCSVList(liked_musics_id)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    free(liked_musics_id);
    return false;
  }

  // Valida os IDs das músicas favoritas
  if (!validateMusicsIdUsers(liked_musics_id, gestorMusics)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    free(liked_musics_id);
    return false;
  }

  // Libera a memória alocada
  free(first_name);
  free(country);
  free(subscription_type);
  free(last_name);
  free(birth_date);
  free(username);
  free(email);
  free(liked_musics_id);

  return true;
}
