int __cdecl func0(int *item_list, int size, int item)
{
  char v4; // [rsp+1h] [rbp-21h]
  int mid; // [rsp+2h] [rbp-20h]
  int found; // [rsp+6h] [rbp-1Ch]
  int last; // [rsp+Ah] [rbp-18h]
  int first; // [rsp+Eh] [rbp-14h]

  first = 0;
  last = size - 1;
  found = 0;
  while ( 1 )
  {
    v4 = 0;
    if ( first <= last )
      v4 = ~(found != 0);
    if ( (v4 & 1) == 0 )
      break;
    mid = (last + first) / 2;
    if ( item_list[mid] == item )
    {
      found = 1;
    }
    else if ( item >= item_list[mid] )
    {
      first = mid + 1;
    }
    else
    {
      last = mid - 1;
    }
  }
  return found;
}