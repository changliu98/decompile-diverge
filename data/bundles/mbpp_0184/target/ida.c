bool __cdecl func0(int *list, int count, int num)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < count; ++i )
  {
    if ( list[i] < num )
      return 0;
  }
  return 1;
}