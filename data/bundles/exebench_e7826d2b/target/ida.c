void __cdecl foo(int *p)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < 24; ++i )
    ++p[i];
}