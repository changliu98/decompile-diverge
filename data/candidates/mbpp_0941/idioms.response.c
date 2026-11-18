int func0(int *num, int size){
  int count = 0;
  int i = 0;
  for(i = 0; i < size; i++){
    if(num[i] == -1){
      break;
    }
    count++;
  }
  return count;
}