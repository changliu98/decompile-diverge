char *__cdecl char_replace(char *str, char o, char n)
{
  char *v3; // rax
  const char *p; // [rsp+0h] [rbp-20h]
  char *pa; // [rsp+0h] [rbp-20h]

  if ( !str || !*str )
    return str;
  p = str;
  while ( 1 )
  {
    pa = strchr(p, o);
    if ( !pa )
      break;
    v3 = pa;
    p = pa + 1;
    *v3 = n;
  }
  return str;
}