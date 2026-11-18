char *js_itoa(char *buf, unsigned int i)
{
  unsigned int ci = i;
  char *cp = buf;
  char temp[32];
  unsigned int pos = 0;

  while (ci) {
    temp[pos++] = '0' + (ci % 10);
    ci /= 10;
  }

  if (!pos)
    temp[pos++] = '0';

  while (pos--)
    *cp++ = temp[pos];

  *cp = '\0';

  return buf;
}