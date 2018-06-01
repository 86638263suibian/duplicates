#include "../include/error.h"

const char *const error_messages[ERROR_LAST] =
{
  "SUCCESS", /* SUCCESS */

  "Error: Unknown error", /* UNKOWN_ERROR */

  /* Function argument errors */
  "Error: Unexpected null pointer passed to" /* NULL_INPUT_POINTER */
    "function",
  "Error: Unexpected zero passed to function", /* INVALID_ZERO_INPUT */

  /* Memory errors */
  "Error: Out of memory", /* MALLOC_FAILURE */
  "Error: Memory limit exceeded", /* MEMORY_LIMIT_EXCEEDED */
  "Error: Reallocation check requested from" /* MEMVARS_BUFFER_NO_INIT */
    "uninitialised MemVars object",

  /* Command line argument errors */
  "Error: Attempt to open input file failed", /* FOPEN_FAILURE */
  "Error: No input file", /* NO_INPUT_FILE */
  "Error: Too many arguments", /* TOO_MANY_ARGUMENTS */

  /* Parser errors */
  "Error: Received invalid characters as input " /* FILE_INVALID_CHARACTERS */
    "(valid characters: decimal digits, '.', and whitespace)",
  "Error: Unexpected decimal point in input", /* UNEXPECTED_DECIMAL_POINT */
  "Error: Unexpected negative sign in input", /* UNEXPECTED_NEGATIVE_SIGN */
  "Error: Unexpected whitespace character in input", /* UNEXPECTED_SPACE */
  "Error: Number in input too long", /* INPUT_BUFFER_OVERRUN */
  "Error: Too many input values", /* TOO_MANY_NUMBERS */
  "Error: Failed to parse any numbers " /* PARSER_FAILURE */
    "(try adding newline to end of input)",
};
