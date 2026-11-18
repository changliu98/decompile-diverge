char *func0(int n)
{
  int len = 2;
  int i;
  for (i = 1; i <= n; i++)
    len += snprintf(((void *)0), 0, " %d", i);
  char *out = (char *)malloc(len);
  if (out == ((void *)0))
    return ((void *)0);
  char *p = out + sprintf(out, "0");
  for (i = 1; i <= n; i++)
    p += sprintf(p, " %d", i);
  return out;
}