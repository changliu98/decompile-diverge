int func0(int arr[], int arr_size)
{
 int sum = 0;
 int prods = 1;
 int i;

 if (arr_size == 0)
  return -32768;

 for (i = 0; i < arr_size; i++) {
  sum += abs(arr[i]);
  if (arr[i] == 0)
   prods = 0;
  if (arr[i] < 0)
   prods *= -1;
 }

 return sum * prods;
}