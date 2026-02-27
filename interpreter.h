#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#define TAPE_CAPACITY 30000

typedef struct {
  char* cur_pos;
  char* start_pos;
  char* end_pos;
  size_t capacity;
} Tape;

void interpret(const char* filename, Tape* p_tape);

#endif

