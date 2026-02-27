#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "interpreter.h"



void interpret(const char* filename, Tape* tape) {
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
        *tape->cur_pos += 1;
        break;
      case '-':
        *tape->cur_pos -= 1;
        break;
      case '>':
        {
          char* p_next = tape->cur_pos + 1;
          if (p_next > tape->end_pos) {
            fprintf(stderr, "Error attempt to reach memory out of tape");
            exit(EXIT_FAILURE);
          }
        }
        tape->cur_pos += 1;
        break;
      case '<':
        {
          char* p_prev = tape->cur_pos - 1;
          if (p_prev < tape->start_pos) {
            fprintf(stderr, "Error attempt to reach memory out of tape");
            exit(EXIT_FAILURE);
          }
        }
        tape->cur_pos -= 1;
        break;
      case '.':
        fprintf(stdout, "%c", *tape->cur_pos);
        break;
      case '[':
        if (*tape->cur_pos == 0) {
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
        if (*tape->cur_pos != 0) {
          fseek(f, loop_stack[p_loop_stack - 1], SEEK_SET);
        } else {
          p_loop_stack--;
        }
        break;
      case ',':
        fflush(stdin);
        *tape->cur_pos = getchar();
        break;
      case ' ':
      case '/':
      case '\n':
      case '\t':
      case '\r':
        break;
      default:
        fprintf(stderr, "Command '%c' doesnt exist.\n", c);
    };
  }
}

