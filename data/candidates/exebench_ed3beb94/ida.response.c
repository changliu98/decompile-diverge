void __cdecl math_matrix_copy(float *from, float *to)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 16; ++i )
    to[i] = from[i];
}