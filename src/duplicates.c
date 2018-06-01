#include "../include/duplicates.h"


static error_t check_inputs (size_t elem_size, size_t no_of_elems,
  const uint8_t *arr)
{
  if (arr == NULL) {
    return NULL_INPUT_POINTER;
  }
  if (elem_size == 0 || no_of_elems == 0) {
    return INVALID_ZERO_INPUT;
  }
  return SUCCESS;
}


/*
 *  Find duplicate values in a sorted array. Write generic pointer -> output
 *  array to value referenced by out parameter. Write number of elements to
 *  value referenced by out_number_of_elements parameter.
 *
 *  WARNING: this function allocates memory to store output values, it is the
 *  responsibility of the caller to free this memory in order to avoid memory
 *  leak errors.
 */
error_t scan_for_duplicates (const void *arr, size_t elem_size,
  size_t no_of_elems, int64_t (*compare)(const void*, const void*),
  void **out, size_t **out_count, size_t *out_no_of_elems)
{
  error_t err = check_inputs(elem_size, no_of_elems, arr);
  if (err != SUCCESS) {
    *out = NULL;
    return err;
  } else {
    uint8_t *results;
    uint64_t *count;
    void *results_v;
    void *count_v;
    uint8_t *copy_arr;

    size_t total = 0;


    /* begin memory management */
    MemVars_t mem_vars = DEFAULT_MEMVARS;
    MemVars_t mem_vars_count = DEFAULT_MEMVARS;

    err = MemVars_buffer_init(&mem_vars, elem_size, no_of_elems, &results_v);
    if (err != SUCCESS) { *out = NULL; return err; }

    results = results_v;

    err = MemVars_buffer_init(&mem_vars_count, sizeof(uint64_t), no_of_elems,
      &count_v);
    if (err != SUCCESS) { *out = NULL; return err; }

    count = count_v;

    err = copy_byte_array(elem_size, no_of_elems, &copy_arr, arr);
    if (err != SUCCESS) { free(results); *out = NULL; return err; }
    else {
    /* end memory management */


      const uint8_t *last_elem_ptr;
      const uint8_t *arr_ptr;

      uint8_t *results_ptr = results;
      uint64_t *count_ptr = count;

      void *results_ptr_v;
      void *count_ptr_v;

      ptrdiff_t next_arr_ptr_pos = 1;
      ptrdiff_t saved_pos = 0;
      bool dup_found_flag = false;
      bool ptr_moved = false;

      /* sort input array */
      comb_sort(copy_arr, elem_size, no_of_elems, compare);

      last_elem_ptr = copy_arr + (no_of_elems - 1) * elem_size;

      for (arr_ptr = copy_arr; /* set array pointer to start of array */
           arr_ptr <= last_elem_ptr; /* while arr_ptr before last element */
           arr_ptr += elem_size) { /* inc arr_ptr by one elem_size per loop */



          /* handle case of counting last element */
          if ((arr_ptr == last_elem_ptr)

          /* if a duplicate has been found but */
          /* we are now at the end of its run  */
          || (compare(arr_ptr, arr_ptr + elem_size) != 0)) {

            if (dup_found_flag) {
              /* update count */
              next_arr_ptr_pos = ((arr_ptr - copy_arr) / elem_size) + 1;
              *count_ptr = (next_arr_ptr_pos - saved_pos);
              saved_pos = next_arr_ptr_pos;
              count_ptr++;
              ptr_moved = true;

              dup_found_flag = false;

            } else {
              saved_pos++;
            }
          }

        /* (if arr_ptr is not at the end of the array AND             */
        /* value at arr_ptr and value of element after arr_ptr are    */
        /* equal) AND (arr_ptr is at the start OR if value at arr_ptr */
        /* and value of element behind arr_ptr are not equal)         */
        if (((arr_ptr != last_elem_ptr) &&
           (compare(arr_ptr, arr_ptr + elem_size) == 0))
        && ((arr_ptr == copy_arr) ||
           (compare(arr_ptr, arr_ptr - elem_size) != 0))) {

          memcpy(results_ptr, arr_ptr, elem_size);
          mem_vars.realloc_counter--;

          results_ptr += elem_size;
          ptr_moved = true;
          total++;
          dup_found_flag = true;

        }
        if (ptr_moved) {

          /* begin memory management */
          results_ptr_v = results_ptr;
          results_v = results;
          err = MemVars_buffer_realloc_check(&mem_vars, elem_size,
            &results_v, &results_ptr_v);
          if (err != SUCCESS) {
            free(copy_arr);
            free(results);
            free(count);
            *out = NULL;
            return err;
          }
          results_ptr = results_ptr_v;
          results = results_v;

          count_ptr_v = count_ptr;
          count_v = count;
          err = MemVars_buffer_realloc_check(&mem_vars_count, sizeof(size_t),
            &count_v, &count_ptr_v);
          if (err != SUCCESS) {
            free(copy_arr);
            free(results);
            free(count);
            *out = NULL;
            return err;
          }
          count_ptr = count_ptr_v;
          count = count_v;
          /* end memory management */

          ptr_moved = false;

        }
      }
      *out = results;
      *out_count = count;
      *out_no_of_elems = total;
      free(copy_arr);
      return SUCCESS;
    }
  }
}
