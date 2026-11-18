char *strncpy2(char *target, const char *source, int n)
{
 char *p = target;
 while (n > 0 && *source != '\0') {
  *p++ = *source++;
  n--;
 }
 *p = '\0';
 return target;
}