int min(int array[], int length) {
 int min = array[0];
 int i;

 for (i = 0; ; i++) {
  if (i >= length) break;
  if (array[i] < min) min = array[i];
 }

 return min;
}