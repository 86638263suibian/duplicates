#ifndef FD_SCAN_
#define FD_SCAN_

#include "../include/sort.h"
#include "../include/memory.h"

error_t scan_for_duplicates(const void*, size_t, size_t,
  int64_t (*)(const void*, const void*), void**, size_t**, size_t*);

#endif
