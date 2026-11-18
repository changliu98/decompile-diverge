void swap(int *arr)
{
 int min, min_index, max, max_index;
 int i;

 min_index = 0;
 min = arr[0];
 i = 0;
 while (1)
 {
  if (i >= 11)
   break;
  if (arr[i] < min)
  {
   min = arr[i];
   min_index = i;
  }
  i++;
 }
 max_index = 0;
 max = arr[0];
 i = 0;
 while (1)
 {
  if (i >= 11)
   break;
  if (arr[i] > max)
  {
   max = arr[i];
   max_index = i;
  }
  i++;
 }

 arr[0] = arr[0] + arr[min_index];
 arr[min_index] = arr[0] - arr[min_index];
 arr[0] = arr[0] - arr[min_index];

 arr[9] = arr[9] + arr[max_index];
 arr[max_index] = arr[9] - arr[max_index];
 arr[9] = arr[9] - arr[max_index];
}