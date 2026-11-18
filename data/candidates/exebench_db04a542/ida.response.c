char *__cdecl checkpath(char *path, const char *srcpath)
{
  char *v2; // rax
  const char *v3; // rax
  char v4; // cl
  char *v5; // rax
  char *p; // [rsp+0h] [rbp-18h]
  const char *srcpatha; // [rsp+8h] [rbp-10h]

  srcpatha = srcpath;
  p = path;
  if ( path && srcpath )
  {
    while ( *srcpatha )
    {
      if ( *srcpatha == 92 )
      {
        v2 = p++;
        *v2 = 47;
        ++srcpatha;
      }
      else
      {
        v3 = srcpatha++;
        v4 = *v3;
        v5 = p++;
        *v5 = v4;
      }
    }
    *p = *srcpatha;
  }
  return path;
}