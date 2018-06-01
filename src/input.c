#include "../include/input.h"

/*
error_t ParserState_new (MemVars_t **out)
{
  Parser_t default_parser_state = DEFAULT_PARSERSTATE;
  *out = malloc(sizeof(Parser_t));
  if (*out == NULL) {
    return MALLOC_FAILURE;
  }
  memcpy(*out, default_parser_state, sizeof(Parser_t));
  return SUCCESS;
}
*/


error_t ParserState_init (ParserState_t *p) {
  p->char_buffer = malloc(CHAR_INPUT_BUFFER_SIZE);
  if ((p->char_buffer) == NULL) {
    return MALLOC_FAILURE;
  }

  p->char_last = p->char_buffer - 1 + (CHAR_INPUT_BUFFER_SIZE / sizeof(char));
  p->char_ptr = p->char_buffer;

  p->initial_num_buffer_size = INITIAL_NUM_BUFFER_SIZE;
  p->num_count = 0;
  p->char_count = 0;

  p->decimal_point_flag = false;
  p->space_flag = true;

  return SUCCESS;
}


/* WARNING: Allocates memory (free() pointer > *out) */
error_t parse_input_file (FILE *file, double **out, size_t *out_no_of_nums)
{
  ParserState_t p = DEFAULT_PARSERSTATE;
  MemVars_t mem_vars = DEFAULT_MEMVARS;

  error_t err = ParserState_init(&p);
  if (err != SUCCESS) {
    return err;
  }

  err = MemVars_buffer_init(&mem_vars, sizeof(double),
    p.initial_num_buffer_size, &(p.num_buffer_v));
  if (err != SUCCESS) {
    return err;
  } else {
    int c;
    p.num_buffer = p.num_buffer_v;
    p.num_ptr = p.num_buffer;

    while (true) {
      c = getc(file);


      if (isspace(c)) {
        if   ((p.char_ptr != p.char_buffer)
        && ((*(p.char_ptr - 1) == '-')
        ||  (*(p.char_ptr - 1) == '.'))) {
          free(p.num_buffer);
          free(p.char_buffer);
          return UNEXPECTED_SPACE;
        }
        if (!(p.space_flag)) {
          *(p.char_ptr) = '\0';
          p.char_ptr = p.char_buffer;
          *(p.num_ptr) = strtod(p.char_buffer, NULL);
          (p.num_ptr)++;
          (p.num_count)++;
          mem_vars.realloc_counter--;

          p.decimal_point_flag = false;
          p.space_flag = true;
        }
      } else {


      if (isdigit(c)) {
        *(p.char_ptr) = (char)c;
        (p.char_ptr)++;
        if (p.char_ptr > p.char_last) {
          free(p.num_buffer);
          free(p.char_buffer);
          return INPUT_BUFFER_OVERRUN;
        }
        p.space_flag = false;
      } else {


      if ((char)c == '.') {
        if (p.decimal_point_flag) {
          free(p.num_buffer);
          free(p.char_buffer);
          return UNEXPECTED_DECIMAL_POINT;
        }
        *(p.char_ptr) = (char)c;
        (p.char_ptr)++;
        if (p.char_ptr > p.char_last) {
          free(p.num_buffer);
          free(p.char_buffer);
          return INPUT_BUFFER_OVERRUN;
        }
        p.space_flag = false;
        p.decimal_point_flag = true;
      } else {


      if ((char)c == '-') {
        if (!(p.space_flag)) {
          free(p.num_buffer);
          free(p.char_buffer);
          return UNEXPECTED_NEGATIVE_SIGN;
        }
        *(p.char_ptr) = (char)c;
        (p.char_ptr)++;
        if (p.char_ptr > p.char_last) {
          free(p.num_buffer);
          free(p.char_buffer);
          return INPUT_BUFFER_OVERRUN;
        }
        p.space_flag = false;
      } else {


      if (c == EOF) {
        if (p.num_count == 0) {
          free(p.num_buffer);
          free(p.char_buffer);
          return PARSER_FAILURE;
        }
        *out = p.num_buffer;
        *out_no_of_nums = p.num_count;
        free(p.char_buffer);
        return SUCCESS;
      } else {


        free(p.num_buffer);
        free(p.char_buffer);
        return FILE_INVALID_CHARACTERS;
      }}}}}


      (p.char_count)++;
      if (p.num_count > MAX_INPUT_NUMBERS) {
        free(p.num_buffer);
        free(p.char_buffer);
        return TOO_MANY_NUMBERS;
      }


      p.num_ptr_v = p.num_ptr;
      p.num_buffer_v = p.num_buffer;
      err = MemVars_buffer_realloc_check(&mem_vars, sizeof(double),
        &(p.num_buffer_v), &(p.num_ptr_v));
      if (err != SUCCESS) {
        return err;
      }
      p.num_ptr = p.num_ptr_v;
      p.num_buffer = p.num_buffer_v;
    }
  }
}
