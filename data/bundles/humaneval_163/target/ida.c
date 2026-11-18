void __cdecl func0(int a, int b, int *out, int *size)
{
  int v4; // ecx
  int i; // [rsp+0h] [rbp-20h]
  int ba; // [rsp+18h] [rbp-8h]
  int aa; // [rsp+1Ch] [rbp-4h]

  aa = a;
  ba = b;
  *size = 0;
  if ( b < a )
  {
    aa = b;
    ba = a;
  }
  for ( i = aa; i <= ba; ++i )
  {
    if ( i < 10 && !(i % 2) )
    {
      v4 = (*size)++;
      out[v4] = i;
    }
  }
}