int func0(int *array, int size) {
 int first_even = -1, first_odd = -1;
 int i, j;

 for (i = 0; ; i++) {
  if (i >= size)
   break;

  if (array[i] % 2 == 0) {
   first_even = array[i];
   break;
  }
 }

 for (j = 0; ; j++) {
  if (j >= size)
   break;

  if (array[j] % 2 != 0) {
   first_odd = array[j];
   break;
  }
 }

 return first_even - first_odd;
}