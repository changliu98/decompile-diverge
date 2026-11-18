static void
basename_discriminant(char *name, long *hash, long *len)
{
 char *p;

 p = strrchr(name, '/');
 if (!p)
  p = name;
 else
  p++;
 *len = 0;
 *hash = 0;
 while (*p) {
  *hash *= 33;
  *hash += *p++;
  (*len)++;
 }
}