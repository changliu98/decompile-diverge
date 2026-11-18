int func0(int n)
{
 int i, j, k, m;
 int max = 0;
 for (i = 1; i < n - 1; i++) {
  for (j = 1; j < n; j++) {
   k = n - i - j;
   m = i * j * k;
   if (m > max)
    max = m;
  }
 }
 return max;
}