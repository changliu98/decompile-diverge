void string_reverse(char *str)
{
  char *p1; char *p2; char tmp;
  p1 = p2 = str;
  while (*p2 != '\0')
    p2++;
  while (p1 < p2) {
    tmp = *p1;
    *p1 = *(--p2);
    *p2 = tmp;
    p1++;
  }
}