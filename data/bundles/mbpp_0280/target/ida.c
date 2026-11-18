bool __cdecl func0(int *dlist, int size, int item, int *pos)
{
  char v5; // [rsp+0h] [rbp-1Ah]
  char found; // [rsp+1h] [rbp-19h]

  *pos = 0;
  found = 0;
  while ( 1 )
  {
    v5 = 0;
    if ( *pos < size )
      v5 = ~found;
    if ( (v5 & 1) == 0 )
      break;
    if ( dlist[*pos] == item )
      found = 1;
    else
      ++*pos;
  }
  return found;
}