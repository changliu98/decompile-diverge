int __cdecl func0(int *item_list, int size, int item)
{
  int first = 0;
  int last = size - 1;
  int found = 0;

  while (first <= last && found == 0)
  {
    int mid = (last + first) / 2;

    if (item_list[mid] == item)
    {
      found = 1;
    }
    else if (item >= item_list[mid])
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