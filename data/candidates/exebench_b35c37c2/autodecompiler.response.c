void itox(short int n, char * s) {
 unsigned short int t, i, j;
 char tmp[16];

 if(n == 0) {
  s[0] = '0';
  s[1] = '\0';
  return;
 }

 for(i = 0; n != 0; ++i) {
  t = n % 16;

  if(t < 11)
   tmp[i] = t + '0';
  else
   tmp[i] = t + 'a' - 10;

  n /= 16;
 }

 for(j = 0; i > 0; --i, ++j)
  s[j] = tmp[i-1];
 s[j] = '\0';
}