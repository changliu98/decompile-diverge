bool __cdecl func0(int *dlist, int size, int item, int *pos)
{
  bool found = false;

  *pos = 0;
  while (*pos < size && !found)
  {
    if (dlist[*pos] == item)
      found = true;
    else
      ++*pos;
  }
  
  return found;
}