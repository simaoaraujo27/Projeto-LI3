// Estrutura que armazena informações sobre o history (histórico de músicas
// ouvidas no sistema)

struct history {
  char *id;      // Identificador único do registo
  char *user_id; // Identificador único do utilizador a que o registo se refere
  char *music_id;  // Identificador único da música a que o registo se refere
  char *timestamp; // Data e hora em que a música foi ouvida pelo utilizador
  char *duration; // Tempo de duração da audição da música. E.g., um utilizador
                  // pode ter ouvido apenas 30 segundos de uma música
  char *platform; // plataforma em que a música foi reproduzida. I.e.,
                  // computador ou dispositivo móvel
};