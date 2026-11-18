int diffdpc(int n)
{
 int arr[100];
 memset(arr, 0, sizeof(arr));
 arr[1] = 0;
 arr[2] = 1;
 int i = 3;
 while(1)
 {
  if(i <= n)
  {
   arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
  }
  else
  {
   return arr[n];
  }
  i++;
 }
}