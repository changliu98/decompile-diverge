void __cdecl func0(char *text)
{
  char *v1; // rax
  char *out; // [rsp+8h] [rbp-18h]
  char *texta; // [rsp+18h] [rbp-8h]

  texta = text;
  out = text;
  while ( *texta )
  {
    if ( !strchr("AEIOUaeiou", *texta) )
    {
      v1 = out++;
      *v1 = *texta;
    }
    ++texta;
  }
  *out = 0;
}