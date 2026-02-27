#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"

void print_usage() {
  fprintf(stderr, "Usage:\n\t./<program.b|bf>\n");
}

int is_brainfuck_file(const char* filename) {
  char* ext = strrchr(filename, '.');

  if (ext == NULL) {
    return EXIT_FAILURE;
  }

  ext++;

  if ((strcmp(ext, "b") == 0) || (strcmp(ext, "bf") == 0)) return EXIT_SUCCESS;

  return EXIT_FAILURE;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    print_usage();
    return EXIT_FAILURE;
  }

  const char* filename = argv[1];

  if (is_brainfuck_file(filename) == 1) {
    print_usage();
    return EXIT_FAILURE;
  }

  char* mem = calloc(TAPE_CAPACITY, sizeof(char));

  if (mem == NULL) {
    fprintf(stderr, "Memory allocation has failed.");
    return EXIT_FAILURE;
  }

  Tape tape = {
    .capacity = TAPE_CAPACITY,
    .start_pos = mem,
    .cur_pos = mem,
    .end_pos = mem + TAPE_CAPACITY,
  };

  interpret(filename, tape);

  free(tape.start_pos);
  
  return EXIT_SUCCESS;
}
