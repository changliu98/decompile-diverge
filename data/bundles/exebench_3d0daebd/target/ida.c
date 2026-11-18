void __cdecl swt_max(double *sigIn, int sigInLength, double *sigMax)
{
  int count; // [rsp+0h] [rbp-1Ch]

  *sigMax = *sigIn;
  for ( count = 1; count < sigInLength; ++count )
  {
    if ( sigIn[count] > *sigMax )
      *sigMax = sigIn[count];
  }
}