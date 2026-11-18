int __cdecl toml_value_string(toml_unparsed_t src, char **ret, int *len)
{
  char *v3; // rcx
  int v4; // eax
  int srclen; // [rsp+0h] [rbp-40h]
  int qchar; // [rsp+4h] [rbp-3Ch]
  const char *sq; // [rsp+8h] [rbp-38h]
  toml_unparsed_t sp_0; // [rsp+10h] [rbp-30h]
  bool multiline; // [rsp+1Fh] [rbp-21h]

  multiline = 0;
  *ret = 0LL;
  if ( !src )
    return -1;
  qchar = *src;
  srclen = strlen(src);
  if ( qchar != 39 && qchar != 34 )
    return -1;
  if ( qchar == src[1] && qchar == src[2] )
  {
    multiline = 1;
    sp_0 = src + 3;
    sq = &src[srclen - 3];
    if ( src + 3 > sq || *sq != qchar || sq[1] != qchar || sq[2] != qchar )
      return -1;
    if ( *sp_0 == 10 )
    {
      sp_0 = src + 4;
    }
    else if ( *sp_0 == 13 && src[4] == 10 )
    {
      sp_0 = src + 5;
    }
  }
  else
  {
    sp_0 = src + 1;
    sq = &src[srclen - 1];
    if ( src + 1 > sq || *sq != qchar )
      return -1;
  }
  if ( qchar == 39 )
    v3 = norm_lit_str(sp_0, (int)sq - (int)sp_0, len, multiline, 0LL, 0);
  else
    v3 = norm_basic_str(sp_0, (int)sq - (int)sp_0, len, multiline, 0LL, 0);
  *ret = v3;
  v4 = -1;
  if ( *ret )
    return 0;
  return v4;
}