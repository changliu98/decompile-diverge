
static char* _xtoa(unsigned long v,char *string, int r, int is_neg)
{
 char *start = string;
 char buf[33],*p;

 p = buf;

 do {
  *p++ = "0123456789abcdef"[(v % r) & 0xf];
 } while (v /= r);

 if (is_neg) {
  *p++ = '-';
 }

 do {
  *string++ = *--p;
 } while (buf != p);

 *string = '\0';

 return start;
}
