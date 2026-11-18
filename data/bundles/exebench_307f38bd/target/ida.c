void __cdecl multiply(int factor1, int factor2, int *prod)
{
  double dAccum; // [rsp+0h] [rbp-20h]
  double dAccuma; // [rsp+0h] [rbp-20h]

  dAccum = (double)factor1 * (double)factor2;
  *prod = (factor2 * factor1) & 0x7FFFFFFF;
  if ( ((factor2 * factor1) & 0x7FFFFFFFu) >= 0x40000000 )
    dAccuma = (dAccum - 536870912.0) / 2147483648.0;
  else
    dAccuma = (dAccum + 536870912.0) / 2147483648.0;
  prod[1] = (int)dAccuma;
}