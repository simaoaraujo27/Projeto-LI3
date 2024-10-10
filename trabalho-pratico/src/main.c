#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 2) {
    fp = stdin;
    fprintf(stderr, "Missing filename.\n");
    return 1;
  } else {
    char *filename = argv[1];
    fp = fopen(filename, "r");
    if (!fp) {
      perror("Error"); // Imprime "Error: No such file or directory"
      return -1;
    }
  }

  char *line = NULL;
  size_t len;

  getline(&line, &len, fp);

  printf("%s\n", line);

  return 0;
}