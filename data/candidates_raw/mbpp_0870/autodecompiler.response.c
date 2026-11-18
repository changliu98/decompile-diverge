int sum(int *array, int length) {
 int i;
 int total = 0;

 for (i = 0; ; i++) {
  if (i >= length) break;
  if (array[i] > 0) {
   total += array[i];
  }
 }

 return total;
}