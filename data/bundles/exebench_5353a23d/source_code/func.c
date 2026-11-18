#include <assert.h>

#include <stdlib.h>

#include <string.h>

void _vector_swap(size_t *first, size_t *second) {
  size_t temp = *first;
  *first = *second;
  *second = temp;
}
