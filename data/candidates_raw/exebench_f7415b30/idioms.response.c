int sscanf_char(int *dest, char *src, unsigned long n)
{
  if (n == 0 || *src == '\0')
    return 0;
  *dest = *src;
  return 1;
}