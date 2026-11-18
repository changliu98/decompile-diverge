bool __cdecl pattern_match_custom_class(char c, const char *pattern_ptr, const char *class_end)
{
  bool ret; // [rsp+7h] [rbp-19h]
  const char *pattern_ptra; // [rsp+10h] [rbp-10h]

  pattern_ptra = pattern_ptr;
  ret = 1;
  if ( pattern_ptr[1] == 94 )
  {
    ret = 0;
    pattern_ptra = pattern_ptr + 1;
  }
  while ( ++pattern_ptra < class_end )
  {
    if ( *pattern_ptra == 37 )
    {
      if ( pattern_match_class(c, *++pattern_ptra) )
        return ret;
    }
    else if ( pattern_ptra[1] == 45 && pattern_ptra + 2 < class_end )
    {
      pattern_ptra += 2;
      if ( *(pattern_ptra - 2) <= c && c <= *pattern_ptra )
        return ret;
    }
    else if ( *pattern_ptra == c )
    {
      return ret;
    }
  }
  return !ret;
}