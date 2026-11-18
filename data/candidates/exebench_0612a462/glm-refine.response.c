int __cdecl gcdEx(int a, int b, int *x, int *y)
{
  if (b != 0)
  {
    int gcd = gcdEx(b, a % b, x, y);
    
    int temp = *x;
    *x = *y;
    *y = temp - *y * (a / b);
    
    return gcd;
  }
  else
  {
    *x = 1;
    *y = 0;
    return a;
  }
}