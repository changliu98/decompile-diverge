size_t func0(char **tuple,size_t size)

{
  size_t i;
  size_t total_size;
  size_t size_local;
  char **tuple_local;
  
  total_size = 0;
  for (i = 0; i < size; i = i + 1) {
    total_size = total_size + 8;
  }
  return total_size;
}