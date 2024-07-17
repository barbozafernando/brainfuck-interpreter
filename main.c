#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"

void print_usage() {
  fprintf(stderr, "Usage: <program.b|bf>\n");
}

int is_brainfuck_file(const char* filename) {
  char* ext = strrchr(filename, '.');

  if (ext == NULL) {
    return EXIT_FAILURE;
  }

  ext++;

  if ((strcmp(ext, "b") == 0) || (strcmp(ext, "bf") == 0)) {
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage();
    return EXIT_FAILURE;
  }

  const char* filename = argv[1];

  if (is_brainfuck_file(filename) == 1) {
    print_usage();
    return EXIT_FAILURE;
  }

  char* tape = calloc(TAPE_CAPACITY, sizeof(char));

  if (tape == NULL) {
    fprintf(stderr, "Memory allocation has failed.");
    return EXIT_FAILURE;
  }

  interpret(filename, tape);

  free(tape);
  
  return EXIT_SUCCESS;
}
