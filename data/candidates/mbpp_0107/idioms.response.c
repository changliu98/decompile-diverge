int func0(int l, int r)
{
  int count = 0;
  int i = 0;
  int k = 0;
  for ( i = l; i <= r; i++ )
  {
    if ( i >= 10 && i <= 15 )
    {
      count++;
    }
    else if ( i > 15 )
    {
      for ( k = i; k != 0; k = k / 16 )
      {
        if ( k % 16 >= 10 )
        {
          count++;
        }
      }
    }
  }
  return count;
}