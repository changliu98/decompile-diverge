int my_itoa(char *buf, int i)
{
 char tmp[12];
 char *tp = tmp + sizeof(tmp);
 char *sp;
 unsigned int u;
 unsigned int ui;
 if (i < 0) {
  ui = 0 - i;
 } else {
  ui = i;
 }
 u = ui;
 do {
  *--tp = '0' + u % 10;
  u /= 10;
 } while (u > 0);
 if (i < 0)
  *--tp = '-';
 else
  tp++;
 sp = buf;
 while (tp < tmp + sizeof(tmp))
  *sp++ = *tp++;
 *sp = '\0';
 return sp - buf;
}