int func0(int n)
{
  int i = n;
  int a = 3;
  int b = 0;
  int c = 2;
  int sum = 0;
  int temp = 0;
  if ( n == 0 )
    return 3;
  if ( n == 1 )
    return 3;
  if ( n == 2 )
    return 5;
  sum = 5;
  while ( i > 2 )
  {
    temp = b + a;
    sum = sum + temp;
    a = b;
    b = c;
    c = temp;
    i = i - 1;
  }
  return sum;
}