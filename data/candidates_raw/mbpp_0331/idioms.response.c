int get_count(int n){
  int i;
  int count = 0;
  for(i = 1; i < n + 1; i = i << 1){
    if((n & i) == 0){
      count++;
    }
  }
  return count;
}