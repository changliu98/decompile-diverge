void __cdecl ft_25_lines(const char *s, float *sign, float *val, int *nbr)
{
  float v4; // xmm0_4
  float v5; // xmm0_4

  nbr[1] = *s - 48;
  if ( (unsigned int)nbr[1] <= 9 )
  {
    if ( *nbr == 1 )
    {
      v4 = *sign / 10.0;
      *sign = v4;
    }
    v5 = *val * 10.0 + (float)nbr[1];
    *val = v5;
  }
}