int num_to_array(int *arr, int num)
{
 int i;
 for (i = 0; num > 0; i++) {
  arr[i] = num % 10;
  num /= 10;
 }
 return i;
}