double __cdecl func0(int a, int b)
{
  double v3; // [rsp+0h] [rbp-20h]

  if ( a < 0 || b < 0 )
    return -1.0;
  v3 = 3.0 * sqrt(3.0);
  return v3 * pow((double)a, 2.0) / (double)(4 * b);
}