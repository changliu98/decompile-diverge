void compare(int arr[], int size, int num)
{
 int i, j, temp;
 for(j = 0; j < size-1; j++)
 {
  for(i = 0; i < size-j-1; i++)
  {
   if(arr[i] > arr[i+1])
   {
    temp = arr[i];
    arr[i] = arr[i+1];
    arr[i+1] = temp;
   }
  }
 }

 if(num > arr[size-1])
 {
  printf("Yes, the entered number is greater than those in the array\n");
 }
 else
 {
  printf("No, entered number is less than those in the array\n");
 }
}