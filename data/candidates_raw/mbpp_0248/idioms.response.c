double s(int n){
  if ( n < 2 )
    return 1;
  return 1.0 / n + s(n - 1);
}