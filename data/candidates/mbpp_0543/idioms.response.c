int func0(long long a, long long b){
  long long sum = a + b;
  int len = 0;
  while(sum > 0){
    sum = sum / 10;
    len++;
  }
  return len;
}