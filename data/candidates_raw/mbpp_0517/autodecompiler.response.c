int max(int array[], int length) {
 int max = array[0];
 int i = 0;
 while(1){
  if(i >= length)
   break;
  if(array[i] > max)
   max = array[i];
  i++;
 }
 return max;
}