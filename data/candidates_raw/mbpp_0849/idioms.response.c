int f1(int n)
{
  int i; int j; int k;
  int *a;
  int n = n;
  a = (int *) ( ( (char *) (a) - ( (char *) ( &a[1] ) - ( char *) (a) ) * ( ( sizeof(int) * ( n + 1 ) + sizeof(int) - 1 ) & ~( sizeof(int) - 1 ) ) ) );
  for ( i = 0; i <= n; i++ )
    a[i] = 0;
  for ( i = 2; i <= n; i++ )
    if ( a[i] == 0 )
      for ( j = i; j <= n; j += i )
        a[j] += i;
  return a[n];
}