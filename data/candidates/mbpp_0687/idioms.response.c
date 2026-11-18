int func0(int a, int b){
  int max;
  int min;
  if (a < b){
    max = b;
    min = a;
  }
  else {
    max = a;
    min = b;
  }
  if (max == 0){
    return min;
  }
  else if (max == 1){
    return 1;
  }
  return func0(max, min % max);
}