int matchbrack(const char *pat, int sc, int folded)
{
 int sign = 0;
 int match = 0;
 int pc;
 int hi;
 int lo;

 if (*pat == '!' || *pat == '^')
  sign = 1, pat++;
 if (*pat == ']') {
  if (sc == ']')
   return !sign;
  pat++;
 } else if (*pat == '-') {
  if (sc == '-')
   return !sign;
  pat++;
 }
 pc = (unsigned char)*(pat-1);
 while (*pat != ']') {
  if (*pat == '-' && pat[1] != ']') {
   pat++;
   hi = utf8get(&pat);
   if (sc >= pc && sc <= hi)
    return !sign;
   if (folded >= pc && folded <= hi)
    return !sign;
   continue;
  }
  pc = utf8get(&pat);
  if (pc == sc || pc == folded)
   return !sign;
 }
 return sign;
}