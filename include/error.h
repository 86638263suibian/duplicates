#ifndef FD_ERROR_
#define FD_ERROR_

typedef enum error
{
  SUCCESS = 0,

  UNKNOWN_ERROR,

  /* Function argument errors */
  NULL_INPUT_POINTER,
  INVALID_ZERO_INPUT,

  /* Memory errors */
  MALLOC_FAILURE,
  MEMORY_LIMIT_EXCEEDED,
  MEMVARS_BUFFER_NO_INIT,

  /* Command line argument errors */
  FOPEN_FAILURE,
  NO_INPUT_FILE,
  TOO_MANY_ARGUMENTS,

  /* Parser errors */
  FILE_INVALID_CHARACTERS,
  UNEXPECTED_DECIMAL_POINT,
  UNEXPECTED_NEGATIVE_SIGN,
  UNEXPECTED_SPACE,
  INPUT_BUFFER_OVERRUN,
  TOO_MANY_NUMBERS,
  PARSER_FAILURE,

  ERROR_LAST
} error_t;

extern const char *const error_messages[];

#endif
