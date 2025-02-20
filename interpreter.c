#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "interpreter.h"

void interpret(const char* filename, char* p_tape) {
  void* base_tape  = p_tape;
  void* final_tape = p_tape + TAPE_CAPACITY;

  FILE* f = fopen(filename, "r");

  if (f == NULL) {
    fprintf(stderr, "Error reading file");
    return;
  }

  int c;
  long loop_stack[256];
  int p_loop_stack = 0;

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
          void* p_next = p_tape + 1;
          if (p_next > final_tape) {
            fprintf(stderr, "Error attempt to reach memory out of tape");
            exit(EXIT_FAILURE);
          }
        }
        p_tape++;
        break;
      case '<':
        {
          void* p_prev = p_tape - 1;
          if (p_prev < base_tape) {
            fprintf(stderr, "Error attempt to reach memory out of tape");
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
          loop_stack[p_loop_stack++] = ftell(f) - 1;
        }
        break;
      case ']':
        if (*p_tape != 0) {
          fseek(f, loop_stack[p_loop_stack - 1], SEEK_SET);
        } else {
          p_loop_stack--;
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
        fprintf(stderr, "Command '%c' doesnt exist\n", c);
    };
  }
}

