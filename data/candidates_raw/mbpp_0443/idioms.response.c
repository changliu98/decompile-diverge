int min(int *list, int size){
  int min = list[0];
  int i;
  for(i = 0; i < size; i++){
    if(list[i] < min){
      min = list[i];
    }
  }
  return min;
}