int __cdecl func0(int *lst, int size)
{
  int i; // [rsp+0h] [rbp-20h]
  int second; // [rsp+4h] [rbp-1Ch]
  int first; // [rsp+8h] [rbp-18h]

  if ( size < 2 )
    return -1;
  first = 0x7FFFFFFF;
  second = 0x7FFFFFFF;
  for ( i = 0; i < size; ++i )
  {
    if ( lst[i] >= first )
    {
      if ( lst[i] < second && lst[i] != first )
        second = lst[i];
    }
    else
    {
      second = first;
      first = lst[i];
    }
  }
  if ( second == 0x7FFFFFFF )
    return -1;
  else
    return second;
}