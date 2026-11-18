char *itoa(int value, char *string, int radix)
{
 char tmp[33];
 char *tp = tmp;
 int i;
 char *sp;

 if (string == ((void *)0))
 {
  string = tp;
 }
 else
 {
  if ((radix < 2) || (radix > 36))
  {
   return tp;
  }
 }

 sp = string;

 if ((radix == 10) && (value < 0))
 {
  *sp++ = '-';
  value = -value;
 }
 else if (value == 0)
 {
  *sp++ = '0';
  *sp = '\0';
  return string;
 }

 while (value != 0)
 {
  i = value % radix;
  *sp++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i];
  value /= radix;
 }

 *sp = '\0';

 while (string < --sp)
 {
  i = *string;
  *string = *sp;
  *sp = i;
 }

 return string;
}