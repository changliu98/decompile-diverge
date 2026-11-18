int __cdecl burl_normalize_2F_to_slash_fix(buffer *b, int qs, int i)
{
  int v4; // [rsp+8h] [rbp-28h]
  int j; // [rsp+Ch] [rbp-24h]
  int blen; // [rsp+14h] [rbp-1Ch]
  char *s; // [rsp+18h] [rbp-18h]

  s = b->ptr;
  blen = buffer_string_length(b);
  if ( qs >= 0 )
    v4 = qs;
  else
    v4 = blen;
  j = i;
  while ( i < v4 )
  {
    s[j] = s[i];
    if ( s[i] == 37 && s[i + 1] == 50 && s[i + 2] == 70 )
    {
      s[j] = 47;
      i += 2;
    }
    ++i;
    ++j;
  }
  if ( qs >= 0 )
  {
    memmove(&s[j], &s[qs], blen - qs);
    j += blen - qs;
  }
  buffer_string_set_length(b, j);
  return qs;
}