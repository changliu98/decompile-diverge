void stress_chop(char *s, char c)
{
 char *p = strchr(s, c);
 if (p) *p = '\0';
}