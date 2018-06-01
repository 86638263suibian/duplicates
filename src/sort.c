#include "../include/sort.h"

/*
 *  Swap two elements in an array
 */
error_t swap (void *elem_ptr_one, void *elem_ptr_two, size_t elem_size)
{
  uint8_t *buffer = malloc(elem_size);

  if (buffer == NULL) {
    return MALLOC_FAILURE;
  }
  if (elem_ptr_one == NULL || elem_ptr_two == NULL) {
    free(buffer);
    return NULL_INPUT_POINTER;
  }
  if (elem_size == 0) {
    free(buffer);
    return INVALID_ZERO_INPUT;
  }

  memcpy(buffer, elem_ptr_one, elem_size);
  memcpy(elem_ptr_one, elem_ptr_two, elem_size);
  memcpy(elem_ptr_two, buffer, elem_size);

  free(buffer);
  return SUCCESS;
}


 /*
  *  Sort array using the comb sort algorithm (faster variation of bubble sort)
  */
error_t comb_sort (void *arr, size_t elem_size, size_t no_of_elems,
  int64_t (*compare)(const void*, const void*))
{
  if (arr == NULL) {
    return NULL_INPUT_POINTER;
  }
  if (elem_size == 0 || no_of_elems == 0) {
    return INVALID_ZERO_INPUT;
  }
  if (no_of_elems == 1) {
    return SUCCESS;
  } else {
    const double shrink_factor = 1.3;
    const size_t bytes_per_elem = elem_size;
    const size_t one_elem = elem_size;
    size_t array_length_bytes = elem_size * no_of_elems;

    size_t diff_last_first_bytes = array_length_bytes - one_elem;
    size_t diff_last_first_elems = diff_last_first_bytes / bytes_per_elem;
    size_t gap_elems = (size_t)(floor(diff_last_first_elems / shrink_factor));
    size_t gap_bytes = gap_elems * bytes_per_elem;

    uint8_t *const array_start = arr;
    uint8_t *const array_end = array_start + diff_last_first_bytes;
    uint8_t *first_moving_ptr = array_start;
    uint8_t *second_moving_ptr = array_start + gap_bytes + one_elem;

    bool at_least_one_swap_occurred;
    bool gap_was_zero_last_run = false;

    do {
      at_least_one_swap_occurred = false;
      do {
        if (compare(first_moving_ptr, second_moving_ptr) == 1) {
          error_t err = swap(first_moving_ptr, second_moving_ptr, elem_size);
          if (err != SUCCESS) {
            return err;
          }
          at_least_one_swap_occurred = true;
        }
        first_moving_ptr += one_elem;
        second_moving_ptr += one_elem;
      } while (second_moving_ptr <= array_end);
      if (gap_elems == 0) {
        gap_was_zero_last_run = true;
      } else {
        gap_elems = (size_t)(floor(gap_elems / shrink_factor));
        gap_bytes = gap_elems * bytes_per_elem;
      }
      first_moving_ptr = array_start;
      second_moving_ptr = array_start + gap_bytes + one_elem;
    } while (!gap_was_zero_last_run || at_least_one_swap_occurred);
  }
  return SUCCESS;
}
