int int2arr(int *array, int num){
 int i = 0;
 while(num != 0){
  array[i] = num % 10;
  num = num / 10;
  i++;
 }
 return i;
}