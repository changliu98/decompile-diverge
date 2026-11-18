void __cdecl Q_ParseNewlines(char *dest, const char *src, int destsize)
{
  const char *v3; // rax
  char *v4; // rax
  char v5; // [rsp+0h] [rbp-1Ch]
  bool v6; // [rsp+7h] [rbp-15h]

  while ( 1 )
  {
    v6 = 0;
    if ( *src )
      v6 = destsize > 1;
    if ( !v6 )
      break;
    if ( *src == 92 && (v3 = src, ++src, v3[1] == 110) )
      v5 = 10;
    else
      v5 = *src;
    v4 = dest++;
    *v4 = v5;
    ++src;
    --destsize;
  }
  *dest = 0;
}