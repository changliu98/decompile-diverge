void sort(int *array, int size){
  int i; int j; int temp; int count_ones; int count_onesa;
  for(i = 0; i < size; i++){
    for(j = i + 1; j < size; j++){
      count_ones = 0;
      temp = array[i];
      int temp2 = array[j];
      while(temp > 0){
        count_ones += temp & 1;
        temp >>= 1;
      }
      temp = count_ones;
      count_onesa = 0;
      while(temp2 > 0){
        count_onesa += temp2 & 1;
        temp2 >>= 1;
      }
      if((count_onesa < temp)||((count_onesa == temp)&& (array[j]<array[i]))){
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}