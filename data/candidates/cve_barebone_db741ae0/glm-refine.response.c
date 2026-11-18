int __cdecl burl_normalize_2F_to_slash_fix(buffer *b, int qs, int i)
{
  char *s = b->ptr;
  int blen = buffer_string_length(b);
  int end = (qs >= 0) ? qs : blen;
  int j = i;

  // Decode "%2F" to "/" in-place up to the query string or end of string
  while (i < end)
  {
    s[j] = s[i];
    if (s[i] == '%' && s[i + 1] == '2' && s[i + 2] == 'F')
    {
      s[j] = '/';
      i += 2;
    }
    ++i;
    ++j;
  }

  // If a query string exists, shift it down to append right after the decoded path
  if (qs >= 0)
  {
    int qs_len = blen - qs;
    memmove(&s[j], &s[qs], qs_len);
    j += qs_len;
  }

  buffer_string_set_length(b, j);
  return qs;
}