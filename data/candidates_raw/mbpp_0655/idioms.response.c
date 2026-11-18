int f1(int n){
  int sum = 0;
  int i;
  for(i=1; i<=n; i++)
    sum += i*i*i*i*i;
  return sum;
}