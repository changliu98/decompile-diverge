void func0(int *arr, int size, int number)
{
 int i, j, temp;
 for (i = 0; i < size - 1; i++)
 {
  for (j = 0; j < size - i - 1; j++)
  {
   if (arr[j] > arr[j + 1])
   {
    temp = arr[j];
    arr[j] = arr[j + 1];
    arr[j + 1] = temp;
   }
  }
 }
 if (arr[size - 1] < number)
 {
  printf("Yes, the entered number is greater than those in the array\n");
 }
 else
 {
  printf("No, entered number is less than those in the array\n");
 }
}