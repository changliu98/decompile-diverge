int func0(char *s)
{
 int l = 0;
 while (*s != '\0') {
  l++;
  *s++;
 }
 return l;
}