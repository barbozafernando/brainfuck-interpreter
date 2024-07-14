#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TAPE_CAPACITY 100

/*
+++++++++[>++++++++<-]>+++++++. = O
*/

void printt(char* tape, size_t len) {
  for(size_t i = 0; i < len; i++) {
    printf("[%d]", tape[i]);
  }
  printf("\n");
};

void interpret(char* program, char* p_tape) {
  void* base_tape       = p_tape;
  char* final_tape      = p_tape + TAPE_CAPACITY;
  char* p_loop          = {0};
  size_t program_length = strlen(program);

  for(size_t cell_index = 0; cell_index < program_length; cell_index++) {
    switch (*program) {
      case '+':
        *p_tape += 1;
        break;
      case '-':
        *p_tape -= 1;
        break;
      case '>':
        {
          char* p_next  = p_tape + 1;
          if (p_next > final_tape) {
            sprintf(stderr, "SEGFAULT");
            exit(EXIT_FAILURE);
          }
        }
        p_tape++;
        break;
      case '<':
        {
          void* p_prev = p_tape - 1;
          if (p_prev < base_tape) {
            sprintf(stderr, "SEGFAULT");
            exit(EXIT_FAILURE);
          }
        }
        p_tape--;
        break;
      case '.':
        fprintf(stdout, "%c", *p_tape);
        break;
      case '[':
        break;
        p_loop = p_tape + 1;
        break;
      case ']':
        break;
        {
          char* p_prevcell = p_loop - 2;
          if (*p_prevcell != 0)
            p_tape = p_loop;
        }
        break;
      default:
        fprintf(stderr, "Command doesnt exist\n");

    };

    program++;
  }

   //printt(p_tape, program_length);
}

int main() {
  char* tape = calloc(TAPE_CAPACITY, sizeof(uint8_t));
  //char code[] = "+++++++++[>++++++++<-]>+++++++.";
  char code[] = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";

  interpret(&code[0], tape);
  
  return EXIT_SUCCESS;
}
