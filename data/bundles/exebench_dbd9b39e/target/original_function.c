static inline void stress_chop(char *str, const char ch)
{
 char *ptr = strchr(str, ch);

 if (ptr)
  *ptr = '\0';
}