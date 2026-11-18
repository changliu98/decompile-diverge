int __cdecl inicializa(int *vec, int n, int *min, int *max)
{
  int v4; // ecx
  int i; // [rsp+0h] [rbp-24h]

  if ( n % 2 )
  {
    *min = *vec;
    *max = *vec;
    return 1;
  }
  else
  {
    i = 2;
    if ( *vec >= vec[1] )
    {
      *min = vec[1];
      v4 = *vec;
    }
    else
    {
      *min = *vec;
      v4 = vec[1];
    }
    *max = v4;
  }
  return i;
}