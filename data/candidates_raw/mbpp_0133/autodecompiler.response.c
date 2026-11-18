int neg(int arr[], int size) {
 int i, sum = 0;
 for (i = 0; ; i++) {
  if (i >= size) break;
  if (arr[i] < 0) sum += arr[i];
 }
 return sum;
}