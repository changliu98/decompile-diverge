size_t __cdecl getSize(float *ptr)
{
  // The function unconditionally returns 8 regardless of the input pointer.
  // The parameter 'ptr' is unused and can be safely ignored.
  (void)ptr;
  return 8;
}