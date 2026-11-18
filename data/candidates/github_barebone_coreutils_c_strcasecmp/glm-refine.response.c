int __cdecl c_strcasecmp(const char *s1, const char *s2)
{
  const unsigned __int8 *p1 = (const unsigned __int8 *)s1;
  const unsigned __int8 *p2 = (const unsigned __int8 *)s2;

  // If both pointers point to the same memory address, they are identical
  if (s1 == s2)
    return 0;

  while (1)
  {
    unsigned __int8 c1 = c_tolower(*p1);
    unsigned __int8 c2 = c_tolower(*p2);

    // Stop if we reach the end of the string, or if the characters don't match
    if (!c1 || c1 != c2)
      break;

    ++p1;
    ++p2;
  }

  // Return the difference between the last compared characters
  return c1 - c2;
}