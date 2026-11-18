int __cdecl arrayFind(int elem, int *list, int length)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; ; ++i )
  {
    if ( i >= length )
      return -1;
    if ( list[i] == elem )
      break;
  }
  for ( j = 0; j < i; ++j )
    list[i - j] = list[i - j - 1];
  *list = elem;
  return 0;
}