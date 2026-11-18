int get_min_max(int a, int b, int c, int d, int *min, int *max)
{
  int min1; int max1;
  if ( a == c )
    min1 = -1;
  else if ( a < c )
    min1 = a;
  else
    min1 = c;
  *min = min1;
  if ( b == d )
    max1 = -1;
  else if ( b > d )
    max1 = b;
  else
    max1 = d;
  *max = max1;
  return 0;
}