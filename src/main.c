#include "../include/duplicates.h"
#include "../include/input.h"


int main (int argc, char **argv)
{
  if (argc < 2) {
    printf("%s\n", error_messages[NO_INPUT_FILE]);
    return -1;
  }
  if (argc > 2) {
    printf("%s\n", error_messages[TOO_MANY_ARGUMENTS]);
    return -1;
  } else {

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
      return FOPEN_FAILURE;
    } else {

      double *input_buffer = NULL;
      size_t no_of_values;
      size_t size_of_values = sizeof(double);

      error_t err = parse_input_file(file, &input_buffer, &no_of_values);
      if (err != SUCCESS) {
        printf("%s\n", error_messages[err]);
        return -1;
      } else {

        void *duplicates_v = NULL;
        size_t *count_each = NULL;
        size_t no_of_dups;

        err = scan_for_duplicates(input_buffer, size_of_values, no_of_values,
          &compare_double, &duplicates_v, &count_each, &no_of_dups);
        if (err != SUCCESS) {
          printf("%s\n", error_messages[err]);
          return -1;
        } else {
          if (no_of_dups == 0) {
            printf("<0>\n(0) nil\n"); return 0;
          } else {
          double *duplicates = duplicates_v;
          uint64_t i;

          printf("<%lu>\n", no_of_dups);
          for (i = 0; i < no_of_dups - 1; i++) {
            printf("(%lu) %.15g    ", count_each[i], duplicates[i]);
          }
          printf("(%lu) %.15g\n", count_each[no_of_dups - 1],
            duplicates[no_of_dups - 1]);

          free(input_buffer);
          free(duplicates_v);
          free(count_each);
          return 0;
          }
        }
      }
    }
  }
}
