int __cdecl func0(const int *tup, int tup_size, const int *lst, int lst_size)
{
  int count = 0;

  for (int i = 0; i < tup_size; ++i) 
  {
    for (int j = 0; j < lst_size; ++j) 
    {
      if (tup[i] == lst[j]) 
      {
        ++count;
        break; // Stop checking the rest of `lst` for the current `tup[i]`
      }
    }
  }
  
  return count;
}