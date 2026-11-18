const char *__cdecl vips_utf8_strcasestr(const char *haystack_start, const char *needle_start, int len_bytes)
{
  int needle_len = g_utf8_strlen(needle_start, -1LL);
  int needle_len_bytes = strlen(needle_start);
  const char *haystack_end = &haystack_start[len_bytes];

  for (const char *haystack = haystack_start;
       haystack - haystack_start <= len_bytes - needle_len_bytes;
       haystack = g_utf8_find_next_char(haystack, NULL))
  {
    const char *haystack_char = haystack;
    const char *needle_char = needle_start;
    int i = 0;

    for (; i < needle_len; ++i)
    {
      gunichar a = g_utf8_get_char_validated(haystack_char, haystack_end - haystack_char);
      gunichar b = g_utf8_get_char_validated(needle_char, -1LL);

      // Check for invalid UTF-8 sequences or premature null-terminators
      if (a == (gunichar)-1 || a == (gunichar)-2 || b >= 0xFFFFFFFE || !a)
        return NULL;

      // Case-insensitive comparison
      if (g_unichar_tolower(a) != g_unichar_tolower(b))
        break;

      haystack_char = g_utf8_find_next_char(haystack_char, haystack_end);
      needle_char = g_utf8_find_next_char(needle_char, NULL);
    }

    // If the inner loop completed without breaking, the needle was found
    if (i == needle_len)
      return haystack;
  }

  return NULL;
}