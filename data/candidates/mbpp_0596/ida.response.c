size_t __cdecl func0(const char **tuple, size_t size)
{
  size_t i; // [rsp+0h] [rbp-20h]
  size_t total_size; // [rsp+8h] [rbp-18h]

  total_size = 0LL;
  for ( i = 0LL; i < size; ++i )
    total_size += 8LL;
  return total_size;
}