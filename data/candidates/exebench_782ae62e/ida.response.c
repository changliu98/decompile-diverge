void __cdecl tosuper(char *a)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; a[i]; ++i )
  {
    if ( a[i] >= 97 && a[i] <= 122 )
      a[i] -= 32;
  }
}