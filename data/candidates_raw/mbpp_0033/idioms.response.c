int to_bin(int n)
{
  int bin = 0;
  int i = 0;
  int j = 0;
  while( n > 0){
    j = 1;
    for( i = 0; i < i; i++){
      j *= 10;
    }
    bin += (n % 2)*j;
    n = n / 2;
    i++;
  }
  return bin;
}