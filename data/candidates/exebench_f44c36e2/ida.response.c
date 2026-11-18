void __cdecl strcpymax(char *dest, const char *src, int n)
{
  const char *v3; // rax
  char v4; // cl
  char *v5; // rax
  bool v6; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  if ( n )
  {
    for ( i = 0; ; ++i )
    {
      v6 = 0;
      if ( *src )
        v6 = i < n - 1;
      if ( !v6 )
        break;
      v3 = src++;
      v4 = *v3;
      v5 = dest++;
      *v5 = v4;
    }
  }
  *dest = 0;
}