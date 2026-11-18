int getAmicableNumbers(int limit){
  int i;
  int sum;
  int sum2;
  int j;
  int sum_j;
  int sum2_j;
  if (limit < 1){
    return -1;
  }
  sum = 0;
  for (i = 2; i <= limit; i++){
    sum = 0;
    for (j = 1; j < i; j++){
      if (i % j == 0){
        sum += j;
      }
    }
    sum2 = 0;
    for (sum_j = 1; sum_j < sum; sum_j++){
      if (sum % sum_j == 0){
        sum2 += sum_j;
      }
    }
    if (i == sum2 && i != sum){
      sum += i;
    }
  }
  return sum;
}