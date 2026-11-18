int __cdecl C_Utils_compare_float_ptr(const float *item1, const float *item2)
{
  int v2; // eax

  if ( *item1 == *item2 )
    return 0;
  v2 = 1;
  if ( *item2 > *item1 )
    return -1;
  return v2;
}