int __cdecl last_slash(const char *path, int *number_found, int *path_size)
{
  int found = 0;
  int lasti = 0;
  int i = 0;

  for ( ; path[i] && i < 256; ++i )
  {
    if ( path[i] == '/' )
    {
      ++found;
      lasti = i;
    }
  }
  
  *number_found = found;
  *path_size = i;
  
  return lasti;
}