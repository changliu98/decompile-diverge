int c_strncasecmp (const char *s1, const char *s2, size_t n)
{
  unsigned char c1, c2;

  if (s1 == s2)
    return 0;

  while (n--)
    {
      c1 = c_tolower (*(const unsigned char *) s1++);
      c2 = c_tolower (*(const unsigned char *) s2++);
      if (c1 == '\0' || c1 != c2)
 return c1 - c2;
    }

  return 0;
}