
char *itoa(long n, char *str, long radix){
 char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 char *p = str;
 char *head = str;

 if (! p || radix < 2 || radix > 36){
  return p;
 }

 if (radix != 10 && n < 0){
  return p;
 }
 if (n == 0){
  *p ++ = '0';
  *p = 0;
  return p;
 }
 if (radix == 10 && n < 0){
  *p ++ = '-';
  n = -n;
 }
 while (n){
  *p ++ = digit[n % radix];
  n /= radix;
 }
 *p = 0;


 for (--p; head < p; ++head, --p){
  char temp = *head;
  *head = *p;
  *p = temp;
 }
 return str;
}
