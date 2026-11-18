int func0(int a[], int n){
  int i; int j; int temp;
  for(i = 0; i < n - 1; i++){
    for(j = 0; j < n - i - 1; j++){
      if(a[j] > a[j + 1]){
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
  int min = 0x7fffffff;
  for(i = 0; i < n - 1; i++){
    if((a[i + 1] - a[i]) < min){
      min = a[i + 1] - a[i];
    }
  }
  return min;
}