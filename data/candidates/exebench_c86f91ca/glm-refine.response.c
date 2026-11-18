void __cdecl remove_dupc2(char *str)
{
  int i, j, k;
  int first_dup;
  int write_idx;

  // Phase 1: Mark duplicate characters with -1 (0xFF)
  for ( i = 0; str[i]; ++i )
  {
    if ( str[i] != -1 )
    {
      for ( j = i + 1; str[j]; ++j )
      {
        if ( str[i] == str[j] )
          str[j] = -1;
      }
    }
  }

  // Phase 2: Find the index of the first marked duplicate character
  first_dup = -1;
  for ( k = 0; str[k]; ++k )
  {
    if ( str[k] == -1 )
    {
      first_dup = k;
      break;
    }
  }

  // Phase 3: Determine the starting point for the compaction write phase
  // If no duplicates were found, `first_dup` remains -1.
  // The original code sets `write_idx` to `i - 1` (the last valid string index) 
  // when `str[k]` is 0, which safely falls back to the end of the string.
  if ( first_dup != -1 )
    write_idx = first_dup;
  else
    write_idx = i - 1;

  // Phase 4: Compact the string by overwriting marked (-1) characters
  for ( k = write_idx + 1; str[k]; ++k )
  {
    if ( str[k] != -1 )
    {
      str[write_idx] = str[k];
      ++write_idx;
    }
  }

  // Phase 5: Null-terminate the compacted string
  str[write_idx] = str[k];
}