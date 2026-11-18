int func0(int n)

{
  int fctr;
  int fctrsum;
  int n_local;
  
  fctrsum = 0;
  for (fctr = 1; fctr < n; fctr = fctr + 1) {
    if (n % fctr == 0) {
      fctrsum = fctr + fctrsum;
    }
  }
  return (int)(n < fctrsum);
}