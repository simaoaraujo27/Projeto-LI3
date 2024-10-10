#include <stdio.h>

int main(int argc, char *argv) {
  if (argc < 2) {
    fprintf(stderr, "Missing filename.\n");
    return 1;
  }

  char filename = argv[1];
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("Error"); // Imprime "Error: No such file or directory"
  }

  return 0;
}