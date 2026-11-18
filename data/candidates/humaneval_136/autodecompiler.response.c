void func0(int *arr, int size, int *minmax)
{
 int max = 0, min = 0, i;
 for(i = 0; ; i++)
 {
  if(i >= size) break;
  if(arr[i] < 0 && (max == 0 || arr[i] > max)) max = arr[i];
  if(arr[i] > 0 && (min == 0 || arr[i] < min)) min = arr[i];
 }
 minmax[0] = max;
 minmax[1] = min;
}