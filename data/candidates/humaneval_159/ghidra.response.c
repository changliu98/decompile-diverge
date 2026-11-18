void func0(int number,int need,int remaining,int *result)

{
  int *result_local;
  int remaining_local;
  int need_local;
  int number_local;
  
  if (remaining < need) {
    *result = number + remaining;
    result[1] = 0;
  }
  else {
    *result = number + need;
    result[1] = remaining - need;
  }
  return;
}