int func0(int n)
{
  int i; int f[100];
  f[0]=0;
  f[1]=1;
  for(i=2; i<=n; i++)
    f[i]=f[i-1]+f[i-2]+f[i-3];
  return f[n];
}