int func0(int *array, int size){
 int product = 1;
 int i = 0;
 for(i = 0; i < size; i++){
  product = product * array[i];
 }
 return product;
}