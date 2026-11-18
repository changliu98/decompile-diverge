char *__cdecl func0(int a, int b, int n)
{
  unsigned int i; // [rsp+8h] [rbp-18h]

  for ( i = 0; (int)(a * i) <= n; ++i )
  {
    if ( !((int)(n - a * i) % b) )
    {
      sprintf(func0_result, "x = %d, y = %d", i, (unsigned int)((int)(n - a * i) / b));
      return func0_result;
    }
  }
  return "No solution";
}