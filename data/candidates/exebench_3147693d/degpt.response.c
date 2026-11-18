size_t nrt_testing_atomic_inc(size_t *ptr)

{
  size_t sVar1;
  size_t out;
  size_t *ptr_local;
  
  sVar1 = *ptr;
  *ptr = sVar1 + 1;
  return sVar1 + 1;
}