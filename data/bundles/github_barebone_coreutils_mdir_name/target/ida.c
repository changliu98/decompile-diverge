char *__cdecl mdir_name(const char *file)
{
  char *dir; // [rsp+8h] [rbp-28h]
  size_t length; // [rsp+18h] [rbp-18h]

  length = dir_len(file);
  dir = (char *)malloc((length == 0) + length + 1);
  if ( !dir )
    return 0LL;
  memcpy(dir, file, length);
  if ( !length )
  {
    length = 1LL;
    *dir = 46;
  }
  dir[length] = 0;
  return dir;
}