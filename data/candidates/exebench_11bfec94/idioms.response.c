void to_hex(long i, char *s)
{
  char *hex = "0123456789ABCDEF";
  int j;
  for (j = 3; j >= 0; j--)
  {
    s[j] = hex[i % 16];
    i /= 16;
  }
  s[4] = '\0';
}