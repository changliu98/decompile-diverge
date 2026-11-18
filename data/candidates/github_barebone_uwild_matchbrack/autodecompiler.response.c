int matchbrack(char *pat, int c, int f)
{
 int ok, lo, hi, neg = 0;

 if (*pat == '!' || *pat == '^') {
  neg = 1;
  pat++;
 }
 if (*pat == ']') {
  if (c == ']')
   ok = !neg;
  else
   pat++;
 } else if (*pat == '-') {
  if (c == '-')
   ok = !neg;
  else
   pat++;
 } else {
  goto start;
 }
 while (*pat != ']') {
  if (*pat == '-' && pat[1] != ']') {
   pat++;
   lo = *(pat-1);
   hi = utf8get(&pat);
   if ((lo <= c && c <= hi) ||
       (lo <= f && f <= hi))
    ok = !neg;
   else
    continue;
  } else {
   int d = utf8get(&pat);
   if (d == c || d == f)
    ok = !neg;
   else
    continue;
  }
 start:
  ;
 }
 ok = neg;
 return ok & 1;
}