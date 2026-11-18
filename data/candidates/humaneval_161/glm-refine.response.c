char *__cdecl func0(char *s)
{
  char temp;
  int i;
  int length = strlen(s);
  int nletter = 0;

  for (i = 0; i < length; ++i)
  {
    if (isalpha((unsigned char)s[i]))
    {
      if (isupper((unsigned char)s[i]))
      {
        s[i] = tolower((unsigned char)s[i]);
      }
      else if (islower((unsigned char)s[i]))
      {
        s[i] = toupper((unsigned char)s[i]);
      }
    }
    else
    {
      ++nletter;
    }
  }

  // If the string contains no letters at all, reverse it
  if (nletter == length)
  {
    for (i = 0; i < length / 2; ++i)
    {
      temp = s[i];
      s[i] = s[length - i - 1];
      s[length - i - 1] = temp;
    }
  }

  return s;
}