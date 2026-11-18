int sieve(int n)
{
 char p[n+1];
 int i, j, sum;

 for (i = 0; i <= n; ++i)
  p[i] = 1;

 for (i = 2; i*i <= n; ) {
  if ((p[i] & 1) == 1) {
   for (j = 2*i; j <= n; j += i)
    p[j] = 0;
  } else {
   i++;
  }
 }

 sum = 0;
 for (i = 2; i <= n; ++i) {
  if (p[i]) sum += i;
 }

 return sum;
}