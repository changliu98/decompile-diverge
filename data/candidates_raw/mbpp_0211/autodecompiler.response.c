int main()
{
  int i, n;
  if(n<0)
  {
    printf__bench("Incorrect input");
    return 0;
  }
  else if(n==0)
  {
    printf__bench("0");
    return 0;
  }
  else if(n==1)
  {
    printf__bench("1");
    return 1;
  }
  else
  {
    for(i=2;i<=n;i++)
    {
      printf__bench("%d ",fib(i));
    }
    return fib(n);
  }
}