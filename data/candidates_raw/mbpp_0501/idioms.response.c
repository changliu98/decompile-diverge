int nprimefactors(int a, int b){
  int n = ngcd(a,b);
  int ret = 0;
  int i;
  int sqrtn = (int)sqrt((double)n);
  for(i=1; i <= sqrtn; i++){
    if(n%i == 0){
      ret += 2;
      if(i == n/i){
        ret -= 1;
      }
    }
  }
  return ret;
}