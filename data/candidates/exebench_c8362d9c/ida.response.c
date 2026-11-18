char *__cdecl parse_fmt(char *fmt, int *type, int *size)
{
  int v4; // [rsp+0h] [rbp-30h]
  bool v5; // [rsp+7h] [rbp-29h]
  char *fmta; // [rsp+20h] [rbp-10h]

  fmta = fmt;
  do
  {
    while ( 1 )
    {
      v5 = 0;
      if ( *fmta )
        v5 = *fmta != 37;
      if ( !v5 )
        break;
      ++fmta;
    }
    if ( *fmta == 37 )
    {
      v4 = fmta[1];
      if ( v4 == 37 )
      {
        *size = (_DWORD)fmta - (_DWORD)fmt + 1;
        *type = -1;
        return fmta + 2;
      }
      if ( v4 == 118 )
      {
        *type = 15;
        *size = (_DWORD)fmta - (_DWORD)fmt;
        return fmta + 2;
      }
    }
  }
  while ( *fmta );
  *type = -1;
  *size = (_DWORD)fmta - (_DWORD)fmt;
  return fmta;
}