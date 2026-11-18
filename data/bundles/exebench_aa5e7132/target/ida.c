void __cdecl GetWord(char *out, const char *in, int max)
{
  const char *v3; // rax
  char v4; // cl
  char *v5; // rax
  bool v6; // [rsp+0h] [rbp-1Ah]
  bool v7; // [rsp+1h] [rbp-19h]
  int count; // [rsp+2h] [rbp-18h]

  count = 0;
  while ( 1 )
  {
    v7 = 0;
    if ( *in <= 32 )
      v7 = *in > 0;
    if ( !v7 )
      break;
    ++in;
  }
  while ( 1 )
  {
    if ( *in > 32 || (v6 = 0, *in < 0) )
      v6 = count < max - 1;
    if ( !v6 )
      break;
    v3 = in++;
    v4 = *v3;
    v5 = out++;
    *v5 = v4;
    ++count;
  }
  *out = 0;
}