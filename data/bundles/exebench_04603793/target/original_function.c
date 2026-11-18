void itoa(unsigned long i, char *b)
{
 unsigned long shifter = i;
 char *p = b;
 do {
  ++p;
  shifter = shifter/10;
 } while (shifter);
 *p = '\0';
 do {
  *--p = '0' + i%10;
  i = i/10;
 } while (i);
}