void __cdecl file_perms_get(const unsigned __int8 *path, int *p_group, int *p_mode)
{
  stat stb; // [rsp+8h] [rbp-A8h] BYREF
  int *p_modea; // [rsp+98h] [rbp-18h]
  int *p_groupa; // [rsp+A0h] [rbp-10h]
  const unsigned __int8 *patha; // [rsp+A8h] [rbp-8h]

  patha = path;
  p_groupa = p_group;
  p_modea = p_mode;
  if ( *p_group )
    *p_groupa = 0;
  if ( *p_modea )
    *p_modea = 0;
  if ( stat((const char *)patha, &stb) >= 0 )
  {
    if ( p_groupa )
      *p_groupa = stb.st_gid;
    if ( p_modea )
      *p_modea = stb.st_mode & 0xFFF;
  }
}