int func0(int n)
{
  int fctr, fctrsum;
  fctrsum = 0;
  for (fctr = 1; fctr < n; fctr++)
    if (n % fctr == 0)
      fctrsum += fctr;
  if (fctrsum > n)
    return 1;
  return 0;
}