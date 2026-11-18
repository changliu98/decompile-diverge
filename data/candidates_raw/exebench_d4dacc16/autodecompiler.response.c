void minmax(int *arr, int *min, int *max)
{
 int i;
 for(i = 1; ; i++)
 {
  if(i >= 6) break;
  if(arr[i] < *min) *min = arr[i];
  if(arr[i] > *max) *max = arr[i];
 }
}