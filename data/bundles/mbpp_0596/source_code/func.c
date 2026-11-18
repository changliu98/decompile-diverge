#include <stdio.h>

#include <assert.h>



size_t func0(const char *tuple[], size_t size) {
  size_t total_size = 0;
  for (size_t i = 0; i < size; i++) {
    total_size += sizeof(tuple[i]);
  }
  return total_size;
}
