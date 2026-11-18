double __cdecl sqrt_df(float *p)
{
  // Dereferences the input pointer and computes the square root of the float value.
  // The result is implicitly promoted to double to match the return type.
  return sqrt(*p);
}