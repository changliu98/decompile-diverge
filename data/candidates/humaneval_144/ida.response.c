int __cdecl func0(const char *x, const char *n)
{
  char den[101]; // [rsp+0h] [rbp-110h] BYREF
  char num[101]; // [rsp+70h] [rbp-A0h] BYREF
  int j; // [rsp+E0h] [rbp-30h]
  int i; // [rsp+E4h] [rbp-2Ch]
  int d; // [rsp+E8h] [rbp-28h]
  int c; // [rsp+ECh] [rbp-24h]
  int b; // [rsp+F0h] [rbp-20h]
  int a; // [rsp+F4h] [rbp-1Ch]
  const char *na; // [rsp+F8h] [rbp-18h]
  const char *xa; // [rsp+100h] [rbp-10h]

  xa = x;
  na = n;
  for ( i = 0; xa[i] != 47; ++i )
    num[i] = xa[i];
  num[i] = 0;
  a = atoi(num);
  j = 0;
  ++i;
  while ( xa[i] )
    den[j++] = xa[i++];
  den[j] = 0;
  b = atoi(den);
  for ( i = 0; na[i] != 47; ++i )
    num[i] = na[i];
  num[i] = 0;
  c = atoi(num);
  j = 0;
  ++i;
  while ( na[i] )
    den[j++] = na[i++];
  den[j] = 0;
  d = atoi(den);
  return c * a % (d * b) == 0;
}