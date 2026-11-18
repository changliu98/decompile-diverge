char *itoa(long value, char *str, long radix)
{
  char *p = str;
  char *head = str;
  char *end;
  char *table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char temp;
  long v = value;
  long r = radix;
  if (str == ((void *)0) || r < 2 || r > 36)
    return str;
  if (r != 10 && v < 0)
    return str;
  if (v == 0)
  {
    p = str + 1;
    *str = '0';
    *p = '\0';
    return p;
  }
  if (r == 10 && v < 0)
  {
    p = str + 1;
    *str = '-';
    v = -v;
  }
  while (v > 0)
  {
    *p++ = table[v % r];
    v /= r;
  }
  *p = '\0';
  end = p - 1;
  while (head < end)
  {
    temp = *head;
    *head = *end;
    *end = temp;
    head++;
    end--;
  }
  return str;
}