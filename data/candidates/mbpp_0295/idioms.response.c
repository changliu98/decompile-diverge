int func0(int n){
  int sum = 1;
  int i;
  for(i = 2; i < n; i++){
    if(n % i == 0){
      sum += i;
    }
  }
  return sum;
}