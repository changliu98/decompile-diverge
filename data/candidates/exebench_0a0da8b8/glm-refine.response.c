void __cdecl string_reverse(char *s)
{
  char c;
  char *t;
  char *sa = s;

  // Find the end of the string (t points to the null terminator)
  for (t = s; *t; ++t)
    ;

  // Swap characters from the outside in
  while (sa < t)
  {
    c = *sa;
    *sa = *(t - 1);
    *t = c;
    
    sa++;
    t--;
  }
}