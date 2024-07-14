#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TAPE_CAPACITY 100

void printt(char* tape, size_t len) {
  printf("\n");
  for(size_t i = 0; i < len; i++) {
    printf("[%d]", tape[i]);
  }
  printf("\n");
};

void interpret(char* program, char* p_tape) {
  void* base_tape       = p_tape;
  char* final_tape      = p_tape + TAPE_CAPACITY;
  char* p_lpst          = {0};
  size_t program_length = strlen(program);

  while(*program != '\0') {
    switch (*program) {
      case '+':
        *p_tape += 1;
        program++;
        break;
      case '-':
        *p_tape -= 1;
         program++;
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
        program++;
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
        program++;
        break;
      case '.':
        {
          char* p_next = p_tape + 1;
          if (*p_next == '\0') {
            fprintf(stdout, "%c\n", *p_tape);
            program++;
            break;
          }
        }
        fprintf(stdout, "%c", *p_tape);
        program++;
        break;
      case '[':
        {
          void* p_loop = program + 1;
          p_lpst = p_loop;
        }
        program++;
        break;
      case ']':
        {
          if (*p_tape != 0)
            program = p_lpst;
          else
            program++;
        }
        break;
      case ',':
        {
          char b;
          scanf(" %c", &b);
          *p_tape = b;
        }
        program++;
        break;
      case ' ':
        program++;
        break;
      default:
        fprintf(stderr, "Command doesnt exist\n");
    };
  }
}

int main() {
  char* tape = calloc(TAPE_CAPACITY, sizeof(uint8_t));
  char code[] = "+++++ +++++ [> +++++ ++> +++++ +++++> +++ <<< -]> ++.> +++++.>+++.";

  interpret(&code[0], tape);
  
  return EXIT_SUCCESS;
}
