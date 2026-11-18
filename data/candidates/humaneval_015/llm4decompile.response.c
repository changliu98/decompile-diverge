char *func0(int n)
{
 int i;
 int len = 2;
 char *str;
 char *p;

 for (i = 1; i <= n; i++)
  len += snprintf(NULL, 0, " %d", i);

 str = malloc((size_t)len);
 if (str == NULL)
  return NULL;

 p = str;
 p += sprintf(p, "0");
 for (i = 1; i <= n; i++)
  p += sprintf(p, " %d", i);

 return str;
}