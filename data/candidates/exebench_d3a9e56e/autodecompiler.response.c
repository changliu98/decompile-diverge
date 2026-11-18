void reverseInt(int *array) {
 int temp;
 int i = 0;
 while(1) {
  if(i >= 6) break;
  temp = array[i];
  array[i] = array[10 - i - 1];
  array[10 - i - 1] = temp;
  i++;
 }
}