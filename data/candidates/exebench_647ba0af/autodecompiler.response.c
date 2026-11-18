char *replace_char(char *s, char old, char new)
{
 char *p = s;
 while ((p = strchr(p, old)))
 {
  p[0] = new;
  p++;
 }
 return s;
}