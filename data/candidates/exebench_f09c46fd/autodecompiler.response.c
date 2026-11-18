void minmax(int *arr, int size, int *min, int *max)
{
 if(*min > arr[0])
 {
  *min = arr[0];
 }
 if(*max < arr[0])
 {
  *max = arr[0];
 }
}