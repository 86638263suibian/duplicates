#ifndef FD_SORT_
#define FD_SORT_

#include "../include/compare.h"

error_t swap (void*, void*, size_t);
error_t comb_sort (void*, size_t, size_t,
  int64_t (*)(const void*, const void*));

#endif
