bool __cdecl matchbrack(const char *pat, int sc, int folded)
{
  int hi;
  bool is_negated;
  int pc;
  const char *p;

  p = pat;
  is_negated = false;

  // Check for negation character: '!' (33) or '^' (94)
  if (*p == '!' || *p == '^')
  {
    is_negated = true;
    ++p;
  }

  // Handle special characters allowed as the first character in the bracket
  if (*p == ']')
  {
    if (sc == ']')
      return !is_negated;
    ++p;
  }
  else if (*p == '-')
  {
    if (sc == '-')
      return !is_negated;
    ++p;
  }

  // pc holds the last character read, initialized to the char before the current position
  pc = *(p - 1);

  // Iterate through the bracket expression until the closing ']'
  while (*p != ']')
  {
    // If it's not a range (either no '-' or '-' is the last character)
    if (*p != '-' || p[1] == ']')
    {
      pc = utf8get(&p);
      if (pc == sc || pc == folded)
        return !is_negated;
    }
    else // It's a character range (e.g., a-z)
    {
      ++p; // Skip the '-'
      hi = utf8get(&p);
      
      // Check if sc or folded falls within the range [pc, hi]
      if ((pc <= sc && sc <= hi) || (pc <= folded && folded <= hi))
        return !is_negated;
    }
  }

  // If no match was found, the result is the negation flag
  return is_negated;
}