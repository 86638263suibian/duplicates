#ifndef FD_MEMORY_
#define FD_MEMORY_

#include "../include/include.h"

typedef struct memory_variables {
  size_t memory_allocated_so_far;
  size_t memory_allocated_previously;
  size_t allocation_amount;
  uint64_t realloc_counter;
  bool buffer_init;
} MemVars_t;

#define DEFAULT_MEMVARS { 0, 0, 0, 0, false }

error_t copy_byte_array (size_t, size_t, uint8_t**, const uint8_t*);
error_t MemVars_buffer_init (MemVars_t*, size_t, size_t, void**);
error_t MemVars_buffer_realloc_check (MemVars_t*, size_t, void**, void**);


#endif
