int find(float x, float *xval, int n)
{
  int ilow; int ihigh; int i;
  if (x <= xval[0])
    return 0;
  if (x >= xval[n-1])
    return n-1;
  ilow = 1;
  ihigh = n;
  for (i = n - 1; i > 1; i = ihigh - ilow) {
    if (xval[(ilow + ihigh)/2 - 1] < x)
      ilow = (ilow + ihigh)/2;
    else
      ihigh = (ilow + ihigh)/2;
  }
  return ilow - 1;
}