void __cdecl reverse(char *s)
{
  char tmp;
  unsigned int len;
  unsigned int i;

  // Calculate the length of the string
  for (len = 0; s[len]; ++len)
    ;

  // Swap characters from the outside in
  for (i = 0; i < len / 2; ++i)
  {
    tmp = s[i];
    s[i] = s[len - (i + 1)];
    s[len - (i + 1)] = tmp;
  }
}