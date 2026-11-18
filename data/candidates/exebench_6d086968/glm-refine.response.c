void __cdecl mat_copy_vector_l3(long *a, const long *b)
{
  // Copy 3 contiguous 'long' elements (24 bytes) from b to a.
  // This is semantically equivalent to the original element-wise assignments.
  *(long (*)[3])a = *(const long (*)[3])b;
}