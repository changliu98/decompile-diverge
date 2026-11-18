int func0(int n)
{
  int fctr; int fctrsum = 0;
  for (fctr = 1; fctr < n; fctr++)
    if (n % fctr == 0)
      fctrsum += fctr;
  return fctrsum > n;
}