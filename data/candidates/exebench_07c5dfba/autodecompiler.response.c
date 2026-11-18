void _itoa_dec(unsigned int n, char *s)
{
 unsigned int i;
 for(i = 0; ; i++) {
  if(i >= 10 + 1) break;
  if(n || i) s[10 - 1 - i] = "0123456789"[n % 10];
  else s[10 - 1 - i] = ' ';
  n /= 10;
 }
}