#include "../include/memory.h"


/* WARNING: Allocates memory (free() pointer > *copy_arr) */
error_t copy_byte_array (size_t elem_size, size_t no_of_elems,
  uint8_t **copy_arr, const uint8_t *arr)
{
  *copy_arr = malloc(elem_size * no_of_elems);
  if (*copy_arr == NULL) {
    return MALLOC_FAILURE;
  }

  memcpy(*copy_arr, arr, elem_size * no_of_elems);
  return SUCCESS;
}

/*
error_t MemVars_new (MemVars_t **out)
{
  MemVars_t default_memvars = (DEFAULT_MEMVARS);
  *out = malloc(sizeof(MemVars_t));
  if (*out == NULL) {
    return MALLOC_FAILURE;
  }
  memcpy(*out, default_memvars, sizeof(MemVars_t));
  return SUCCESS;
}
*/

/* WARNING: Allocates memory (free() pointer > *out) */
error_t MemVars_buffer_init (MemVars_t *m, size_t elem_size, size_t no_of_elems,
  void **out)
{
  m->allocation_amount = elem_size * no_of_elems;
  *out = malloc(m->allocation_amount);
  if (*out == NULL) {
    return MALLOC_FAILURE;
  }

  m->memory_allocated_so_far = m->allocation_amount;
  m->realloc_counter = m->allocation_amount / elem_size;
  m->memory_allocated_previously = 0;
  m->buffer_init = true;
  return SUCCESS;
}


 /*
  *  WARNING: Reallocates memory (free() pointer > *buffer)
  *
  *  NOTE: Put realloc_counter--; in loop iteration where buffer is written to
  */
error_t MemVars_buffer_realloc_check (MemVars_t *m, size_t elem_size,
  void **buffer, void **buffer_ptr)
{
  if (!(m->buffer_init)) {
    return MEMVARS_BUFFER_NO_INIT;
  }
  if (m->realloc_counter == 0) {
    ptrdiff_t buffer_ptr_pos = (uint8_t *)(*buffer_ptr) - (uint8_t *)(*buffer);

    m->memory_allocated_previously = m->memory_allocated_so_far;
    m->allocation_amount *= 2;
    *buffer = realloc(*buffer, m->allocation_amount);
    if (*buffer == NULL) {
      return MALLOC_FAILURE;
    }
    *buffer_ptr = (uint8_t *)(*buffer) + buffer_ptr_pos;

    m->memory_allocated_so_far = m->allocation_amount;
    m->realloc_counter =
      (m->memory_allocated_so_far
        - m->memory_allocated_previously)
      / elem_size;

    if (m->memory_allocated_so_far > MEMORY_LIMIT) {
      return MEMORY_LIMIT_EXCEEDED;
    }
  }
  return SUCCESS;
}
