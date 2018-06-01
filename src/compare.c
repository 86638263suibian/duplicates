#include "../include/compare.h"

/*
 *  Comparison functions to pass to generic swap and sort functions
 */

int64_t compare_double (const void* number_p, const void* compared_to_p) {
  double number = *(const double *)number_p;
  double compared_to = *(const double *)compared_to_p;
  if (number > compared_to) {
   return 1;
  }
  if (number == compared_to) {
   return 0;
  }
  return -1; /* number < compared_to */
 }

/*
int64_t compare_int32 (const void* number_p, const void* compared_to_p) {
  int32_t number = *(const int32_t *)number_p;
  int32_t compared_to = *(const int32_t *)compared_to_p;
  if (number > compared_to) {
    return 1;
  }
  if (number == compared_to) {
    return 0;
  }
  return -1; / * number < compared_to * /
}


int64_t compare_int64 (const void* number_p, const void* compared_to_p) {
  int64_t number = *(const int64_t *)number_p;
  int64_t compared_to = *(const int64_t *)compared_to_p;
  printf(" ");
  if (number > compared_to) {
    return 1;
  }
  if (number == compared_to) {
    return 0;
  }
  return -1; / * number < compared_to * /
}
*/
