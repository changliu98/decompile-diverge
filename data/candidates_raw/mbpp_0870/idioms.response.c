int sum_of_pos(int *array, int size){
  int sum = 0;
  int i = 0;
  for(i = 0; i < size; i++){
    if(array[i] > 0){
      sum += array[i];
    }
  }
  return sum;
}