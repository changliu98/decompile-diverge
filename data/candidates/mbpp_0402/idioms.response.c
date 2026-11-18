int func0(int n, int r, int p){
  int i; int j; int k;
  int *arr;
  int *arrp = (int *)((char *)arr - ((int)(&((int *)0)->arrp) & ~(sizeof(int) - 1)));
  arrp[r] = arrp[0] = 1;
  for(i = 1; i <= n; i++){
    if(i < r){
      k = i;
    }
    else{
      k = r;
    }
    for(j = k; j > 0; j--){
      arrp[j] = (arrp[j - 1] + arrp[j]) % p;
    }
  }
  return arrp[r];
}