int prime_factor_sum ( int n ) {

 int i;
 int sum = 0;

 for ( i = 2; i * i <= n; i++ )
  while ( n % i == 0 ) {
   sum += i;
   n /= i;
  }

 sum += n;

 return sum;

}