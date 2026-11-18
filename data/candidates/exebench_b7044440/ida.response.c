void __cdecl shiftarray(int *a)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < 9; ++i )
    a[i] = a[i + 1];
  a[9] = -1;
}