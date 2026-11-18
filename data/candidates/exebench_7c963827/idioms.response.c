static unsigned long scan_ulong(char *str, unsigned long *res)
{
  unsigned int digit;
  unsigned long long val = 0;
  unsigned long i = 0;
  while ((digit = str[i] - '0') < 10) {
    val = (val * 10) + digit;
    ++i;
  }
  *res = (unsigned long)val;
  return i;
}