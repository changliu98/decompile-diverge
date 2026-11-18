void __cdecl multiplyByConstant(int (*src)[3], int multiplier)
{
  int cols; // [rsp+0h] [rbp-14h]
  int rows; // [rsp+4h] [rbp-10h]

  for ( rows = 0; rows < 3; ++rows )
  {
    for ( cols = 0; cols < 3; ++cols )
      (*src)[3 * rows + cols] *= multiplier;
  }
}