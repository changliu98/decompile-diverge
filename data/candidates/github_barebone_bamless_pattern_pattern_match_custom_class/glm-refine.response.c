bool __cdecl pattern_match_custom_class(char c, const char *pattern_ptr, const char *class_end)
{
  bool negated = false;
  const char *p = pattern_ptr;

  // Check for negation (e.g., [^...])
  if (pattern_ptr[1] == '^')
  {
    negated = true;
    p = pattern_ptr + 1;
  }

  // Iterate through the class pattern (skipping the opening '[')
  while (++p < class_end)
  {
    if (*p == '%')
    {
      // Escaped character class (e.g., %d, %w)
      if (pattern_match_class(c, *++p))
        return negated;
    }
    else if (p[1] == '-' && p + 2 < class_end)
    {
      // Character range (e.g., a-z)
      p += 2;
      if (p[-2] <= c && c <= *p)
        return negated;
    }
    else if (*p == c)
    {
      // Exact character match
      return negated;
    }
  }
  
  // If no match was found, return the inverse of the negation flag
  return !negated;
}