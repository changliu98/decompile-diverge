double func0(int n)
{
  if ( n < 2 )
    return 1.0;
  else
    return (1.0 / (double)n) + func0( n - 1 );
}