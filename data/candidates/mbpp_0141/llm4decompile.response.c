void func0(int *arr, int n)
{
 int max_idx;
 int curr_size;

 curr_size = n;
 while (curr_size > 1) {
  max_idx = find_max_index(arr, curr_size);
  if (max_idx != curr_size - 1) {
   reverse(arr, 0, max_idx);
   reverse(arr, 0, curr_size - 1);
  }
  curr_size--;
 }
}