void __cdecl test1(short n, int *x)
{
  short i; // [rsp+0h] [rbp-12h]
  short ia; // [rsp+0h] [rbp-12h]

  for ( i = 0; i < n; i = ia + 1 )
  {
    ia = i + 1;
    x[ia] = 0;
  }
}