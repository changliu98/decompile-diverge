double func0(int n)
{
 int r;
 double nCr, sum;

 sum = 1.0;
 nCr = 1.0;
 for (r = 1; r <= n; r++) {
  nCr = nCr * (n + 1 - r) / r;
  sum += nCr * nCr;
 }
 return sum;
}