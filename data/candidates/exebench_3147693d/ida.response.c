size_t __cdecl nrt_testing_atomic_inc(size_t *ptr)
{
  size_t v1; // rcx

  v1 = *ptr + 1;
  *ptr = v1;
  return v1;
}