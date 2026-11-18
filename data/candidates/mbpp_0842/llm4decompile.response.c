int func0(int arr[], int arr_size) {
 int i, j;
 for (i = 0; i < arr_size; i++) {
  int count = 0;
  for (j = 0; j < arr_size; j++) {
   if (arr[i] == arr[j]) {
    count++;
   }
  }
  if (count % 2) {
   return arr[i];
  }
 }
 return -1;
}