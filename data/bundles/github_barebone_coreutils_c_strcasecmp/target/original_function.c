int
c_strcasecmp (const char *s1, const char *s2)
{
  register const unsigned char *p1 = (const unsigned char *) s1;
  register const unsigned char *p2 = (const unsigned char *) s2;

  if (p1 == p2)
    return 0;

  for (;; p1++, p2++)
    {
      unsigned char c1 = c_tolower (*p1);
      unsigned char c2 = c_tolower (*p2);

      if (c1 == '\0' || c1 != c2)
        {
          if (UCHAR_MAX <= INT_MAX)
            return c1 - c2;
          else
            /* On machines where 'char' and 'int' are types of the same size,
               the difference of two 'unsigned char' values - including the
               sign bit - doesn't fit in an 'int'.  */
            return _GL_CMP (c1, c2);
        }
    }
}