void int_to_str(unsigned int n, char *c) {
 int i = 10 - 1;
 while(1) {
  if(i < 0) {
   break;
  }
  c[i] = n % 10 + '0';
  n /= 10;
  i--;
 }
 c[10] = '\0';
}