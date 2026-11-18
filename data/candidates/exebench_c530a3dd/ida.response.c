unsigned int __cdecl str_copy(char *s, const char *t)
{
  char v2; // al
  char v3; // al
  char v4; // al
  char v5; // al
  int len; // [rsp+0h] [rbp-1Ch]
  int lena; // [rsp+0h] [rbp-1Ch]
  int lenb; // [rsp+0h] [rbp-1Ch]
  int lenc; // [rsp+0h] [rbp-1Ch]
  const char *tb; // [rsp+4h] [rbp-18h]
  const char *tc; // [rsp+4h] [rbp-18h]
  const char *td; // [rsp+4h] [rbp-18h]
  char *sb; // [rsp+Ch] [rbp-10h]
  char *sc; // [rsp+Ch] [rbp-10h]
  char *sd; // [rsp+Ch] [rbp-10h]

  for ( len = 0; ; len = lenc + 1 )
  {
    v2 = *t;
    *s = *t;
    if ( !v2 )
      return len;
    sb = s + 1;
    tb = t + 1;
    lena = len + 1;
    v3 = *tb;
    *sb = *tb;
    if ( !v3 )
      return lena;
    sc = sb + 1;
    tc = tb + 1;
    lenb = lena + 1;
    v4 = *tc;
    *sc = *tc;
    if ( !v4 )
      return lenb;
    sd = sc + 1;
    td = tc + 1;
    lenc = lenb + 1;
    v5 = *td;
    *sd = *td;
    if ( !v5 )
      break;
    s = sd + 1;
    t = td + 1;
  }
  return lenc;
}