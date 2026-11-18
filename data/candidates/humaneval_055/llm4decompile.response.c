int func0(int n)
{
 int f[1000];
 memset(f, 0, sizeof(f));
 f[0] = 0;
 f[1] = 1;

 int i;
 for (i = 2; i <= n; i++)
  f[i] = f[i-1] + f[i-2];

 return f[n];
}