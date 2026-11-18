char *
vips_utf8_strcasestr (const char *haystack_start, const char *needle_start,
                       int len_bytes)
{
  const char *haystack;
  const char *needle;
  int needle_len;
  int needle_len_bytes;
  int i;

  needle_len = g_utf8_strlen (needle_start, -1);
  needle_len_bytes = strlen (needle_start);

  for (haystack = haystack_start;
       haystack - haystack_start <= len_bytes - needle_len_bytes;
       haystack = g_utf8_find_next_char (haystack, NULL))
    {
      for (needle = needle_start, i = 0; i < needle_len;
           needle = g_utf8_find_next_char (needle, NULL), i++)
        {
          gunichar haystack_char =
            g_utf8_get_char_validated (haystack,
                                       haystack_start + len_bytes - haystack);
          gunichar needle_char = g_utf8_get_char_validated (needle, -1);

          if (haystack_char == (gunichar) -1 ||
              haystack_char == (gunichar) -2 ||
              needle_char == (gunichar) -1 ||
              needle_char == (gunichar) -2)
            return NULL;

          if (haystack_char == 0)
            return NULL;

          haystack_char = g_unichar_tolower (haystack_char);
          needle_char = g_unichar_tolower (needle_char);

          if (haystack_char != needle_char)
            break;

          haystack = g_utf8_find_next_char (haystack,
                                            haystack_start + len_bytes);
        }

      if (i == needle_len)
        return (char *) haystack;
    }

  return NULL;
}