const char *__cdecl vips_utf8_strcasestr(const char *haystack_start, const char *needle_start, int len_bytes)
{
  gunichar v4; // [rsp+0h] [rbp-50h]
  gunichar b; // [rsp+4h] [rbp-4Ch]
  gunichar a; // [rsp+8h] [rbp-48h]
  int i; // [rsp+Ch] [rbp-44h]
  const char *haystack_char; // [rsp+10h] [rbp-40h]
  const char *needle_char; // [rsp+18h] [rbp-38h]
  const char *haystack; // [rsp+20h] [rbp-30h]
  int needle_len_bytes; // [rsp+2Ch] [rbp-24h]
  int needle_len; // [rsp+30h] [rbp-20h]

  needle_len = g_utf8_strlen(needle_start, -1LL);
  needle_len_bytes = strlen(needle_start);
  for ( haystack = haystack_start;
        haystack - haystack_start <= len_bytes - needle_len_bytes;
        haystack = g_utf8_find_next_char(haystack, 0LL) )
  {
    haystack_char = haystack;
    needle_char = needle_start;
    for ( i = 0; i < needle_len; ++i )
    {
      a = g_utf8_get_char_validated(haystack_char, &haystack_start[len_bytes] - haystack);
      b = g_utf8_get_char_validated(needle_char, -1LL);
      if ( a == -1 || a == -2 || b >= 0xFFFFFFFE )
        return 0LL;
      if ( !a )
        return 0LL;
      v4 = g_unichar_tolower(a);
      if ( v4 != g_unichar_tolower(b) )
        break;
      haystack_char = g_utf8_find_next_char(haystack_char, &haystack_start[len_bytes]);
      needle_char = g_utf8_find_next_char(needle_char, 0LL);
    }
    if ( i == needle_len )
      return haystack;
  }
  return 0LL;
}