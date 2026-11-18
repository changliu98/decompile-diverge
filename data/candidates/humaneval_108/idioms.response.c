int func0(int *array, int size){
  int count = 0;
  int i = 0;
  for(i = 0; i < size; i++){
    if(array[i] > 0){
      count++;
    }
    else{
      int sum = 0;
      int num = abs(array[i]);
      while(num / 10 > 0){
        sum += (num % 10);
        num = num / 10;
      }
      sum += num;
      if(sum - num > 0){
        count++;
      }
    }
  }
  return count;
}