void __cdecl arrayadd(int *a, int *b)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 50; ++i )
    b[i] = a[i] + 5;
}