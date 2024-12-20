// Estrutura que armazena informações sobre um álbum
struct albuns {
  char *id;         // Identificador único do álbum
  char *title;      // Título do álbum
  char *artists_id; // Lista de identificadores únicos dos artistas que lançaram
                    // o álbum;
  char *year;      // Ano de lançamento
  char *producers; // Lista de produtores
};