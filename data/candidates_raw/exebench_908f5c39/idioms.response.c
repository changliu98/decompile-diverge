int gcd(int *a, int *b)
{
  int *t;
  while(*a > 0){
    if(*a < *b){
      t = a;
      a = b;
      b = t;
    }
    *a -= *b;
  }
  return *b;
}