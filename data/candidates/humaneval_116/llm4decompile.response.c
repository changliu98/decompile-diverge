void func0(int *arr, int size)
{
 int i, j, x, y, temp, count_ones, temp2;

 for (i = 0; i < size; i++) {
  for (j = i + 1; j < size; j++) {
   x = arr[i];
   y = arr[j];

   count_ones = 0;
   while (x > 0) {
    if (x & 1)
     count_ones++;
    x >>= 1;
   }

   temp = 0;
   while (y > 0) {
    if (y & 1)
     temp++;
    y >>= 1;
   }

   if (count_ones > temp) {
    temp2 = arr[i];
    arr[i] = arr[j];
    arr[j] = temp2;
   } else if (count_ones == temp) {
    if (arr[j] < arr[i]) {
     temp2 = arr[i];
     arr[i] = arr[j];
     arr[j] = temp2;
    }
   }
  }
 }
}