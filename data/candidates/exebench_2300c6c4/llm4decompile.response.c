char *strtoupper(char *s)
{
 int i;
 for (i = 0; i < 8; i++)
  s[i] = (s[i] >= 'a' && s[i] <= 'z') ? s[i] - ('a' - 'A') : s[i];
 return s;
}