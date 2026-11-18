char zhalfstr(char *num){
 char c, n, nn, d;
 int i, j, k, l;
 char last, first, zero;

 c = '0';
 last = '0';
 i = -1;
 zero = 0;
 k = 0;
 while(1){
  if(c == '\0') break;
  n = num[i+1];
  d = ((n-'0')>>1) + '0';
  d += (c-'0')%2 ? 5 : 0;
  num[i+1-k] = d;
  if(d == '0' && !zero) k++;
  else zero = 1;
  if(c != '\0') last = c;
  c = n;
  i++;
 }
 if(i == k){
  num[0] = '0';
  num[1] = '\0';
 }
 else num[i-k] = '\0';

 return last;
}