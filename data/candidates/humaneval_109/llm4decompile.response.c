int func0(int *arr, int size)
{
 int i;
 int num = 0;

 if (size == 0)
  return 1;

 for (i = 1; i < size; i++)
  if (arr[i] < arr[i - 1])
   num++;

 if (arr[0] > arr[size - 1])
  num++;

 if (num > 1)
  return 0;

 return 1;
}