void itoa(char *buf, int base, long number)
{
 char *p = buf;
 char *p1, *p2;
 unsigned long ud = 0;
 int divisor = 10;

 if (base == 'd' && number < 0) {
  *p++ = '-';
  buf++;
  ud = -number;
 } else if (base == 'x')
  divisor = 16;

 do {
  int remainder = ud % divisor;
  *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
 } while (ud /= divisor);

 *p = 0;

 p1 = buf;
 p2 = p - 1;
 while (p1 < p2) {
  char tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
  p1++;
  p2--;
 }
}