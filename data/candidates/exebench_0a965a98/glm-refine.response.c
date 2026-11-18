int __cdecl new_strcpy(char *s, char *t, int num)
{
  int i;

  for (i = 0; i < num && t[i] != '\0'; ++i)
  {
    s[i] = t[i];
  }
  
  s[i] = '\0';
  return 0;
}