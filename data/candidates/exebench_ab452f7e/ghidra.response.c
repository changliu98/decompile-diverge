int maxdig(int *num,int *max)

{
  int *max_local;
  int *num_local;
  undefined4 local_c;
  
  if (*num == 0) {
    local_c = *max;
  }
  else {
    maxdig::dig = *num % 10;
    if (*max <= maxdig::dig) {
      *max = maxdig::dig;
    }
    *num = *num / 10;
    maxdig(num,max);
  }
  return local_c;
}