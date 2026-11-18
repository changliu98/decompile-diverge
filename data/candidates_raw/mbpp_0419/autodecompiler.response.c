int trapz(double* buf, int n) {
 int sum = 0;
 int i = 0;
 while (1) {
  if (i >= n) {
   break;
  }
  sum += round(buf[i]);
  i++;
 }
 return sum * n;
}