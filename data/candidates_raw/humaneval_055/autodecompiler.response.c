int fib(int n)
{
 int F[1000];
 memset(F, 0, sizeof(F));
 F[0] = 0; F[1] = 1;
 int i;
 for (i = 2; ; ++i)
 {
  if (i > n) break;
  F[i] = F[i-1] + F[i-2];
 }
 return F[n];
}