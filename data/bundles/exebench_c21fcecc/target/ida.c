int __cdecl StrSafeCopy(char *dst, const char *src, int size)
{
  const char *v3; // rax
  char *v4; // rcx
  const char *v5; // rax
  int n; // [rsp+0h] [rbp-2Ch]
  const char *s; // [rsp+4h] [rbp-28h]

  s = src;
  n = size;
  if ( size )
  {
    n = size - 1;
    if ( size != 1 )
    {
      do
      {
        v3 = s++;
        LOBYTE(v3) = *v3;
        v4 = dst++;
        *v4 = (char)v3;
        if ( !(_BYTE)v3 )
          break;
        --n;
      }
      while ( n );
    }
  }
  if ( !n )
  {
    if ( size )
      *dst = 0;
    do
      v5 = s++;
    while ( *v5 );
  }
  return (_DWORD)s - (_DWORD)src - 1;
}