int fft_size(int n)
{
 int m, k;

 for (m = 2; ; m++) {
  if (m * m > n) {
   k = 1;
   break;
  }
  if (n % m == 0) {
   k = n / m;
   break;
  }
 }

 return k;
}