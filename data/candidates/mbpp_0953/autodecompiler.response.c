int func0 (int *arr, int n) {
 int i, j = 0, k, len = 0, maxLen = 0;
 while (1) {
  if (j >= n - 1) break;
  for (i = 0; i < n - j - 1; i++) {
   if (arr[i] > arr[i + 1]) {
    int temp = arr[i];
    arr[i] = arr[i + 1];
    arr[i + 1] = temp;
   }
  }
  j++;
 }

 for (k = 0; k < n; k++) {
  len = 1;
  for (i = k; i < n; i++) {
   if (arr[i] == arr[i + 1]) {
    len++;
   } else {
    break;
   }
  }
  if (len > maxLen) maxLen = len;
 }
 return maxLen;
}