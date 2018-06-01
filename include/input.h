#ifndef FD_INPUT_
#define FD_INPUT_

#include "../include/memory.h"

typedef struct parser_state {
  char *char_buffer;
  char *char_last;
  char *char_ptr;

  double *num_buffer;
  double *num_ptr;
  void *num_buffer_v;
  void *num_ptr_v;

  size_t initial_num_buffer_size;

  size_t num_count;
  size_t char_count;
  bool decimal_point_flag;
  bool space_flag;
  bool init;
} ParserState_t;

#define DEFAULT_PARSERSTATE {\
    NULL, NULL, NULL,\
    NULL, NULL, NULL, NULL,\
    (INITIAL_NUM_BUFFER_SIZE),\
    0, 0, false, false, false\
  }

error_t ParserState_init (ParserState_t*);
error_t parse_input_file (FILE*, double**, size_t*);

#endif
