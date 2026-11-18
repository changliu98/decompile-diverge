int func0(int *array, int length) {
 int i, j, count, sum;
 sum = 0;

 for (i = 0; ; i++) {

  if (i >= length)
   break;

  count = 1;
  for (j = 0; j < length; j++) {

   if (array[j] == array[i] && j != i)
    count++;
  }

  if (count > 1)
   sum += array[i];
 }

 return sum;
}