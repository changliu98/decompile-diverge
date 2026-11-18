static char *
utf8_strcasestr (const char *haystack, const char *needle, int len)
{
  int needle_len = g_utf8_strlen (needle, -1);
  int needle_len_bytes = strlen (needle);
  char *ret;
  char *haystack_ptr;

  haystack_ptr = (char *) haystack;

  while (1)
    {
      if (haystack_ptr - haystack > len - needle_len_bytes)
        {
          ret = NULL;
          break;
        }

      char *haystack_char = haystack_ptr;
      char *needle_char = (char *) needle;
      int i = 0;

      while (1)
        {
          if (i >= needle_len)
            break;

          int u_haystack = g_utf8_get_char_validated (haystack_char,
                                                      haystack + len - haystack_ptr);
          int u_needle = g_utf8_get_char_validated (needle_char, -1);

          if (u_haystack == -1 || u_haystack == -2 ||
              u_needle == -1 || u_needle == -2)
            {
              ret = NULL;
              goto done;
            }
          else if (u_haystack == 0)
            {
              ret = NULL;
              goto done;
            }

          if (g_unichar_tolower (u_haystack) != g_unichar_tolower (u_needle))
            break;

          haystack_char = g_utf8_find_next_char (haystack_char,
                                                 haystack + len);
          needle_char = g_utf8_find_next_char (needle_char, NULL);

          i++;
        }

      if (i == needle_len)
        {
          ret = haystack_ptr;
          goto done;
        }

      while (haystack_ptr - haystack < len)
        {
          haystack_ptr = g_utf8_find_next_char (haystack_ptr, NULL);
        }
    }

done:
  return ret;
}