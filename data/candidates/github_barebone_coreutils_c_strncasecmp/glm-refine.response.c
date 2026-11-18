int __cdecl c_strncasecmp(const char *s1, const char *s2, size_t n)
{
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

  // If the pointers are identical, or the length to compare is zero
  if (p1 == p2 || n == 0)
    return 0;

  for (; n > 0; n--, p1++, p2++)
  {
    unsigned char c1 = c_tolower(*p1);
    unsigned char c2 = c_tolower(*p2);

    // Stop if we reached the end of the string, or if characters don't match
    if (c1 == 0 || c1 != c2)
      return c1 - c2;
  }

  // If we exhaust the loop (compared exactly 'n' characters successfully), 
  // the last characters compared were equal, so the difference is 0.
  return 0;
}