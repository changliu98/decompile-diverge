int __cdecl func0(int *operations, int size)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int num; // [rsp+4h] [rbp-18h]

  num = 0;
  for ( i = 0; i < size; ++i )
  {
    num += operations[i];
    if ( num < 0 )
      return 1;
  }
  return 0;
}