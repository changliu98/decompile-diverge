void stress_chop(char *str, const char ch)
{
 char *p;

 p = strchr(str, ch);
 if (p)
  *p = '\0';
}