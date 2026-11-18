float __cdecl func0(int a, int b)
{
  int temp; // [rsp+10h] [rbp-10h]
  int digits; // [rsp+14h] [rbp-Ch]

  digits = 0;
  temp = b;
  if ( b )
  {
    while ( temp )
    {
      ++digits;
      temp /= 10;
    }
  }
  else
  {
    digits = 1;
  }
  return (double)a + (double)b / pow(10.0, (double)digits);
}