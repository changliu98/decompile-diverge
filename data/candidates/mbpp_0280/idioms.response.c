int func0(int *dlist, int size, int item, int *pos)
{
  int i = *pos = 0;
  int found = 0;
  int mask = 0;
  while ( (mask = (i < size) ? ~found : 0) & 1 )
  {
    if ( dlist[i] == item )
      found = 1;
    else
      ++i;
  }
  return found;
}