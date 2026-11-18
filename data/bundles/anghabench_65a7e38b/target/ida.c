int __cdecl SCALE(long val, int mul, int div)
{
  if ( val >= 0 )
    return (div / 2 + mul * val) / div;
  else
    return (mul * val - div / 2) / div;
}