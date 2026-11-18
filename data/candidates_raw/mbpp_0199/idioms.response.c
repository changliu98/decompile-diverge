int is_prime(int n)
{
  int i;
  int prime = 0;
  for (i = n; i > 0; i--) {
    if ( (i - 1) & i == 0 ) {
      prime = i;
      break;
    }
  }
  return prime;
}