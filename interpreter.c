#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAPE_CAPACITY 100

/*
+++++++++[>++++++++<-]>+++++++.
*/

void interpret(char* program) {
  while(*program != '\0') {
    printf("%c\n", *program);
    program++;
  }
}

int main() {
  uint8_t* tape = calloc(TAPE_CAPACITY, sizeof(uint8_t));
  uint32_t cell_index = 0;
  char code[] = "+++++++++[>++++++++<-]>+++++++.";


  interpret(&code[0]);
  

  return 0;
}
