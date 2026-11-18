bool __cdecl cwk_path_is_string_equal(const char *first, const char *second, size_t first_size, size_t second_size)
{
  int v5; // [rsp+0h] [rbp-30h]
  bool v6; // [rsp+5h] [rbp-2Bh]
  bool v7; // [rsp+6h] [rbp-2Ah]
  size_t first_sizea; // [rsp+10h] [rbp-20h]
  const char *seconda; // [rsp+18h] [rbp-18h]
  const char *firsta; // [rsp+20h] [rbp-10h]

  firsta = first;
  seconda = second;
  first_sizea = first_size;
  if ( first_size == second_size )
  {
    if ( path_style == 1 )
    {
      return strncmp(first, second, first_size) == 0;
    }
    else
    {
      while ( 1 )
      {
        v7 = 0;
        if ( *firsta )
        {
          v7 = 0;
          if ( *seconda )
            v7 = first_sizea != 0;
        }
        if ( !v7 )
          break;
        v6 = 0;
        if ( strchr((&separators)[path_style], *firsta) )
          v6 = strchr((&separators)[path_style], *seconda) != 0LL;
        v5 = tolower(*firsta);
        if ( v5 != tolower(*seconda) && !v6 )
          return 0;
        ++firsta;
        ++seconda;
        --first_sizea;
      }
      return 1;
    }
  }
  else
  {
    return 0;
  }
}