char **__cdecl func0(char **lst, int lst_size, int *return_size)
{
  char **out;
  size_t len_j;
  size_t len_j1;
  char *temp;
  int j;
  int i;
  int ia;
  int ib;

  *return_size = 0;
  
  // Filter strings with even lengths
  for ( i = 0; i < lst_size; ++i )
  {
    if ( (strlen(lst[i]) & 1) == 0 )
      lst[(*return_size)++] = lst[i];
  }
  
  // Sort the filtered strings by length, then lexicographically
  for ( ia = 0; ia < *return_size - 1; ++ia )
  {
    for ( j = 0; j < *return_size - ia - 1; ++j )
    {
      len_j = strlen(lst[j]);
      len_j1 = strlen(lst[j + 1]);
      if ( len_j > len_j1 || (len_j == len_j1 && strcmp(lst[j], lst[j + 1]) > 0) )
      {
        temp = lst[j];
        lst[j] = lst[j + 1];
        lst[j + 1] = temp;
      }
    }
  }
  
  // Allocate a new array and copy the sorted strings
  out = (char **)malloc(8LL * *return_size);
  for ( ib = 0; ib < *return_size; ++ib )
    out[ib] = lst[ib];
    
  return out;
}