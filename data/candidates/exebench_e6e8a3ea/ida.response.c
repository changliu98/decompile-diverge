int __cdecl last_slash(const char *path, int *number_found, int *path_size)
{
  bool v4; // [rsp+1h] [rbp-25h]
  int lasti; // [rsp+2h] [rbp-24h]
  int found; // [rsp+6h] [rbp-20h]
  int i; // [rsp+Ah] [rbp-1Ch]

  found = 0;
  lasti = 0;
  for ( i = 0; ; ++i )
  {
    v4 = 0;
    if ( path[i] )
      v4 = i < 256;
    if ( !v4 )
      break;
    if ( path[i] == 47 )
    {
      ++found;
      lasti = i;
    }
  }
  *number_found = found;
  *path_size = i;
  return lasti;
}