void __cdecl foo(int *x, int *y)
{
  int i; // [rsp+0h] [rbp-14h]
  int ia; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 8 && y[i] == i + 2; ++i )
    ;
  if ( i == 8 && *x == 1 )
  {
    *x = 8;
    for ( ia = 0; ia < 8; ++ia )
      y[ia] = ia + 9;
  }
  else
  {
    *x = 6;
  }
}