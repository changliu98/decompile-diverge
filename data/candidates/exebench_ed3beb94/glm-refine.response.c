void __cdecl math_matrix_copy(float *from, float *to)
{
  __movsd(to, from, 16);
}