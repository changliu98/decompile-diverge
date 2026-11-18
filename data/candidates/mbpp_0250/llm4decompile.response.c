int func0(int *arr, int arr_size, int x) {
 int count = 0;
 for (int i = 0; i < arr_size; i++) {
  if (arr[i] == x) {
   count++;
  }
 }
 return count;
}