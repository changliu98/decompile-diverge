void __cdecl cwk_path_get_root_windows(const char *path, size_t *length)
{
  bool is_separator; // [rsp+6h] [rbp-1Ah]
  const char *c; // [rsp+8h] [rbp-18h]
  const char *ca; // [rsp+8h] [rbp-18h]
  const char *cb; // [rsp+8h] [rbp-18h]

  *length = 0LL;
  if ( *path )
  {
    if ( cwk_path_is_separator(path) )
    {
      if ( cwk_path_is_separator(path + 1) )
      {
        c = path + 2;
        if ( path[2] == 63 || (is_separator = 0, *c == 46) )
        {
          c = path + 3;
          is_separator = cwk_path_is_separator(path + 3);
        }
        if ( is_separator )
        {
          *length = 4LL;
        }
        else
        {
          for ( ca = cwk_path_find_next_stop(c); cwk_path_is_separator(ca); ++ca )
            ;
          cb = cwk_path_find_next_stop(ca);
          if ( cwk_path_is_separator(cb) )
            ++cb;
          *length = cb - path;
        }
      }
      else
      {
        ++*length;
      }
    }
    else if ( path[1] == 58 )
    {
      *length = 2LL;
      if ( cwk_path_is_separator(path + 2) )
        *length = 3LL;
    }
  }
}