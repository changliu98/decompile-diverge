char **__cdecl func0(char **str_array, int array_size, int target_length, int *out_size)
{
  int i;
  int match_count = 0;

  for ( i = 0; i < array_size; ++i )
  {
    if ( strlen(str_array[i]) == target_length )
    {
      func0_result[match_count++] = str_array[i];
    }
  }
  
  *out_size = match_count;
  return (char **)func0_result;
}