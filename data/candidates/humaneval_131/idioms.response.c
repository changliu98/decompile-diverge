int func0(int n){
  int prod = 1;
  int has_odd = 0;
  while(n > 0){
    if((n % 10) % 2 == 1){
      has_odd = 1;
      prod *= n % 10;
    }
    n /= 10;
  }
  if(has_odd){
    return prod;
  }
  else {
    return 0;
  }
}