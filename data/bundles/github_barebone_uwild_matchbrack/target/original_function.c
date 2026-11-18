static bool
matchbrack(const char *pat, int sc, int folded)
{
  int pc;
  bool compl = false;
  if (*pat == '!' || *pat == '^') {
    compl = true;
    pat++;
  }
  if (*pat == ']') {
    if (sc == ']')
      return !compl;
    pat++;
  }
  else if (*pat == '-') {
    if (sc == '-')
      return !compl;
    pat++;
  }
  for (pc = pat[-1]; *pat != ']'; ) {
    if (pat[0] == '-' && pat[1] != ']') {
      int lo, hi;
      pat++; /* skip the dash */
      lo=pc, hi=utf8get(&pat);
      if ((lo <= sc && sc <= hi) ||
          (lo <= folded && folded <= hi))
        return !compl;
    }
    else {
      pc = utf8get(&pat);
      if (pc == sc || pc == folded)
        return !compl;
    }
  }
  return compl;
}