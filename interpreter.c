#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TAPE_CAPACITY 4096

void print_usage() {
  fprintf(stderr, "Usage: <program.b|bf>\n");
}

void interpret(char* program, char* p_tape) {
  void* base_tape       = p_tape;
  char* final_tape      = p_tape + TAPE_CAPACITY;

  FILE* f = fopen(program, "r");

  if (f == NULL) {
    fprintf(stderr, "Error reading file");
    return;
  }

  int c;
  long loop_stack[256];
  int loop_stack_ptr = 0;

  while((c = getc(f)) != EOF) {
    switch (c) {
      case '+':
        *p_tape += 1;
        break;
      case '-':
        *p_tape -= 1;
        break;
      case '>':
        {
          char* p_next = p_tape + 1;
          if (p_next > final_tape) {
            fprintf(stderr, "SEGFAULT");
            exit(EXIT_FAILURE);
          }
        }
        p_tape++;
        break;
      case '<':
        {
          void* p_prev = p_tape - 1;
          if (p_prev < base_tape) {
            fprintf(stderr, "SEGFAULT");
            exit(EXIT_FAILURE);
          }
        }
        p_tape--;
        break;
      case '.':
        fprintf(stdout, "%c", *p_tape);
        break;
      case '[':
        if (*p_tape == 0) {
          int open_brackets = 1;
          while (open_brackets != 0) {
            c = getc(f);
            if (c == EOF) {
              fprintf(stderr, "Unmatched '['\n");
              exit(EXIT_FAILURE);
            } else if (c == '[') {
              open_brackets++;
            } else if (c == ']') {
              open_brackets--;
            }
          }
        } else {
          loop_stack[loop_stack_ptr++] = ftell(f) - 1;
        }
        break;
      case ']':
        if (*p_tape != 0) {
          fseek(f, loop_stack[loop_stack_ptr - 1], SEEK_SET);
        } else {
          loop_stack_ptr--;
        }
        break;
      case ',':
        *p_tape = getchar();
        break;
      case ' ':
      case '\n':
      case '\t':
      case '\r':
        break;
      default:
        fprintf(stderr, "Command doesnt exist\n");
    };
  }
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

  interpret(argv[1], tape);

  free(tape);
  
  return EXIT_SUCCESS;
}
