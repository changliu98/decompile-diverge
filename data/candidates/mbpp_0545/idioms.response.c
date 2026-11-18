int func0(int n){
  int result = n;
  if (n == 1){
    return 0;
  }
  else {
    result = n ^ func0(n);
  }
  return result;
}