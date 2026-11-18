void __cdecl max1D_double(double *input, int len, double *retVals)
{
  int i; // [rsp+0h] [rbp-1Ch]

  *retVals = -1.0;
  retVals[1] = -INFINITY;
  for ( i = 0; i < len; ++i )
  {
    if ( input[i] > retVals[1] )
    {
      retVals[1] = input[i];
      *retVals = (double)i;
    }
  }
}