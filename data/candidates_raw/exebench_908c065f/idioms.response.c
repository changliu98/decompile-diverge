void reverse(char *str)
{
  char *p1 = str; char *p2 = str; char tmp;
  while (*p1)
    p1++;
  p1--;
  while (p2 < p1)
  {
    tmp = *p2;
    *p2 = *p1;
    *p1 = tmp;
    p2++;
    p1--;
  }
}