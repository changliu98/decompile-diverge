void __cdecl func0(int number, int need, int remaining, int *result)
{
  if ( need <= remaining )
  {
    *result = need + number;
    result[1] = remaining - need;
  }
  else
  {
    *result = remaining + number;
    result[1] = 0;
  }
}