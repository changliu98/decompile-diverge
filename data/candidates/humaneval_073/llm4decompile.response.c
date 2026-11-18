int func0(int *arr, int size)
{
 int i;
 int count = 0;

 for (i = 0; i < size / 2; i++) {
  if (arr[i] != arr[size - 1 - i])
   count++;
 }

 return count;
}