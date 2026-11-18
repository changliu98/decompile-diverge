int binary_search(int *array, int n, int value)
{
 int left = 0;
 int right = n - 1;
 int middle;

 while (left <= right) {
  middle = left + ((right - left) >> 1);
  if (value < array[middle])
   right = middle - 1;
  else if (value > array[middle])
   left = middle + 1;
  else
   return middle;
 }

 return -1;
}