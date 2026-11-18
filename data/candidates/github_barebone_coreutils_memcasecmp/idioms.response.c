int memcasecmp(char *s1, char *s2)
{
  unsigned long i;
  for (i = 0; i < strlen(s1); i++)
    if (toupper(s1[i]) != toupper(s2[i]))
      return s1[i] - s2[i];
  return 0;
}