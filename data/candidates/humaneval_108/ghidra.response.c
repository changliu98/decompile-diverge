int func0(int *n,int size)

{
  int w;
  int sum;
  int i;
  int num;
  int size_local;
  int *n_local;
  
  num = 0;
  for (i = 0; i < size; i = i + 1) {
    if (n[i] < 1) {
      sum = 0;
      for (w = abs(n[i]); 9 < w; w = w / 10) {
        sum = w % 10 + sum;
      }
      if (0 < sum - w) {
        num = num + 1;
      }
    }
    else {
      num = num + 1;
    }
  }
  return num;
}