char *get_dec(char *s, int *val)
{
 int k;

 if (*s >= '0' && *s <= '9') {
  k = 0;
  while (1) {
   if (*s < '0' || *s > '9')
    break;
   k = k * 10 + *s++ - '0';
  }
  *val = k;
 } else
  *val = 0;
 return s;
}