int min_max(int *arr, int size, int *min, int *max)
{
 int i=0;
 if(size%2!=0)
 {
  *min=arr[0];
  *max=arr[0];
  i=1;
 }
 else
 {
  i=2;
  if(arr[0]<arr[1])
  {
   *min=arr[0];
   *max=arr[1];
  }
  else
  {
   *min=arr[1];
   *max=arr[0];
  }
 }

 return i;
}