int func0(int a[], int n, int x){
  int count = 0;
  int i;
  for(i = 0; i < n; i++){
    if(a[i] == x){
      count++;
    }
  }
  return count;
}