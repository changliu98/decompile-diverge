int getFirst(int *array, int *first){
 int count = 0;
 int size = sizeof(array)/sizeof(array[0]);
 for(int i = 0; i < size; i++){
  if(array[i] != 0){
   count++;
   *first = array[i];
  }
  else
   continue;
 }
 return count;
}