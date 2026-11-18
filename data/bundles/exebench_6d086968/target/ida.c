void __cdecl mat_copy_vector_l3(long *a, const long *b)
{
  *a = *b;
  a[1] = b[1];
  a[2] = b[2];
}