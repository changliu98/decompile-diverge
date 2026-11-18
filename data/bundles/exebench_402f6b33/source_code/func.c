#include <stdarg.h>

void itoa(int num, char *str, int base)
{
 int i, sign = num;

 char tmp[16];

 const char *digits = "0123456789ABCDEF";

 if (sign < 0) {
  num = -num;
 }

 i = 0;

 if (num == 0) {
  tmp[i++] = '0';
 } else {
  while (num != 0) {
   tmp[i++] = digits[num % base];
   num /= base;
  }
 }

 if (sign < 0) {
  tmp[i++] = '-';
 }

 while (i--) {
  *str++ = tmp[i];
 }

 *str = '\0';
}
